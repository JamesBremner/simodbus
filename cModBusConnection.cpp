#include "StdAfx.h"


#include "cModBusConnection.h"

cModBusSim theModBusSim;


/*
class cModbusSlaveConnect
	: public boost::enable_shared_from_this<cModbusSlaveConnect>
{
public:
	typedef boost::shared_ptr<cModbusSlaveConnect> pointer;

	~cModbusSlaveConnect()
	{
		printf(" connection destroyed\n");
	}

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new cModbusSlaveConnect(io_service));
	}
	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}
	void start()
	{
		printf("Connected\n");

		connected = true;

		wait();

	}

	void wait()
{
	socket_.async_read_some(boost::asio::buffer(myBuffer,256),
		boost::bind(&cModbusSlaveConnect::reader,this,
		boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	}
	void reader( const boost::system::error_code& error,
		std::size_t len )
	{
		if (error) {
			return;
		}
	}


private:
	cModbusSlaveConnect(boost::asio::io_service& io_service)
		: socket_(io_service)
		, connected( false )
	{  }
	boost::asio::ip::tcp::socket socket_;

  char myBuffer[256];

  bool connected;
};

class cModbusSlaveServer
{
public:
	cModbusSlaveServer(boost::asio::io_service& io_service)
		: acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
				27015))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		cModbusSlaveConnect::pointer new_connection = cModbusSlaveConnect::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&cModbusSlaveServer::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(cModbusSlaveConnect::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			// start the new connection running
			new_connection->start();

			// get ready to accept next connection
			start_accept();
		}
	}

	boost::asio::ip::tcp::acceptor acceptor_;
};

*/

cModBusSim::cModBusSim(void)
: myConnection( new cConnectionBase )
{

}

cModBusSim::~cModBusSim(void)
{
}

int cModBusSim::Connect()
{
	int iret =  myConnection->Connect();
	if(  iret ) {
		myErrorMsg = (char*)myConnection->GetLastError();
	}
	return iret;
}


void cModBusSim::setSerial()
{
	if( myConnection->IsSerial() )
		return;
	delete myConnection;
	myConnection = new cConnectionSerial();
}
void cModBusSim::setTCP()
{
	if( myConnection->IsTCP() )
		return;
	delete myConnection;
	myConnection = new cConnectionTCP;
}

/**

  Send a read query

  @param[in] Station
  @param[in] Register

*/
void cModBusSim::SendQueryRead( int Station, int Register )
{
	unsigned char buf[1000];
	int msglen;
	if( IsRTU() ) {
		buf[0] = Station;
		buf[1] = 4;
		buf[2] = 0;				// max register 255
		buf[3] = Register;
		buf[4] = 0;
		buf[5] = 1;
		unsigned short crc = CyclicalRedundancyCheck( buf,6);
		buf[6] = crc >> 8;
		buf[7] = 0xFF & crc;
		msglen = 8;
	} else {
		buf[0] = ':';				// ASCII framing start
		buf[1] = Station >> 4;
		buf[2] = 0xF  & Station;
		buf[3] = 0;
		buf[4] = 4;					// read command
		buf[5] = Register >> 4;
		buf[6] = 0xF  & Register;
		buf[7] = 0;
		buf[8] = 1;					// read one register
		unsigned char lrc = LongitudinalRedundancyCheck( &buf[1],8);
		buf[9] =  lrc  >> 4;					// LRC
		buf[10] = 0xF & lrc;
		buf[11] = '\r';				// ASCFII framing end
		buf[12] = '\n';	
		msglen = 13;
	}
	myHumanReadableMessage = MakeHumanReadable( buf,msglen);

	myConnection->SendData( 
			(const unsigned char *)buf,
			msglen );

	//if( flagTCP ) {
	//	int iResult = send(ConnectSocket,(const char *)buf,msglen, 0 );
	//	if (iResult == SOCKET_ERROR) {
	//		iResult = WSAGetLastError();
	//		printf("send failed: %d\n", WSAGetLastError());
	//	}
	//} else {
		Sleep(300);
		if( ! myConnection->WaitForData(
			7,
			6000 ) ) {
				myHumanReadableReply = "timed out\r\n";
			return;
		}
		memset(buf,'\0',100);
		msglen = myConnection->ReadData(
			buf,
			999);
		myHumanReadableReply = MakeHumanReadable(buf,msglen);

		int iv;
		union  {
			short s;
			unsigned char c[2];
		} v;
		v.c[0] = buf[4];
		v.c[1] = buf[3];

		iv = v.s & 0x7FFF;
		if( v.s & 0x8000 )
			iv -= 32767;
		myValue = iv / 1000.0f;

	

}

std::string cModBusSim::MakeHumanReadable( unsigned char * msg, int len )
{
	std::string readable;
	char charbuf[10];
	for( int k = 0; k < len; k++ ) {
		sprintf_s(charbuf,9,"%02X ",*msg++);
		readable += charbuf;
	}
	readable += "\r\n";
	return readable;
}
std::string cModBusSim::getReply()
{
	if( myHumanReadableReply.length() ) {
		return myHumanReadableReply;
	} else {
		return std::string("No reply\n");
	}
}


/**

  Connect to serial port communicating with MODBUS stations

  @return 0 if no errors

  */
