#pragma once

class cConnectionBase
{
	protected:
	enum connection_type {
		none,
		serial,
		tcp
	} myType;
	bool flagRTU;


public:
	cConnectionBase()
		: myType( none )
		, flagRTU( true )
	{}
	cConnectionBase( connection_type t )
		: myType( t )
		, flagRTU( true )
	{}

	virtual int Connect()							{ return 1; }		///< No connection from base class
	virtual bool IsOpened()							{ return false; }	///< base class cannot be opened
	virtual int SendData
		( const unsigned char *buffer, int size )	{ return 0; }		///< base class cannot send data
	virtual int WaitForData
		( int len, int msec )						{ return 0; }		///< base class always times out
	virtual int ReadData( void *, int )				{ return 0; }		///< base class connot read data
	virtual int ReadDataWaiting( void )				{ return 0; }		///< never any data on base class

	void setSerial()						{ myType = serial; }
	void setTCP()							{ myType = tcp; }
	virtual void setCOMPort( int i )		{ }

	bool IsSerial()							{ return ( myType == serial ); }
	bool IsTCP()							{ return ( myType == tcp ); }

	void setASCII()							{ flagRTU = false; }
	void setRTU()							{ flagRTU = true; }
	bool IsRTU()							{ return flagRTU; }


};
/**

  Connect using a TCP socket

*/
class cConnectionTCP : public cConnectionBase
{
public:
	int Connect();
	virtual int SendData
		( const unsigned char *buffer, int size );
private:
	SOCKET ConnectSocket;
};
/**

  Connect using a serial port

*/
class cConnectionSerial : public cConnectionBase
{
public:
	cConnectionSerial()
		: cConnectionBase( serial )
		, myCOMPort( -1 )
	{}
	int Connect();
	virtual bool IsOpened()					{ return mySerial.IsOpened(); }
	int WaitForData( int len, int msec )	{ return mySerial.WaitForData( len, msec ); }
	int ReadData( void * msg, int len )		{ return mySerial.ReadData( msg, len ); }
	int ReadDataWaiting( void )				{ return mySerial.ReadDataWaiting(); }
	int SendData
		( const unsigned char *buffer, int size )
	{ return mySerial.SendData( buffer, size ); }

	void setCOMPort( int i )				{ myCOMPort = i; }
private:
	raven::cSerial mySerial;
	int myCOMPort;

};

/**
	Simulate a modbus device or master
*/
class cModBusSim
{
public:

	cModBusSim(void);
	~cModBusSim(void);

	int Connect()				{ return myConnection->Connect(); }
	void setSerial();
	void setTCP();
	bool IsSerial()				{ return myConnection->IsSerial(); }
	bool IsTCP()				{ return myConnection->IsTCP(); }

	void SendQueryRead( int Station, int Register );
	std::string getMessageSent()			{ return myHumanReadableMessage; }
	std::string getReply();
	float getValue()						{ return myValue; }
	
	int Slave();
	
	int Poll();

	char * getData()						{ return (char*)myBuffer; }


	void setCOMPort( int i )				{ myConnection->setCOMPort( i ); }
	void setASCII()							{ myConnection->setASCII(); }
	void setRTU()							{ myConnection->setRTU(); }
	bool IsRTU()							{ return myConnection->IsRTU(); }

private:
	std::string myHumanReadableMessage;
	std::string myHumanReadableReply;
	float myValue;
	unsigned char myBuffer[100];
	
	cConnectionBase * myConnection;

	void Server();
	std::string MakeHumanReadable( unsigned char * msg, int len );
	unsigned char LongitudinalRedundancyCheck(
		unsigned char * msg, int len);
	unsigned short CyclicalRedundancyCheck(
		unsigned char * msg, int len );
};

extern cModBusSim theModBusSim;