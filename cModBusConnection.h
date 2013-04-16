#pragma once
/**

  Base class for all kinds of MODBUS connections

  */
class cConnectionBase
{
	protected:
	enum connection_type {
		none,
		serial,
		tcp
	} myType;
	bool flagRTU;
	char * myErrorMsg;


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

	const char * GetLastError()				{ return myErrorMsg; }

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
	/**

	Construct serial connector

	This does not open the connection - call Connect()

	*/
	cConnectionSerial()
		: cConnectionBase( serial )
		, myCOMPort( -1 )
	{}
	int Connect();

	/// True if the connection is open
	virtual bool IsOpened()					{ return mySerial.IsOpened(); }

	/**
	 Wait for some data to arrive.

	 @param[in]  msec milliseconds to wait before timeout
	 @param[in] len minimum amount of data reuired

	  @return 1 if data ready, 0 if timeout

	  */
	int WaitForData( int len, int msec )	{ return mySerial.WaitForData( len, msec ); }
/**

  Read data from COM port

  @param[in] msg pointer to location to store data
  @param[in] len  maximum number of bytes to read

  @return  0 if error

*/	
	int ReadData( void * msg, int len )		{ return mySerial.ReadData( msg, len ); }
/**

  Check for data waiting to be read

  @return  the number of bytes waiting to be read

*/
	int ReadDataWaiting( void )				{ return mySerial.ReadDataWaiting(); }
/**

  Send data to the COM port

  @param[in] buffer  pointer to data to be written
  @param[in] size    number of bytes to write

  @return 0 if error

*/
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

	int Connect();
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

	const char * GetLastError() { return myErrorMsg; }

private:
	std::string myHumanReadableMessage;
	std::string myHumanReadableReply;
	float myValue;
	unsigned char myBuffer[100];
	
	cConnectionBase * myConnection;

	char * myErrorMsg;

	void Server();
	std::string MakeHumanReadable( unsigned char * msg, int len );
	unsigned char LongitudinalRedundancyCheck(
		unsigned char * msg, int len);
	unsigned short CyclicalRedundancyCheck(
		unsigned char * msg, int len );
};

extern cModBusSim theModBusSim;