int cConnectionSerial::Connect()
{
	if( myCOMPort < 1 ) {
		myErrorMsg = "Bad port number";
		return 1;
	}
	char szPort[100];
	sprintf_s(szPort,99,"COM%d",myCOMPort);

	/*
	Configure connection according to MODBUS mode
	*/
	if( ! flagRTU ) {
		mySerial.SetParity(0);
		mySerial.SetByteSize(7);
		mySerial.SetStopBits(TWOSTOPBITS);
	} else {
		mySerial.SetParity(0);
		mySerial.SetByteSize(8);
		mySerial.SetStopBits(ONESTOPBIT);
	}

	/*
	Open connection
	*/
	if( ! mySerial.Open( szPort ) ) {
		myErrorMsg = (char * )mySerial.GetLastError();
		return 1;
	}

	return 0;

}

/**

  Start simulating the stations

  return 0 if no errors

*/
int cModBusSim::Slave()
{
	return myConnection->Slave();

}
void cModBusSim::Server()
{
	//boost::asio::io_service io_service;
	//cModbusSlaveServer server(io_service);
	//io_service.run();

}
/**

  Poll connection for a message from the master

  return 2 or less if no message
  return 3 or more if garbled message
  return 0 if good message received

*/
int cModBusSim::Poll()
{
	if( ! myConnection->IsOpened() )
		return 1;
	if( ! myConnection->ReadDataWaiting() )
		return 2;
	int len = myConnection->ReadData(myBuffer,99);

	myHumanReadableMessage = MakeHumanReadable( myBuffer, len );

	if( ! IsRTU() ) {

		// check framing
		if( (char)myBuffer[0] != ':' )
			return 3;
		if( (char)myBuffer[len-2] != '\r' )
			return 3;
		if( (char)myBuffer[len-1] != '\n' )
			return 3;

		// check LRC
		// don't include framing and master LRC
		unsigned char lrc = LongitudinalRedundancyCheck( &myBuffer[1], len-5 );
		if( (lrc & 0xF) != myBuffer[10] || (lrc >> 4) != myBuffer[9] ) {
			
			return 4;
		}

	} else {

		// RTU mode

		unsigned short crc = CyclicalRedundancyCheck( myBuffer, 6 );
		if( ( crc >> 8  ) != myBuffer[6] && ( crc & 0xFF ) != myBuffer[7] ) {
			myHumanReadableReply = "CRC ERROR\n";
			return 4;
		}

		int cmd = myBuffer[1];
		int block = myBuffer[5];

		// accept either a input or holding register read
		// return same for both
		if( cmd == 3 || cmd == 4 ) {

			// for any read command
			// return just one value = 1
			myBuffer[2] = 2 * block;
			for( int kr = 0; kr < block; kr++ ) {
				myBuffer[3+kr*2] = 0;
				myBuffer[4+kr*2] = 1;
			}
			len = 3 + 2 * block;
			unsigned short crc = CyclicalRedundancyCheck( myBuffer,len);
			myBuffer[len] = crc >> 8;
			myBuffer[len+1] = 0xFF & crc;
			len += 2;


		}

	}
	myHumanReadableReply = MakeHumanReadable(myBuffer,len);
	myConnection->SendData(myBuffer,len);

	return 0;
}
/**
The Longitudinal Redundancy Check

The Longitudinal Redundancy Check (LRC) field is one byte, containing an 8–bit
binary value. The LRC value is calculated by the transmitting device, which
appends the LRC to the message. The receiving device recalculates an LRC
during receipt of the message, and compares the calculated value to the actual
value it received in the LRC field. If the two values are not equal, an error results.
The LRC is calculated by adding together successive 8–bit bytes in the message,
discarding any carries, and then two’s complementing the result. The LRC is an
8–bit field, therefore each new addition of a character that would result in a value
higher than 255 decimal simply ‘rolls over’ the field’s value through zero. Because
there is no ninth bit, the carry is discarded automatically.
A procedure for generating an LRC is:
1. Add all bytes in the message, excluding the starting ‘colon’ and ending
CRLF. Add them into an 8–bit field, so that carries will be discarded.
2. Subtract the final field value from FF hex (all 1’s), to produce the
ones–complement.
3. Add 1 to produce the twos–complement.
Placing the LRC into the Message
When the the 8–bit LRC (2 ASCII characters) is transmitted in the message, the
high–order character will be transmitted first, followed by the low–order character.
For example, if the LRC value is 61 hex (0110 0001):
*/
unsigned char cModBusSim::LongitudinalRedundancyCheck(
	unsigned char * msg, int len )
{
	unsigned char uchLRC = 0 ; /* LRC char initialized */
	while( len-- ) { /* pass through message buffer */
		uchLRC += *msg++ ; /* add buffer byte without carry */
	}
	return ((unsigned char)(-((char)uchLRC))) ; /* return twos complement */
}
unsigned short cModBusSim::CyclicalRedundancyCheck(
	unsigned char * msg, int len )
{
	/* Table of CRC values for high–order byte */
	static unsigned char auchCRCHi[] = {
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
		0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40
	} ;
	/* Table of CRC values for low–order byte */
	static unsigned char auchCRCLo[] = {
		0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
		0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
		0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
		0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
		0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
		0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
		0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
		0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
		0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
		0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
		0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
		0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
		0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
		0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
		0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
		0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
		0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
		0x40
	} ;
	unsigned char uchCRCHi = 0xFF ; /* high byte of CRC initialized */
	unsigned char uchCRCLo = 0xFF ; /* low byte of CRC initialized */
	unsigned uIndex ; /* will index into CRC lookup table */
	while (len--) /* pass through message buffer */
	{
		uIndex = uchCRCHi ^ *msg++ ; /* calculate the CRC */
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ;
		uchCRCLo = auchCRCLo[uIndex] ;
	}
	return (uchCRCHi << 8 | uchCRCLo) ;
}