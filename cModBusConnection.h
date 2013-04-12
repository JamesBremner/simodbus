#pragma once

class cModBusConnection
{
public:

	cModBusConnection(void);
	~cModBusConnection(void);
	void SendQueryRead( int Station, int Register );
	std::string getMessageSent()			{ return myHumanReadableMessage; }
	std::string getReply()					{ return myHumanReadableReply; }
	float getValue()							{ return myValue; }
	int Connect();
	int Slave();
	void setCOMPort( int i )				{ myCOMPort = i; }
	int Poll();
	char * getData()						{ return (char*)myBuffer; /*"test\n\r"; */}
	void setSerial()						{ flagTCP = false; }
	void setTCP()							{ flagTCP = true; }
	bool IsSerial()							{ return ( flagTCP == false ); }

	void setASCII()							{ flagRTU = false; }
	void setRTU()							{ flagRTU = true; }

private:
	std::string myHumanReadableMessage;
	std::string myHumanReadableReply;
	float myValue;
	SOCKET ConnectSocket;
	int myCOMPort;
	raven::cSerial mySerial;
	unsigned char myBuffer[100];
	bool flagRTU;
	bool flagTCP;


	void Server();
	std::string MakeHumanReadable( unsigned char * msg, int len );
	unsigned char LongitudinalRedundancyCheck(
		unsigned char * msg, int len);
	unsigned short CyclicalRedundancyCheck(
		unsigned char * msg, int len );
};

extern cModBusConnection theModBusConnection;