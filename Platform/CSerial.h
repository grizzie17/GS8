/*---------------------------------------------------------------------+\
|
|	CSerial.h  --  class to abstract the details of OS serial-port communication
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
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
#ifndef _H_CSerial
#define _H_CSerial
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"

#if defined( SERIAL_POSIX )

#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#endif


#include "CCharString.h"
#include "TArray.h"
#include "CMutex.h"
#include "UNResult.h"
#include "UDeclPlatform.h"

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#if defined( SERIAL_WINDOWS )
	#ifndef SERIAL_DEFAULT_OVERLAPPED
		#ifndef SERIAL_NO_OVERLAPPED
		#	define SERIAL_DEFAULT_OVERLAPPED	true
		#else
		#	define SERIAL_DEFAULT_OVERLAPPED	false
		#endif
	#endif
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CSerialPortSettings*			CSerialPortSettingsPtr;
typedef class CSerialPortSettings&			CSerialPortSettingsRef;
typedef const class CSerialPortSettings&	ConstCSerialPortSettingsRef;

typedef class CSerial*			CSerialPtr;
typedef class CSerial&			CSerialRef;
typedef const class CSerial&	ConstCSerialRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|	CSerialPortSettings													|
\+---------------------------------------------------------------------*/

class DECL_CLASS CSerialPortSettings
{
//	class lifecycle  ----------------------------------------------------
public:
			CSerialPortSettings();
			CSerialPortSettings( ConstCSerialPortSettingsRef r );	// copy constructor
	virtual	~CSerialPortSettings();

public:
//	public types  -------------------------------------------------------

	typedef enum EParitys
	{
		PAR_NONE,
		PAR_ODD,
		PAR_EVEN,
		PAR_MARK,               //WINDOWS ONLY
		PAR_SPACE
	} EParitys;

	typedef enum EStopBits
	{
		STOP_1,
		STOP_1_5,               //WINDOWS ONLY
		STOP_2
	} EStopBits;

	typedef enum EFlow
	{
		FLOW_OFF,
		FLOW_HARDWARE,
		FLOW_XONXOFF
	} EFlow;

//	public functions  ---------------------------------------------------

	// properties
	void	SetBaud( unsigned long n );
	void	SetDataBits( unsigned int n );
	void	SetParity( EParitys e );
	void	SetStopBits( EStopBits e );
	void	SetHandshaking( EFlow e );


	void	LoadSettings( ConstCSerialPortSettingsRef r );




protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CMutex			m_oMutex;

	unsigned long	m_nBaud;
	unsigned int	m_nDataBits;
	EParitys		m_eParity;
	EStopBits		m_eStopBits;
	EFlow			m_eFlow;

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};



/*---------------------------------------------------------------------+\
|	CSerial
\+---------------------------------------------------------------------*/


class DECL_CLASS CSerial : public CSerialPortSettings
{
//	class lifecycle  ----------------------------------------------------
public:
				CSerial();
				CSerial( ConstCSerialRef r );	// copy constructor
				CSerial( ConstCSerialPortSettingsRef r );
	virtual		~CSerial();

public:
//	public types  -------------------------------------------------------


	typedef TArray<CCharString>	StringArray;


	typedef enum EOpenMode
	{
		MODE_Readonly,
		MODE_Writeonly,
		MODE_ReadWrite
	} EOpenMode;

//	public functions  ---------------------------------------------------

	CSerialRef	operator=( ConstCSerialRef r );		// assignment

	static
	bool	CheckPort( const char* sName );

	static
	NResult	EnumeratePorts( StringArray* pList );

	// properties
	bool	SetPortName( const char* sName );
	const char*	GetPortName( void ) const;
	void	SetMinBytes( long n );
	void	SetTimeout( unsigned long nMilli );
	void	SetNonblocking( bool b );

	NResult	Open( EOpenMode eMode = MODE_Readonly );
	NResult	Close( void );

	size_t	Read( unsigned char* pBuffer, size_t nMaxBytes );
	size_t	Write( const unsigned char* pBuffer, size_t nCount );
	size_t	Write( ConstCCharDescriptorRef rString );
	NResult	Flush( void );

	NResult	LastError( void );

	bool	IsOpen( void );
	size_t	AvailableBytes( void );		// number of bytes available for read

protected:
//	protected types  ----------------------------------------------------

#if defined( SERIAL_POSIX )

	typedef	int		SERIALHDL;

#elif defined( SERIAL_WINDOWS )

	typedef	HANDLE	SERIALHDL;

	// Internal helper class which wraps DCB structure
	class CDCB : public DCB
	{
	public:
		CDCB() { DCBlength = sizeof(DCB); }
	};
#endif

//	protected functions  ------------------------------------------------


	NResult	GetLastOSError( void );



//	protected data  -----------------------------------------------------

	CCharString		m_sPort;
	long			m_nMinBytes;
	unsigned long	m_nTimeout;
	bool			m_bNonblocking;
	NResult			m_nLastError;
	SERIALHDL		m_nFD;			// port descriptor/handle

#if defined( SERIAL_POSIX )

	struct termios	m_tTermOpt;
	struct timeval	m_tv;
	fd_set			m_fdsRead;

#elif defined( SERIAL_WINDOWS )

	LONG	m_lLastError;		// Last serial error
	//EEvent	m_eEvent;			// Event type
	DWORD	m_dwEventMask;		// Event mask
	DWORD	m_dwInQueue;
	DWORD	m_dwOutQueue;

#	ifndef SERIAL_NO_OVERLAPPED
	HANDLE	m_hevtOverlapped;	// Event handle for internal overlapped operations
#	endif

#endif

private:
//	private types  ------------------------------------------------------

	typedef CSerialPortSettings	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_CSerial */
