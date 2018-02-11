/*---------------------------------------------------------------------+\
|
|	CSerial.cpp  --  brief description of what CSerial.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	06-Jan-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"
#if defined( SERIAL_POSIX )

#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <errno.h>

#if defined( __CYGWIN__ )
#include <cygwin/fs.h>
#else
#include <linux/fs.h>
#include <linux/serial.h>
#include <linux/tty.h>
#endif

#elif defined( SERIAL_WINDOWS )

//#include <crtdbg.h>
#include <tchar.h>
#include <WinReg.h>

#endif // SERIAL_XXXXXX

#include "CSerial.h"
#include "TPointer.h"


NAMESPACE_ROOT_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/


// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 CSerialPortSettings Code
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * CSerialPortSettings - constructor

\+---------------------------------------------------------------------*/
CSerialPortSettings::CSerialPortSettings
		(
		void
		)
		:
		m_oMutex(),
		m_nBaud(9600),
		m_nDataBits(8),
		m_eParity(PAR_NONE),
		m_eStopBits(STOP_1),
		m_eFlow(FLOW_OFF)
{
}

/*---------------------------------------------------------------------+\

 * CSerialPortSettings - constructor

\+---------------------------------------------------------------------*/
CSerialPortSettings::CSerialPortSettings
		(
		ConstCSerialPortSettingsRef	r
		)
		: m_oMutex(),
		m_nBaud(r.m_nBaud),
		m_nDataBits(r.m_nDataBits),
		m_eParity(r.m_eParity),
		m_eStopBits(r.m_eStopBits),
		m_eFlow(r.m_eFlow)
{
}

/*---------------------------------------------------------------------+\

 * ~CSerialPortSettings - destructor

\+---------------------------------------------------------------------*/
CSerialPortSettings::~CSerialPortSettings
		(
		void
		)
{
}



/*---------------------------------------------------------------------+\

 * SetBaud

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::SetBaud
		(
		unsigned long	n
		)
{
	m_nBaud = n;
}


/*---------------------------------------------------------------------+\

 * SetDataBits

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::SetDataBits
		(
		unsigned int	n
		)
{
	m_nDataBits = n;
}

/*---------------------------------------------------------------------+\

 * SetParity

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::SetParity
		(
		EParitys e
		)
{
	m_eParity = e;
}

/*---------------------------------------------------------------------+\

 * SetStopBits

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::SetStopBits
		(
		EStopBits e
		)
{
	m_eStopBits = e;
}

/*---------------------------------------------------------------------+\

 * SetHandshaking

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::SetHandshaking
		(
		EFlow e
		)
{
	m_eFlow = e;
}


/*---------------------------------------------------------------------+\

 * LoadSettings

\+---------------------------------------------------------------------*/
void	CSerialPortSettings::LoadSettings
		(
		ConstCSerialPortSettingsRef r
		)
{
	m_eFlow = r.m_eFlow;
	m_eParity = r.m_eParity;
	m_eStopBits = r.m_eStopBits;
	m_nBaud = r.m_nBaud;
	m_nDataBits = r.m_nDataBits;
}





/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




/*=====================================================================+\
||																		|
||	 CSerial Code
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CSerial - constructor

\+---------------------------------------------------------------------*/
CSerial::CSerial
		(
		void
		)
		:
		inherited(),
		m_sPort(),
		m_nMinBytes(0),
		m_nTimeout(0),
		m_bNonblocking(false),
		m_nLastError( NR_S_SUCCESS ),
		m_nFD( 0 )
#if defined( SERIAL_POSIX )
#elif defined( SERIAL_WINDOWS )
		, m_dwInQueue( 16 )
		, m_dwOutQueue( 16 )
#endif
{
}

/*---------------------------------------------------------------------+\

 * CSerial - copy constructor

\+---------------------------------------------------------------------*/
CSerial::CSerial
		(
		ConstCSerialRef	r
		)
		: inherited( r ),
		m_sPort( r.m_sPort ),
		m_nMinBytes( r.m_nMinBytes ),
		m_nTimeout( r.m_nTimeout ),
		m_bNonblocking( r.m_bNonblocking ),
		m_nLastError( NR_S_SUCCESS ),
		m_nFD( 0 )
#if defined( SERIAL_POSIX )
#elif defined( SERIAL_WINDOWS )
		, m_dwInQueue( r.m_dwInQueue )
		, m_dwOutQueue( r.m_dwOutQueue )
#endif
{
}

CSerial::CSerial
		(
		ConstCSerialPortSettingsRef	r
		)
		: inherited( r ),
		m_sPort(),
		m_nMinBytes(0),
		m_nTimeout(0),
		m_bNonblocking(false),
		m_nLastError( NR_S_SUCCESS ),
		m_nFD( 0 )
#if defined( SERIAL_POSIX )
#elif defined( SERIAL_WINDOWS )
		, m_dwInQueue( 16 )
		, m_dwOutQueue( 16 )
