/*---------------------------------------------------------------------+\
|
|	CServiceVehicleSocket.cpp  --  brief description of what CServiceVehicleSocket.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <limits.h>

#include "CServiceVehicleSocket.h"

#include "VPluginFactory.h"

#include "UPlatformTime.h"

namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define	RECORD_XML


#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
//#define	LOCAL_PRINT( fmt, ... )

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
const char xmlHdr[]		=	"<?xml";
const char xmlRoot[]	=	"<VehicleData";
const char xmlRootEnd[]	=	"</VehicleData>";
const char xmlData[]	=	"<Parameters";
const char xmlDataEnd[]	=	"</Parameters>";



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
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( CServiceVehicleSocket );






/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CServiceVehicleSocket - constructor

\+---------------------------------------------------------------------*/
CServiceVehicleSocket::CServiceVehicleSocket
		(
		void
		)
		: inherited(),
		m_oMutex(),
		m_pSocket( 0 ),
		m_sMCAddress(),
		m_nMCPort( 0 ),
		m_pRxThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( 0 ),
		m_nMCTimeOut( 0 ),
		m_nMCMaxMsgSize( 1024 * 3 )
{
}

CServiceVehicleSocket::CServiceVehicleSocket
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_oMutex(),
		m_pSocket( 0 ),
		m_sMCAddress(),
		m_nMCPort( 0 ),
		m_pRxThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( 0 ),
		m_nMCTimeOut( 0 ),
		m_nMCMaxMsgSize( 1024 * 3 )
{
}

CServiceVehicleSocket::CServiceVehicleSocket
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_oMutex(),
		m_pSocket( 0 ),
		m_sMCAddress(),
		m_nMCPort( 0 ),
		m_pRxThread( 0 ),
		m_nSequence( 0 ),
		m_bInitDone( 0 ),
		m_nMCTimeOut( 0 ),
		m_nMCMaxMsgSize( 1024 * 3 )
{
//	memset(&gVDMsgs,0,sizeof(gVDMsgs));
}

/*---------------------------------------------------------------------+\

 * ~CServiceVehicleSocket - destructor

\+---------------------------------------------------------------------*/
CServiceVehicleSocket::~CServiceVehicleSocket
		(
		void
		)
{
	if ( m_pRxThread )
		ThreadClose( m_pRxThread );

	if ( m_pSocket )
		delete m_pSocket;


}

/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/


/*---------------------------------------------------------------------+\
|	 IActiveXML
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * RegisterXMLClient -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleSocket::RegisterXMLClient
		(
		IActiveXMLClientPtr	p
		)
{
	CMutexLocker	lock( &m_oMutex );
	LOCAL_PRINT( "RegisterXMLClient = %p\n", p );

	m_aClients.AppendData( &p );
	return NR_S_SUCCESS;
}



/*---------------------------------------------------------------------+\

 * FetchXMLData -

\+---------------------------------------------------------------------*/
int		CServiceVehicleSocket::FetchXMLData
		(					// RTN:	ID used for releasing buffer
		char**	hBuffer,	// OUT:	address of buffer
		size_t*	pnSize,		// OUT:	number of bytes in buffer
		size_t*	pnSequence	// OUT: sequence identifier
		)
{
	CMutexLocker	lock( &m_oMutex );

	size_t	nTopSeq = 0;
	DBuf*	pTopBuf = 0;

	DBuf*	p = m_aBuffers.PointArray();
	DBuf*	pBase = p;
	DBuf*	pEnd = p + m_aBuffers.Length();

	while ( p < pEnd )
	{
		if ( 0 < p->nSize )
		{
			if ( nTopSeq < p->nSequence )
			{
				nTopSeq = p->nSequence;
				pTopBuf = p;
			}
		}
		++p;
	}

	if ( pTopBuf )
	{
		pTopBuf->nUsers++;
		*hBuffer = pTopBuf->pBuffer;
		*pnSize = pTopBuf->nSize;
		*pnSequence = pTopBuf->nSequence;
		return int(pTopBuf - pBase);
	}
	else
	{
		return -1;
	}
}


