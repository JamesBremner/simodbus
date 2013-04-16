#include "StdAfx.h"

#include "cModBusConnection.h"

 	using namespace  System;
	using namespace  System::Text;
 	using namespace  System::Net;
	using namespace  System::Net::Sockets;

ref class cConnectionTCP_ref {
public: static NetworkStream^ myStream;
};


/**

  Connect to TCP port communicating with MODBUS stations

  @return 0 if no errors

*/
int cConnectionTCP::Connect()
{
	myFlagOpen = false;
	myFlagSlave = false;

	//-------------------------------
	// Initialize socket library
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup( wVersionRequested, &wsaData );

	//--------------------------------
	// Declare and initialize variables.
	char* ip = "127.0.0.1";
	char port[10];
	sprintf_s(port,9,"%d",myPort);
	struct addrinfo aiHints;
	struct addrinfo *aiList = NULL;
	int retVal;

	//--------------------------------
	// Setup the hints address info structure
	// which is passed to the getaddrinfo() function
	memset(&aiHints, 0, sizeof(aiHints));
	aiHints.ai_family = AF_INET;
	aiHints.ai_socktype = SOCK_STREAM;
	aiHints.ai_protocol = IPPROTO_TCP;

	//--------------------------------
	// Call getaddrinfo(). If the call succeeds,
	// the aiList variable will hold a linked list
	// of addrinfo structures containing response
	// information about the host
	if ((retVal = getaddrinfo(ip, port, &aiHints, &aiList)) != 0) {
		myErrorMsg = "getaddrinfo() failed.\n";
		return 1;
	}

	//--------------------------------
	// Connect to socket
	ConnectSocket = INVALID_SOCKET;
	struct addrinfo *ptr;
	ptr = aiList;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
		ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		//printf("Error at socket(): %ld\n", WSAGetLastError());
		myErrorMsg = "Invalid scocket";
		return 1;
	}
	if( connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen) ) {
		//printf("Error at socket(): %ld\n", WSAGetLastError());
		static char msg[200];
		sprintf_s(msg,199,"Error at socket(): %d",WSAGetLastError());
		myErrorMsg = msg;
		return 1;
	}


	myFlagOpen = true;
	return 0;
}

int cConnectionTCP::Slave()
{
	myFlagOpen = false;
	myFlagSlave = true;

	 TcpListener^ server = gcnew TcpListener( IPAddress::Parse( "127.0.0.1" ),myPort );
	 server->Start();

	 TcpClient^ client = server->AcceptTcpClient();
	 cConnectionTCP_ref::myStream = client->GetStream();
	 
	myFlagOpen = true;

	return 0;
}
/**

  True if data available to be read

*/
int cConnectionTCP::ReadDataWaiting( void )
{
	if( myFlagSlave ) {
		return cConnectionTCP_ref::myStream->DataAvailable;
	} else {
		fd_set fds;
		FD_ZERO( &fds );
		FD_SET( ConnectSocket, &fds );
		TIMEVAL timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;
		return ( select( 0, &fds, 0, 0, &timeout ) == 1 );

	}
}
int cConnectionTCP::WaitForData
		( int len, int msec )
{
		int timeout = 0;
	while( ! ReadDataWaiting() )
	{
		if( timeout++ > msec ) {
			return 0;
		}
		Sleep(1);
	}
	return 1;

}

/**

  Read data from COM port

  @param[in] msg pointer to location to store data
  @param[in] len  maximum number of bytes to read

  @return  0 if error

*/	
int cConnectionTCP::ReadData( void* msg, int len )
{
	if( myFlagSlave ) {
	 array<Byte>^ myReadBuffer = gcnew array<Byte>(1024);

	 int i = cConnectionTCP_ref::myStream->Read( myReadBuffer, 0, myReadBuffer->Length );
	 if( i < len )
		 len = i;
	  pin_ptr<unsigned char> p1 = &myReadBuffer[0];
	  unsigned char* p2 = p1;
	  unsigned char* pm = (unsigned char*)msg;
	  for( int k = 0; k < len; k++ ) {
		  *pm++ = *p2++;
	  }
	 
	 return len;
	} else {
		return recv( ConnectSocket, (char*)msg, len, 0 );
	}

}
/**

Send data to the socket

 @param[in] buffer
 @param[in] size  number of bytes to send

 @return 0 if there is an error

 */
int cConnectionTCP::SendData
( const unsigned char *buffer, int size )
{
	if( myFlagSlave ) {
		array<Byte>^ WriteBuffer = gcnew array<Byte>( size );
		pin_ptr<unsigned char> p1 = &WriteBuffer[0];
		unsigned char* p2 = p1;
		for( int k = 0; k < size; k++ ) {
			*p2++ = *buffer++;
		}
		cConnectionTCP_ref::myStream->Write( WriteBuffer, 0, WriteBuffer->Length );
		return size;

	} else {
		int iResult = send(ConnectSocket,
			(const char* )buffer, size, 0 );
		if (iResult == SOCKET_ERROR) {
			iResult = WSAGetLastError();
			printf("send failed: %d\n", WSAGetLastError());
			return 0;
		}
		return size;
	}
}