#endif
{
}

/*---------------------------------------------------------------------+\

 * ~CSerial - destructor

\+---------------------------------------------------------------------*/
CSerial::~CSerial
		(
		void
		)
{
	Close();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CSerialRef
		CSerial::operator=
		(
		ConstCSerialRef	r
		)
{
	inherited::operator = ( r );

	m_sPort = r.m_sPort;
	m_nMinBytes = r.m_nMinBytes;
	m_nTimeout = r.m_nTimeout;
	m_bNonblocking = r.m_bNonblocking;
	m_nLastError = NR_S_SUCCESS;
#if defined( SERIAL_POSIX )
	m_nFD = 0;
	m_fdsRead = r.m_fdsRead;
#elif defined( SERIAL_WINDOWS )
#endif

	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPortName

\+---------------------------------------------------------------------*/
bool	CSerial::SetPortName
		(
		const char* sName
		)
{
	m_sPort = sName;
	return true;
}


/*---------------------------------------------------------------------+\

 * GetPortName

\+---------------------------------------------------------------------*/
const char*	
		CSerial::GetPortName
		(
		void
		) const
{
	return m_sPort.Pointer();
}

/*---------------------------------------------------------------------+\

 * SetMinBytes

\+---------------------------------------------------------------------*/
void	CSerial::SetMinBytes
		(
		long n
		)
{
	m_nMinBytes = n;
}

/*---------------------------------------------------------------------+\

 * SetTimeout

\+---------------------------------------------------------------------*/
void	CSerial::SetTimeout
		(
		unsigned long n
		)
{
	m_nTimeout = n;
}


/*---------------------------------------------------------------------+\

 * SetNonblocking

\+---------------------------------------------------------------------*/
void	CSerial::SetNonblocking
		(
		bool	b
		)
{
	m_bNonblocking = b;
}




/*---------------------------------------------------------------------+\

 * Open -

\+---------------------------------------------------------------------*/
NResult	CSerial::Open
		(
		EOpenMode eMode // = MODE_Readonly
		)
{
	NResult	nr = NR_E_FAIL;

#if defined( SERIAL_POSIX )


	m_nFD = -1;

	memset( &m_tTermOpt, 0, sizeof(m_tTermOpt) );

	m_tTermOpt.c_oflag &= ~OPOST;		// raw output

	m_tTermOpt.c_cflag |= CLOCAL;		// no modem control

	switch ( eMode )
	{
	case MODE_Readonly:
	case MODE_ReadWrite:
		m_tTermOpt.c_cflag |= CREAD;
		break;
	case MODE_Writeonly:
	default:
		break;
	}

	switch ( m_nBaud )
	{
	case 50:                //POSIX ONLY
		m_tTermOpt.c_cflag |= B50;
		break;
	case 75:                //POSIX ONLY
		m_tTermOpt.c_cflag |= B75;
		break;
	case 110:
		m_tTermOpt.c_cflag |= B110;
		break;
	case 134:               //POSIX ONLY
		m_tTermOpt.c_cflag |= B134;
		break;
	case 150:               //POSIX ONLY
		m_tTermOpt.c_cflag |= B150;
		break;
	case 200:               //POSIX ONLY
		m_tTermOpt.c_cflag |= B200;
		break;
	case 300:
		m_tTermOpt.c_cflag |= B300;
		break;
	case 600:
		m_tTermOpt.c_cflag |= B600;
		break;
	case 1200:
		m_tTermOpt.c_cflag |= B1200;
		break;
	case 1800:              //POSIX ONLY
		m_tTermOpt.c_cflag |= B1800;
		break;
	case 2400:
		m_tTermOpt.c_cflag |= B2400;
		break;
	case 4800:
		m_tTermOpt.c_cflag |= B4800;
		break;
	case 9600:
		m_tTermOpt.c_cflag |= B9600;
		break;
	case 14400:             //WINDOWS ONLY
	case 19200:
		m_tTermOpt.c_cflag |= B19200;
		break;
	case 38400:
		m_tTermOpt.c_cflag |= B38400;
		break;
	case 56000:             //WINDOWS ONLY
	case 57600:
		m_tTermOpt.c_cflag |= B57600;
		break;
	case 115200:
		m_tTermOpt.c_cflag |= B115200;
		break;
	case 128000:            //WINDOWS ONLY
	case 256000:            //WINDOWS ONLY
		break;
	default:
		break;
	}


	switch ( m_nDataBits )
	{
	case 5:
		m_tTermOpt.c_cflag |= CS5;
		break;
	case 6:
		m_tTermOpt.c_cflag |= CS6;
		break;
	case 7:
		m_tTermOpt.c_cflag |= CS7;
		break;
	case 8:
	default:
		m_tTermOpt.c_cflag |= CS8;
		break;
	}


	switch (m_eStopBits)
	{
	case STOP_1_5:
	case STOP_2:
		m_tTermOpt.c_cflag |= CSTOPB;
		break;
	default:
		m_tTermOpt.c_cflag &= ~CSTOPB;
		break;
	}

	switch ( m_eParity )
	{
	case PAR_NONE:
		m_tTermOpt.c_iflag |= IGNPAR;
		m_tTermOpt.c_cflag &= ~PARENB;
		break;
	case PAR_ODD:
		m_tTermOpt.c_cflag |= PARENB | PARODD;
		break;
	case PAR_EVEN:
		m_tTermOpt.c_cflag |= PARENB;
		m_tTermOpt.c_cflag &= ~PARODD;
		break;
	case PAR_MARK:
		m_tTermOpt.c_iflag |= PARMRK;
		break;
	case PAR_SPACE:
	default:
		break;
	}

	switch ( m_eFlow )
	{
	case FLOW_OFF:
		m_tTermOpt.c_cflag &=  ~CRTSCTS;
		m_tTermOpt.c_iflag &= ~(IXON | IXOFF | IXANY);
		break;
	case FLOW_HARDWARE:
		m_tTermOpt.c_cflag |= CRTSCTS;
		break;
	case FLOW_XONXOFF:
		m_tTermOpt.c_iflag |= (IXON | IXOFF | IXANY);
	default:
		break;
	}


	// Non-canonical input
	m_tTermOpt.c_lflag = 0;

	long	n = m_nTimeout;
	if ( 0 < n )
	{
		n = n / 100;	// make tenths of second
		if ( n < 1 )
			n = 1;
	}
	m_tTermOpt.c_cc[VTIME] = n;

	// this is actually filled in by the read function
	m_tTermOpt.c_cc[VMIN] = m_bNonblocking ? 0 : umax(1L,m_nMinBytes);   // block read until 1 char received


	if ( m_nFD <= 0 )
	{
		int flags = O_NOCTTY|O_NDELAY;

		switch ( eMode )
		{
		case MODE_Readonly:
			flags |= O_RDONLY;
			break;
		case MODE_ReadWrite:
			flags |= O_RDWR;
			break;
		case MODE_Writeonly:
		//	flags = 0;
		default:
			break;
		}


		if( m_bNonblocking )
			flags |= O_NONBLOCK;

		m_nFD = open(m_sPort.Pointer(), flags , 0);

		if ( 0 < m_nFD )
		{
			//flush and set port attributes
			tcflush(m_nFD, TCIFLUSH);
			tcsetattr(m_nFD, TCSANOW, &m_tTermOpt);
			fcntl( m_nFD, F_SETFL, 0 );

			LOCAL_PRINT("CSerial::Open - fd = %d\n", m_nFD);

			nr = NR_S_SUCCESS;
		}
		else
		{
			//error opening serial port
			LogPrint("CSerial::Open:ERROR - could not open serial port '%s'\n", m_sPort.Pointer() );
			int	n = errno;
			if ( 0 != n )
				perror( 0 );
			nr = NR_E_FAIL;
		}
	}
	else
	{
		LOCAL_PRINT("CSerial::Open - already connected\n");
		nr = NR_S_SUCCESS;
	}

#elif defined( SERIAL_WINDOWS )

	DWORD	dwDesiredAccess = 0;

	switch ( eMode )
	{
	case MODE_Readonly:
		dwDesiredAccess = GENERIC_READ;
		break;
	case MODE_ReadWrite:
		dwDesiredAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	case MODE_Writeonly:
		dwDesiredAccess = GENERIC_WRITE;
	default:
		break;
	}

	DWORD	dwBaud = 0;

	switch ( m_nBaud )
	{
	case 50:                //POSIX ONLY
	case 75:                //POSIX ONLY
	case 110:
		dwBaud = CBR_110;
		break;
	case 134:               //POSIX ONLY
	case 150:               //POSIX ONLY
	case 200:               //POSIX ONLY
	case 300:
		dwBaud = CBR_300;
		break;
	case 600:
		dwBaud = CBR_600;
		break;
	case 1200:
		dwBaud = CBR_1200;
		break;
	case 1800:              //POSIX ONLY
	case 2400:
		dwBaud = CBR_2400;
		break;
	case 4800:
		dwBaud = CBR_4800;
		break;
	case 9600:
		dwBaud = CBR_9600;
		break;
	case 14400:             //WINDOWS ONLY
		dwBaud = CBR_14400;
		break;
	case 19200:
		dwBaud = CBR_19200;
		break;
	case 38400:
		dwBaud = CBR_38400;
		break;
	case 56000:             //WINDOWS ONLY
		dwBaud = CBR_56000;
		break;
	case 57600:
		dwBaud = CBR_57600;
		break;
	case 115200:
		dwBaud = CBR_115200;
		break;
	case 128000:            //WINDOWS ONLY
		dwBaud = CBR_128000;
		break;
	case 256000:            //WINDOWS ONLY
		dwBaud = CBR_256000;
		break;
	default:
		break;
	}

	BYTE	byParity;
	switch ( m_eParity )
	{
	case PAR_NONE:
		byParity = NOPARITY;
		break;
	case PAR_ODD:
		byParity = ODDPARITY;
		break;
	case PAR_EVEN:
		byParity = EVENPARITY;
		break;
	case PAR_MARK:               //WINDOWS ONLY
		byParity = MARKPARITY;
		break;
	case PAR_SPACE:
		byParity = SPACEPARITY;
		break;
	default:
		byParity = NOPARITY;
		break;
	}

	BYTE	byStop;
	switch ( m_eStopBits )
	{
	case STOP_1:
		byStop = ONESTOPBIT;
		break;
	case STOP_1_5:               //WINDOWS ONLY
		byStop = ONE5STOPBITS;
		break;
	case STOP_2:
		byStop = TWOSTOPBITS;
		break;
	default:
		byStop = ONESTOPBIT;
		break;
	}



	do_sequence
	{
		if ( m_nFD )
		{
			LogPrint( "%s - already connected\n", __PRETTY_FUNCTION__ );
			LogPrint( "CSerial::Open - already connected\n" );
			nr = m_nLastError = NR_E_CONNECT_FAIL;
			break;
		}


		char	sPort[64];
		sprintf_s(sPort, sizeof(sPort), "\\\\.\\%s", m_sPort.Pointer() );
#	if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR>	wsPort = WideStringFromString( sPort );
		m_nFD = ::CreateFile(wsPort,
								dwDesiredAccess,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_FLAG_OVERLAPPED,
								NULL);

#	else
		m_nFD = ::CreateFileA(sPort,
								dwDesiredAccess,
								0,
								NULL,
								OPEN_EXISTING,
								FILE_FLAG_OVERLAPPED,
								NULL);
#	endif
		if ( INVALID_HANDLE_VALUE == m_nFD )
		{
			GetLastOSError();
			LogPrint( "CSerial::Open -- unble to open port %s\n", m_sPort.Pointer() );
			m_nFD = 0;
			nr = m_nLastError = NR_E_CONNECT_FAIL;
			break;
		}



		// Setup the COM-port
		if (m_dwInQueue || m_dwOutQueue)
		{

			if (!::SetupComm(m_nFD,m_dwInQueue,m_dwOutQueue))
			{
				// Display a warning
				NResult	n = GetLastOSError();
				LogPrint("CSerial::Open - Unable to setup the COM-port\n");

				// Close the port
				Close();

				// Save last error from SetupComm
				nr = m_nLastError = n;
				break;
			}
		}

		COMMCONFIG		tCommCfg = {0};


#if ! defined( OS_MSWIN_WCE )
		// NEEDS_WORK: find WinCE solution

		DWORD	nCommCfgSize = sizeof(COMMCONFIG);
		if ( ! ::GetCommConfig( m_nFD, &tCommCfg, &nCommCfgSize ) )
		{
			// Obtain the error code
			nr = m_nLastError = GetLastOSError();

			// Display a warning
			LogPrint("CSerial::Setup - Unable to obtain configuration information\n");
			break;
		}


		// Obtain the DCB structure for the device
		//CDCB dcb;
		if ( ! ::GetCommState(m_nFD, &tCommCfg.dcb) )
		{
			// Obtain the error code
			nr = m_nLastError = GetLastOSError();

			// Display a warning
			LogPrint("CSerial::Setup - Unable to obtain DCB information\n");
			break;
		}
#endif


		tCommCfg.dcb.fBinary = TRUE;
		tCommCfg.dcb.fInX = FALSE;
		tCommCfg.dcb.fOutX = FALSE;
		tCommCfg.dcb.fAbortOnError = FALSE;
		tCommCfg.dcb.fNull = FALSE;

		// Set the new data
		tCommCfg.dcb.BaudRate = DWORD(dwBaud);
		tCommCfg.dcb.ByteSize = BYTE(m_nDataBits);
		tCommCfg.dcb.Parity   = BYTE(byParity);
		tCommCfg.dcb.StopBits = BYTE(byStop);

		// Determine if parity is used
		tCommCfg.dcb.fParity  = DWORD(m_eParity != PAR_NONE);

		// Set the handshaking flags
		switch (m_eFlow)
		{
		case FLOW_OFF:
			tCommCfg.dcb.fOutxCtsFlow = false;					// Disable CTS monitoring
			tCommCfg.dcb.fOutxDsrFlow = false;					// Disable DSR monitoring
			tCommCfg.dcb.fDtrControl = DTR_CONTROL_DISABLE;		// Disable DTR monitoring
			tCommCfg.dcb.fOutX = false;							// Disable XON/XOFF for transmission
			tCommCfg.dcb.fInX = false;							// Disable XON/XOFF for receiving
			tCommCfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
			break;

		case FLOW_HARDWARE:
			tCommCfg.dcb.fOutxCtsFlow = true;					// Enable CTS monitoring
			tCommCfg.dcb.fOutxDsrFlow = true;					// Enable DSR monitoring
			tCommCfg.dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;	// Enable DTR handshaking
			tCommCfg.dcb.fOutX = false;							// Disable XON/XOFF for transmission
			tCommCfg.dcb.fInX = false;							// Disable XON/XOFF for receiving
			tCommCfg.dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;	// Enable RTS handshaking
			break;

		case FLOW_XONXOFF:
			tCommCfg.dcb.fOutxCtsFlow = false;					// Disable CTS (Clear To Send)
			tCommCfg.dcb.fOutxDsrFlow = false;					// Disable DSR (Data Set Ready)
			tCommCfg.dcb.fDtrControl = DTR_CONTROL_DISABLE;		// Disable DTR (Data Terminal Ready)
			tCommCfg.dcb.fOutX = true;							// Enable XON/XOFF for transmission
			tCommCfg.dcb.fInX = true;							// Enable XON/XOFF for receiving
			tCommCfg.dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
			break;

		default:
			break;
		}

#if ! defined( OS_MSWIN_WCE )
		// NEEDS_WORK: find WinCE solution

		// Set the new Config structure
		if ( ! ::SetCommConfig( m_nFD, &tCommCfg, sizeof(tCommCfg) ) )
		{
			// Obtain the error code
			nr = m_nLastError = GetLastOSError();

			// Display a warning
			LogPrint("CSerial::Setup - Unable to set Config information\n");
			break;
		}

#endif





		// Determine the time-outs
		COMMTIMEOUTS cto;
		if (!::GetCommTimeouts(m_nFD,&cto))
		{
			// Obtain the error code
			nr = GetLastOSError();

			// Display a warning
			LogPrint("CSerial::SetupReadTimeouts - Unable to obtain timeout information\n");
			break;
		}



		// Set the new timeouts
		if ( m_bNonblocking )
		{
			cto.ReadIntervalTimeout = MAXDWORD;
			cto.ReadTotalTimeoutConstant = m_nTimeout;
			cto.ReadTotalTimeoutMultiplier = 0;

			cto.WriteTotalTimeoutConstant = m_nTimeout;
			cto.WriteTotalTimeoutMultiplier = 0;
		}
		else
		{
			cto.ReadIntervalTimeout = 20;
			cto.ReadTotalTimeoutMultiplier = 20;
			cto.ReadTotalTimeoutConstant = m_nTimeout;

			cto.WriteTotalTimeoutConstant = m_nTimeout;
			cto.WriteTotalTimeoutMultiplier = 20;
		}

		// Set the new DCB structure
		if (!::SetCommTimeouts(m_nFD,&cto))
		{
			// Obtain the error code
			nr = GetLastOSError();

			// Display a warning
			LogPrint("CSerial::SetupReadTimeouts - Unable to set timeout information\n");
			break;
		}



		nr = NR_S_SUCCESS;

	}

	if ( NR_FAILED(nr) )
	{
		Close();
		m_nLastError = nr;
	}


#endif

	return nr;
}


/*---------------------------------------------------------------------+\

 * Close -

\+---------------------------------------------------------------------*/
NResult	CSerial::Close
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;

	CMutexLocker	lock( &m_oMutex );

#if defined( SERIAL_POSIX )

	if ( 0 < m_nFD )
	{
		close( m_nFD );
	}
	else
	{
		nr = NR_E_HANDLE;
	}
	m_nFD = 0;

#elif defined( SERIAL_WINDOWS )

	if ( m_nFD )
	{
#if ! defined( OS_MSWIN_WCE )
		// NEEDS_WORK: find WinCE solution
		::CancelIo( m_nFD );
#endif
		::CloseHandle( m_nFD );
		m_nFD = 0;
	}
	else
	{
		nr = NR_E_HANDLE;
	}

#endif

	m_nLastError = nr;

	return nr;
}



/*---------------------------------------------------------------------+\

 * Read -

\+---------------------------------------------------------------------*/
size_t	CSerial::Read
		(
		unsigned char*	pBuffer,
		size_t			nMaxBytes
		)
{
	size_t	nBytesRead = 0;

	if ( pBuffer )
	{

#if defined( SERIAL_POSIX )

		if ( 0 < m_nFD )
		{
			LOCAL_PRINT( "CSerial::Read[%0X] - ReadFile start\n", m_nFD );
			if( m_bNonblocking )
			{
				struct timeval tv;
				//FIXME add param to xml
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				FD_SET(m_nFD, &m_fdsRead);

				int retval = select((m_nFD + 1), &m_fdsRead, NULL, NULL, &tv);

				if (retval <= 0)
				{
					LOCAL_PRINT("CSerial::Read, non blocking select timeout.\n");
					return(0);
				}
			}

			nBytesRead = read( m_nFD, pBuffer, nMaxBytes );
			LOCAL_PRINT("CSerial::Read[%0X] - nBytesRead = %d, max = %d, errno = %0X\n",
					 m_nFD, nBytesRead, nMaxBytes, errno );
			if ( nBytesRead < 0 )
			{
				GetLastOSError();
				nBytesRead = 0;
			}
		}
		else
		{
			LogPrint("CSerial::Read:ERROR - NULL file descriptor (%p) or data buffer pointer (%p)\n",
					 m_nFD, pBuffer );
		}

#elif defined( SERIAL_WINDOWS )

		if ( m_nFD )
		{
			DWORD	nRead;

			LOCAL_PRINT( "CSerial::Read[%0X] - ReadFile start\n", m_nFD );

			OVERLAPPED	tOV = { 0 };

			tOV.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
			if ( tOV.hEvent )
			{
				if ( ! ReadFile( m_nFD, pBuffer, DWORD(nMaxBytes), &nRead, &tOV ) )
				{
					if ( ERROR_IO_PENDING != GetLastError() )
					{
						GetLastOSError();
						nBytesRead = 0;
					}
					else
					{
#if ! defined( OS_MSWIN_WCE )
						// NEEDS_WORK: find WinCE solution
						// we need to wait
						if ( GetOverlappedResult( m_nFD, &tOV, &nRead, TRUE ) )
							nBytesRead = nRead;
						else
							nBytesRead = 0;
#else
						nBytesRead = 0;
#endif
					}
				}
				else
				{
					// read completed immediately
					nBytesRead = nRead;
				}

				CloseHandle( tOV.hEvent );
			}

			LOCAL_PRINT( "CSerial::Read[%0X] - ReadFile finish\n", m_nFD );
		}


#endif
	}

	return nBytesRead;
}



/*---------------------------------------------------------------------+\

 * Write -

\+---------------------------------------------------------------------*/
size_t	CSerial::Write
		(
		const unsigned char* pBuffer,
		size_t				nCount
		)
{
	size_t	nBytesWritten = 0;

	if ( pBuffer  &&  0 < nCount )
	{

		//CMutexLocker	lock( &m_oMutex );

#if defined( SERIAL_POSIX )

		if ( 0 < m_nFD )
		{
			LOCAL_PRINT( "CSerial::Write[%0X] - WriteFile start\n", m_nFD );
			nBytesWritten = write( m_nFD, pBuffer, nCount );
			LOCAL_PRINT("CSerial::Write[%0X] - nBytesWritten = %d\n",
					 m_nFD, nBytesWritten);
		}
		else
		{
			LogPrint("CSerial::Write:ERROR - NULL file descriptor (%p) or data buffer pointer (%p)\n",
					 m_nFD, pBuffer );
		}


#elif defined( SERIAL_WINDOWS )

		if ( m_nFD )
		{
			DWORD	nWritten;
			OVERLAPPED	tOV = { 0 };

			LOCAL_PRINT( "CSerial::Write[%0X] - WriteFile start\n", m_nFD );


			tOV.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
			if ( tOV.hEvent )
			{

				if ( ! ::WriteFile( m_nFD, pBuffer, DWORD(nCount), &nWritten, &tOV ) )
				{
					if ( ERROR_IO_PENDING == GetLastError() )
					{
#if ! defined( OS_MSWIN_WCE )
						// NEEDS_WORK: find WinCE solution
						// we need to wait for the I/O to complete
						if ( GetOverlappedResult( m_nFD, &tOV, &nWritten, TRUE ) )
							nBytesWritten = nWritten;
						else
							nBytesWritten = 0;
#else
						nBytesWritten = 0;
#endif
					}
					else
					{
						GetLastOSError();
						nBytesWritten = 0;
						LogPrint( "CSerial::Write - Unable to write data\n" );
					}
				}
				else
				{
					// write completed immediately
					nBytesWritten = nWritten;
				}

				CloseHandle( tOV.hEvent );


			}
			LOCAL_PRINT( "CSerial::Write[%0X] - WriteFile finish written=%ld\n", m_nFD, nBytesWritten );
		}

#endif
	}

	return nBytesWritten;
}


/*---------------------------------------------------------------------+\

 * Write -

\+---------------------------------------------------------------------*/
size_t	CSerial::Write
		(
		ConstCCharDescriptorRef rString
		)
{
	size_t	nBytesWritten = 0;

	if ( 0 < rString.Length() )
	{
		nBytesWritten = Write( (const unsigned char*)rString.Pointer(), rString.Length() );
	}

	return nBytesWritten;
}


/*---------------------------------------------------------------------+\

 * Flush -

\+---------------------------------------------------------------------*/
NResult	CSerial::Flush
		(
		void
		)
{
	//CMutexLocker	lock( &m_oMutex );

#if defined( SERIAL_POSIX )
	tcflush(m_nFD, TCOFLUSH);
	tcflush(m_nFD, TCIFLUSH);
#elif defined( SERIAL_WINDOWS )

	if ( IsOpen() )
	{
		FlushFileBuffers( m_nFD );
	}
#endif

	return NR_S_SUCCESS;
}

/*---------------------------------------------------------------------+\

 * IsOpen -

\+---------------------------------------------------------------------*/
bool	CSerial::IsOpen
		(
		void
		)
{
#if defined( SERIAL_POSIX )
	return 0 < m_nFD;
#elif defined( SERIAL_WINDOWS )
	return 0 != m_nFD;
#endif
}


/*---------------------------------------------------------------------+\

 * AvailableBytes - how many bytes are available for read

\+---------------------------------------------------------------------*/
size_t	CSerial::AvailableBytes
		(
		void
		)
{
	size_t	nResult = 0;

#if defined( SERIAL_POSIX )

	if ( m_nFD )
	{
		ioctl( m_nFD, FIONREAD, &nResult );
		//DbgPrint( "\nCSerial::AvailBytes = %ld\n\n", nResult );
	}

#elif defined( SERIAL_WINDOWS )

	//CMutexLocker	lock( &m_oMutex );

	if ( IsOpen() )
	{
		DWORD	mErrors;
		COMSTAT	tComStat;
		if ( ::ClearCommError( m_nFD, &mErrors, &tComStat ) )
		{
			m_nLastError = NR_S_SUCCESS;
			nResult = tComStat.cbInQue;
		}
		else
		{
			nResult =  0;
		}
	}

#endif

	return nResult;
}


/*---------------------------------------------------------------------+\

 * LastError -

\+---------------------------------------------------------------------*/
NResult	CSerial::LastError
		(
		void
		)
{
	//CMutexLocker	lock( &m_oMutex );
	return m_nLastError;
}


/*---------------------------------------------------------------------+\

 * CheckPort -

\+---------------------------------------------------------------------*/
//static
bool	CSerial::CheckPort
		(
		const char*	//sName
		)
{
	return true;
}


/*---------------------------------------------------------------------+\

 * enumLinuxPorts -

\+---------------------------------------------------------------------*/
#if 0
//static
bool	CSerial::enumLinuxPorts
		(
		StringArray*	pList,
		const char*		sFile,
		const char*		sPrefix
		)
{
	bool	bResult = false;
	FILE*	nFD;
	char	sLine[128];
	long	nLen;
	long	nParseCount;
	long	nPort;

	nFD = fopen( sFile, "r" );
	if ( nFD )
	{
		while ( fgets( sLine, sizeof(sLine)-1, nFD ) )
		{
			nLen = strlen( sLine );
			nPort = ParseInt( sLine, nLen, &nParseCount );
			if ( 0 < nParseCount  &&  -1 < nPort )
			{
				if ( ':' == sLine[nParseCount]  &&  ' ' == sLine[nParseCount+1] )
				{
					if ( strstr( sLine, "port:" ) )
					{
						CCharString	sPort;

						sPort.Format( "/dev/tty%s%d", sPrefix, nPort );
						pList->AppendData( &sPort );
						bResult = true;
					}
				}
			}
		}
		if ( ! feof( nFD ) )
			bResult = false;
		fclose( nFD );
	}
	else
	{
		LOCAL_PRINT( "unable to open file = %s\n", sFile );
	}

	return bResult;
}
#endif



/*---------------------------------------------------------------------+\

 * EnumeratePorts - get list of available serial ports

\+---------------------------------------------------------------------*/
//static
NResult	CSerial::EnumeratePorts
		(
		StringArray *pList
		)
{
	NResult	nResult = NR_E_FAIL;

#if defined( SERIAL_POSIX )

	DIR*			pDir;
	struct dirent*	pEntry;

	pDir = opendir( "/dev" );
	if ( pDir )
	{
		while ( NULL != (pEntry = readdir( pDir ) ) )
		{
			char*	s = pEntry->d_name;
			if ( 0 == strncmp( s, "tty", 3 ) )
			{
				char	c = tolower(s[3]);
				if ( 'a' <= c  &&  c <= 'z' )
				{
					CCharString	sPort;
					sPort.Format( "/dev/%s", s );
					int	fd = open( sPort.Pointer(), O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY );
					if ( 0 < fd )
					{
						struct serial_struct tSerInfo;
						if ( 0 <= ioctl( fd, TIOCGSERIAL, &tSerInfo ))
						{
							LOCAL_PRINT( "%s  port=%d, type=%d, line=%d, irq=%d, flags=%0X, io_type=%d, xmit_fifo_size=%d\n",
										sPort.Pointer(),
										tSerInfo.port, tSerInfo.type, tSerInfo.line, tSerInfo.irq, tSerInfo.flags, (int)tSerInfo.io_type, tSerInfo.xmit_fifo_size );
							bool	bUse = false;
							if ( tSerInfo.irq )
							{
								if ( 0 < tSerInfo.type )
									bUse = true;
							}
							else
							{
								bUse = true;
							}
							if ( bUse )
							{
								pList->AppendData( &sPort );
								nResult = NR_S_SUCCESS;
							}
						}
						else
						{
							DbgPrint( "%s -- problem ioctl device\n", sPort.Pointer() );
							DbgPrint( "%s\n", strerror( errno ) );
							pList->AppendData( &sPort );
						}
						close( fd );
					}
					else
					{
						DbgPrint( "%s -- problem opening device\n", sPort.Pointer() );
						DbgPrint( "%s\n", strerror( errno ) );
					}
				}
			}
		}
		closedir( pDir );
		pList->Sort();
	}




#elif defined( SERIAL_WINDOWS )

	HKEY	hSerialComm;
	LONG	nQResult = 0;


	nQResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
							__T("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
							0, KEY_QUERY_VALUE, &hSerialComm );

	if ( ERROR_SUCCESS == nQResult )
	{
		// get the max value name and max value lengths
		DWORD	nMaxNameLen;
		DWORD	nMaxValueLen;

		nQResult = RegQueryInfoKey( hSerialComm,
						NULL, NULL, NULL, NULL, NULL, NULL, NULL,
						&nMaxNameLen, &nMaxValueLen, NULL, NULL );

		if ( ERROR_SUCCESS == nQResult )
		{
			char*	sName = 0;
			char*	sValue = 0;
			DWORD	nIndex = 0;
			DWORD	nType;
			LONG	nEnum;
			DWORD	nNameSize;
			DWORD	nValueSize;
			CCharString	sPort;

			if ( nMaxNameLen < 128 )
				nMaxNameLen = 128;
			if ( nMaxValueLen < 128 )
				nMaxValueLen = 128;

			sName = new char[nMaxNameLen+1];
			sValue = new char[nMaxValueLen+1];

#	if defined( OS_MSWIN_WCE )
			TArrayPointer<WCHAR>	wsName;
			TArrayPointer<WCHAR>	wsValue;
			wsName = new WCHAR[nMaxNameLen+1];
			wsValue = new WCHAR[nMaxValueLen+1];
#	endif

			nEnum = ERROR_SUCCESS;
			nIndex = 0;
			do
			{
				::memset( sName, 0, nMaxNameLen+1 );
				::memset( sValue, 0, nMaxValueLen+1 );
				nNameSize = nMaxNameLen;
				nValueSize = nMaxValueLen;

#	if defined( OS_MSWIN_WCE )
				nEnum = RegEnumValue( hSerialComm, nIndex,
									wsName, &nNameSize,
									NULL, &nType,
									(LPBYTE)(WCHAR*)wsValue, &nValueSize );
#	else
				nEnum = RegEnumValueA( hSerialComm, nIndex,
									sName, &nNameSize,
									NULL, &nType,
									(LPBYTE)sValue, &nValueSize );
#	endif
				if ( ERROR_SUCCESS == nEnum )
				{
					// if the value is the correct type, then add it
					if ( REG_SZ == nType )
					{
#	if defined( OS_MSWIN_WCE )
						::WideCharToMultiByte( CP_ACP, 0, wsValue, nValueSize, sValue, nMaxValueLen, NULL, NULL );
#	endif
						sPort = sValue;
						pList->AppendData( &sPort );
						nResult = NR_S_SUCCESS;
					}
				}
				++nIndex;
			} while ( ERROR_SUCCESS == nEnum );

			delete [] sName;
			delete [] sValue;

			::RegCloseKey( hSerialComm );
		}
	}

	pList->Sort();


#endif

	return nResult;
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * GetLastOSError - translate OS error# to NResult

\+---------------------------------------------------------------------*/
NResult	CSerial::GetLastOSError
		(
		void
		)
{
	NResult	nr = NR_E_ERROR;

#if defined( SERIAL_POSIX )

	errno_t	n = errno;
	if ( 0 == n )
	{
		nr = NR_S_SUCCESS;
	}
	else
	{
		DbgPrint( "%s\n",::strerror(n));
		nr = NR_E_ERROR;
		switch ( n )
		{
		case ENOENT:
			nr = NR_E_FILENOTFOUND;
			break;
		case EIO:
			nr = NR_E_IO;
			break;
		case EBADF:
			nr = NR_E_HANDLE;
			break;
		default:
			break;
		}
	}

#elif defined( SERIAL_WINDOWS )

	// todo: we need to add a translation table
	unsigned long	n = ::GetLastError();
	switch ( n )
	{
	case ERROR_SUCCESS:
		nr = NR_S_SUCCESS;
		break;
	case ERROR_INVALID_FUNCTION:
		nr = NR_E_INVALIDFUNCTION;
		break;
	case ERROR_FILE_NOT_FOUND:
		nr = NR_E_FILENOTFOUND;
		break;
	case ERROR_ACCESS_DENIED:
		nr = NR_E_ACCESSDENIED;
		break;
	case ERROR_INVALID_HANDLE:
		nr = NR_E_HANDLE;
		break;
	default:
		nr = NR_E_ERROR;
		break;
	}

#endif

	m_nLastError = nr;

	return nr;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_ROOT_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