/*---------------------------------------------------------------------+\

 * ReleaseXMLData -

\+---------------------------------------------------------------------*/
void	CServiceVehicleSocket::ReleaseXMLData
		(
		int		nID			// IN:	id of buffer to release
		)
{
	if ( -1 < nID )
	{
		CMutexLocker	lock( &m_oMutex );
		DBuf*	p = m_aBuffers.PointArray(nID);
		if ( p )
		{
			--p->nUsers;
		}
	}
}




/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * RunGlue - Function to call "Run" from within spawned thread

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceVehicleSocket::RunGlueRx
		(
		void*	pVoid
		)
{
	CServiceVehicleSocketPtr	pThis = (CServiceVehicleSocketPtr)pVoid;

	return pThis->RunRx();
}


/*---------------------------------------------------------------------+\

 * RunRx -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceVehicleSocket::RunRx
		(
		void
		)
{
	size_t dataLen			= 0;

#if defined( _DEBUG )
	char	sPath[1024];

	const char*	s = GetUserConfigFolder();

	PathBuild( sPath, sizeof(sPath), s, "VehicleData.xml" );
#endif


	DBuf*	pCurrent = 0;

	m_nSequence	= 1;

	loop_forever
	{
		if ( m_pSocket )
		{
			pCurrent = GetBufferForRead();
			dataLen = (size_t)m_pSocket->RecvFrom( pCurrent->pBuffer, pCurrent->nAlloc, 0, 0u );
		}
		else
		{
			dataLen = (size_t)NR_E_RX_FAIL;
			DbgPrint( "CServiceVehicleSocket: socket not opened\n" );
		}

		if ( 0 < dataLen )
		{
#if defined( _DEBUG )
#if defined( OS_LINUX )
//			const char	sSpin[] = {"-/|\\"};
//			DbgPrint( "%c\r", sSpin[m_nSequence%strlen(sSpin)] );
#endif
#if defined( RECORD_XML )
			FILE*	pf;

			if ( 0 == fopen_s( &pf, sPath, "w+" ) )
			{
				::fwrite( pCurrent->pBuffer, 1, dataLen, pf );
				fclose( pf );
			}
#endif
#endif
			m_oMutex.Lock();
			++m_nSequence;
			pCurrent->nSize = dataLen;
			pCurrent->nSequence = m_nSequence;
			m_oMutex.Unlock();
			NotifyClients();
		}
		else if ( (size_t)NR_E_BUFFER_OVERRUN == dataLen )
		{
			GrowBuffer( pCurrent );
		}
		else
		{
			if ( m_pSocket )
				delete m_pSocket;
			m_pSocket = 0;
			OpenMulticastSocket();
		}


	}


	return (UThreadRtn)0;
}



/*---------------------------------------------------------------------+\

 * OpenMulticastSocket -

\+---------------------------------------------------------------------*/
bool	CServiceVehicleSocket::OpenMulticastSocket
		(
		void
		)
{
	bool	bResult = false;

	do_sequence
	{
		if ( m_pSocket )
			break;

		if ( 0 == m_nMCPort )
			break;

		if ( m_sMCAddress.Length() < 8 )
			break;

		m_pSocket = new CSocketUDP( m_nMCPort, true );
		if ( ! m_pSocket )
			break;

		m_pSocket->JoinGroup( m_sMCAddress );
		if ( 0 != m_pSocket->LastError() )
			break;

		DbgPrint( "CServiceVehicleSocket::OpenMulticastSocket - joined multicast group\n" );

		bResult = true;
	}

	if ( ! bResult )
	{
		if ( m_pSocket )
			delete m_pSocket;
		m_pSocket = 0;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetBufferForRead -

\+---------------------------------------------------------------------*/
CServiceVehicleSocket::DBuf*
		CServiceVehicleSocket::GetBufferForRead
		(
		void
		)
{
	DBuf*	pFound = 0;

	pFound = FindIdleBuffer();
	if ( ! pFound )
	{
		if ( 1 < m_aBuffers.Length() )
		{
			DbgPrint( "GetBufferForRead::retrying to find idle buffer\n"  );
			for ( int i = 0; i < 3; ++i )
			{
				millisleep( 100 );
				pFound = FindIdleBuffer();
				if ( pFound )
					break;
			}
		}
		if ( ! pFound )
		{
			CMutexLocker	lock( &m_oMutex );

			DBuf	buf;

			index_t n = m_aBuffers.AppendData( &buf );
			pFound = m_aBuffers.PointArray( n );
			pFound->pBuffer = new char[m_nMCMaxMsgSize];
			pFound->nAlloc = m_nMCMaxMsgSize;
			pFound->nSequence = 0;
			pFound->nUsers = 0;
			pFound->nSize = 0;
			DbgPrint("GetBufferForRead::Added buffers: new count = %ld\n", m_aBuffers.Length());
		}
	}

	return pFound;
}

/*---------------------------------------------------------------------+\

 * FindIdleBuffer -

\+---------------------------------------------------------------------*/
CServiceVehicleSocket::DBuf*
		CServiceVehicleSocket::FindIdleBuffer
		(
		void
		)
{
	DBuf*	pFound = 0;

	CMutexLocker	lock( &m_oMutex );

	size_t	nSeq = m_nSequence;
	DBuf*	p = m_aBuffers.PointArray();
	DBuf*	pEnd = p + m_aBuffers.Length();

	while ( p < pEnd )
	{
		if ( p->nUsers < 1 )
		{
			if ( p->nSequence < nSeq )
			{
				nSeq = p->nSequence;
				pFound = p;
			}
		}
		++p;
	}

	if ( pFound )
	{
		pFound->nUsers = 0;
		pFound->nSize = 0;
	}

	return pFound;
}


/*---------------------------------------------------------------------+\

 * GrowBuffer -

\+---------------------------------------------------------------------*/
void	CServiceVehicleSocket::GrowBuffer
		(
		DBuf*	p
		)
{
	CMutexLocker	lock( &m_oMutex );
	delete [] p->pBuffer;
	size_t	nNewSize = p->nAlloc + p->nAlloc / 2;
	DbgPrint( "GrowBuffer - new size = %ld\n", nNewSize );
	p->pBuffer = new char[nNewSize];
	p->nAlloc = nNewSize;
	p->nSize = 0;
	p->nUsers = 0;
	p->nSequence = 0;
}



/*---------------------------------------------------------------------+\

 * NotifyClients -

\+---------------------------------------------------------------------*/
void	CServiceVehicleSocket::NotifyClients
		(
		void
		)
{
	//DbgPrint( "CServiceVehicleSocket::NotifyClients = %ld\n", m_aClients.Length() );
	if ( 0 < m_aClients.Length() )
	{
		//CMutexLocker	lock( &m_oMutex );
		IActiveXMLClientPtr*	h = m_aClients.PointArray();
		if ( h )
		{
			IActiveXMLClientPtr*	hEnd = h + m_aClients.Length();
			while ( h < hEnd )
			{
				if ( *h )
				{
					(*h)->NotifyXMLAvailable();
				}
				++h;
			}
		}
	}
}



/*---------------------------------------------------------------------+\

 * SetMCMaxMsgSize -

\+---------------------------------------------------------------------*/
void	CServiceVehicleSocket::SetMCMaxMsgSize
		(
		int m
		)
{
	if ( 0 < m )
	{
		m_nMCMaxMsgSize = (size_t)m;
	}
}








/*---------------------------------------------------------------------+\

 * MsgIsOk - very basic XML well-form-ed-ness check

\+---------------------------------------------------------------------*/
bool	CServiceVehicleSocket::MsgIsOk
		(
		char* buf,
		unsigned int len
		)
{
	char*	posHdr	= NULL;
	char*	posRoot	= NULL;
	char*	posREnd	= NULL;
	char*	posData = NULL;
	char*	posDEnd = NULL;

	if ( buf == NULL || len < 1 )
		return false;

	buf[len] = 0; // NULL terminate buffer/string

	posHdr = strstr(buf,xmlHdr);
	if (  posHdr == NULL )
	{
		posHdr = buf;	// Maybe no header? Set at first byte, should be == Root
	}

	posRoot = strstr(posHdr,xmlRoot);
	if ( posRoot == NULL )
		return false;

	posData = strstr(posRoot,xmlData);
	if ( posData == NULL )
		return false;

	posDEnd = strstr(posData,xmlDataEnd);
	if ( posDEnd == NULL )
		return false;

	posREnd = strstr(posDEnd,xmlRootEnd);
	if ( posREnd == NULL )
		return false;

	posHdr = strchr(posREnd,'>');
	if ( posHdr == NULL )
		return false;

	++posHdr = 0; // insure any garbage bytes past posREnd does not matter

	return true;
}




/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	VSupports
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CServiceVehicleSocket::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IActiveXML )
			pI = INTERFACE_THIS( IActiveXMLPtr );
		else
			pI = 0;
	}

	return pI;
}




