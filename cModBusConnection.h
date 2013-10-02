#pragma once


/**

  Base class for all kinds of MODBUS connections

  This maintains the type of connection and provides a common inerface
  for all types.  If you try to open a connection, read or write using this
  then you will simply get an error return.

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
	virtual int Slave()								{ return 1; }		///< No slave simulator in base class
	virtual bool IsOpened()							{ return false; }	///< base class cannot be opened
	virtual void getConfig( std::wstring& config )	{ config.clear(); } ///< no configuration
	virtual int SendData
		( const unsigned char *buffer, int size )	{ return 0; }		///< base class cannot send data
	virtual int WaitForData
		( int len, int msec )						{ return 0; }		///< base class always times out
	virtual int ReadData( void *, int )				{ return 0; }		///< base class connot read data
	virtual int ReadDataWaiting( void )				{ return 0; }		///< never any data on base class

	void setSerial()								{ myType = serial; }
	void setTCP()									{ myType = tcp; }
	virtual void setCOMPort( int i, int nBaud )		{ }

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
	cConnectionTCP()
		: cConnectionBase( tcp )
		, myPort( 27016 )
		, myFlagOpen( false )
	{}
	int Connect();
	bool IsOpened()							{ return myFlagOpen; }
	int Slave();
	int SendData
		( const unsigned char *buffer, int size );
	int ReadDataWaiting( void );
	int ReadData( void *msg, int len );
	virtual int WaitForData
		( int len, int msec );
private:
	SOCKET ConnectSocket;
	int myPort;
	bool myFlagOpen;
	bool myFlagSlave;


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

	/**

	Open the connection

	*/
	int Connect();

	/*
	get the connection configuration ( speed, stop bits etc )

	*/
	void getConfig(std::wstring& config_text )	{ mySerial.getConfig( config_text ); }

	/**

	Start simulating the stations

	This simply opens the connection.
	All stations are assumed to be on one port
	The application is responsible for polling the port

	*/
	int Slave()								{ return Connect(); }

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

	void setCOMPort( int i, int nBaud )				{ myCOMPort = i; myBaud = nBaud; }

private:
	raven::cSerial mySerial;
	int myCOMPort;
	int myBaud;

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
	bool IsSerial()							{ return myConnection->IsSerial(); }
	bool IsTCP()							{ return myConnection->IsTCP(); }
	void getConfig( std::wstring& config )	{ myConnection->getConfig( config ); }

	void SendQueryRead( int Station, int Register, int Length );
	void SendQueryWrite( int Station, int Register, int Value );
	std::string getMessageSent()			{ return myHumanReadableMessage; }
	std::string getReply();
	float getValue( int i = 1 );
	
	int Slave();
	
	int Poll();

	char * getData()						{ return (char*)myBuffer; }


	void setCOMPort( int i, int nBaud )		{ myConnection->setCOMPort( i, nBaud ); }
	void setASCII()							{ myConnection->setASCII(); }
	void setRTU()							{ myConnection->setRTU(); }
	bool IsRTU()							{ return myConnection->IsRTU(); }

	void ClearSimulatedStationRegisters()	{ myStationMap.clear(); }
	void AddSimulatedStationRegister( int station, int reg, int val );

	const char * GetLastError()				{ return myErrorMsg; }

private:
	std::string myHumanReadableMessage;
	std::string myHumanReadableReply;
	float myValue;
	float myValueArray[255];
	unsigned char myBuffer[1000];
	typedef std::map < int, std::map< int, int > > stationmap_t;
	stationmap_t myStationMap;
	
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