/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Load - Load parameters from XML

\+---------------------------------------------------------------------*/
bool	CServiceVehicleSocket::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{

		m_sMCAddress = pConfig->GetParameterAsString( "Multicast Address", "235.55.55.5" );
		m_nMCPort = (unsigned short)pConfig->GetParameterAsInteger( "Multicast Port", 55555 );

		GFLOAT	f = pConfig->GetParameterAsFloatUnits( "Timeout", "milliseconds", GFLOAT(30* 1000) );

		m_nMCTimeOut = long(f);

		//m_nMCTimeOut = pConfig->GetParameterAsInteger( "Timeout", 30 * 1000 );

		long	n = pConfig->GetParameterAsInteger( "Maximum Message Size", 4 * 1024 );
		SetMCMaxMsgSize( n );

		DbgPrint( "CServiceVehicleSocket::Load - complete\n" );

	}

	m_bRunning = false;

	return bResult;
}




/*---------------------------------------------------------------------+\
|	 IService
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleSocket::Start
		(
		void
		)
{
	NResult	nr = NR_E_NOTHREAD;

	do_sequence
	{
		if ( ! OpenMulticastSocket() )
			break;

		m_bInitDone = true;

		DBuf	buf;
		DBuf*	pFound;
		index_t	n;

		// add some empty buffers
		n = m_aBuffers.AppendData( &buf );
		pFound = m_aBuffers.PointArray( n );
		pFound->pBuffer = new char[m_nMCMaxMsgSize];
		pFound->nAlloc = m_nMCMaxMsgSize;
		pFound->nUsers = 0;
		pFound->nSequence = 0;
		pFound->nSize = 0;

		n = m_aBuffers.AppendData( &buf );
		pFound = m_aBuffers.PointArray( n );
		pFound->pBuffer = new char[m_nMCMaxMsgSize];
		pFound->nAlloc = m_nMCMaxMsgSize;
		pFound->nUsers = 0;
		pFound->nSequence = 0;
		pFound->nSize = 0;




		m_pRxThread = ThreadCreate( (UThreadFunction)RunGlueRx, this );
		if ( m_pRxThread )
		{
			nr = NR_S_SUCCESS;
			m_bRunning = true;
		}
	}

	return nr;

}


/*---------------------------------------------------------------------+\

 * Stop -

\+---------------------------------------------------------------------*/
NResult	CServiceVehicleSocket::Stop
		(
		void
		)
{
	if ( m_pRxThread )
	{
		ThreadClose( m_pRxThread );
		m_pRxThread = 0;
	}

	if ( m_pSocket )
	{
		delete m_pSocket;
		m_pSocket = 0;
	}
	m_bRunning = false;
	return NR_S_SUCCESS;
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
