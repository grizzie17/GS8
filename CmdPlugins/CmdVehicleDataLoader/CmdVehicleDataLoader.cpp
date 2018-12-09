/*---------------------------------------------------------------------+\
|
|	CmdVehicleDataLoader.cpp  --  Plugin to process touch screen points
|
|	Purpose:
|
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
	08-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Major cleanup to protect from generating bogus matrix
	04-Aug-2010			J.Griswold		(Reviewed by: xxxx)
        Fixed overflow problem when calculating touch matrix
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CmdVehicleDataLoader.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformTime.h"
#include "CApplicationGauge.h"
#include "CServiceManager.h"
#include "IDictionaryUser.h"

#include "VPluginFactory.h"
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


#define	DATASVC	1

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
||	 Code																|
||																		|
\+=====================================================================*/
PLUGIN_CREATE_FACTORY( CmdVehicleDataLoader );





/*---------------------------------------------------------------------+\

 * class CVehicleReadCallBack -

\+---------------------------------------------------------------------*/
class CVehicleReadCallBack : public XMLLite::VReadCallBack
{
public:
	CVehicleReadCallBack
		(
		char*	s,
		long	n
		)
		: m_pMsg( s ),
		m_nMsgLen( (size_t)n )
	{}

	virtual
	size_t	Read					// RTN:	returns number of bytes actually read
			(
			void*			pBuffer,		// OUT: buffer to receive data
			size_t			nBytesToRead,	// IN:	number of bytes to read
			XMLLite::ETEXT_FORMAT			// IN:	target format
			)
	{
		size_t	n = nBytesToRead < m_nMsgLen ? nBytesToRead : m_nMsgLen;
		if ( 0 == memcpy_s( pBuffer, nBytesToRead, m_pMsg, n ) )
			return n;
		else
			return 0;
	}

	/*
		Gets the size of the file (stream)
	*/
	virtual
	size_t	GetSize		// RTN:	return file (stream) size in bytes
			(
			void
			)
	{
		return m_nMsgLen;
	}

	/*
		Get a name associated with the call-back stream.
		For files this should be name of the file or
		at least a partial path with name.
	*/
	//BEGIN_OVERRUN_WARNING
	virtual
	size_t	GetName					// RTN:	string length of name
			(
			char*			sTarget,	// OUT:	buffer to receive name
			size_t			nSizeTarget	// IN:	size of target
			)
	{
		char	sName[] = "VehicleData";
		if ( 0 < nSizeTarget )
			strcpy_s( sTarget, nSizeTarget, sName );
		return strlen( sName );
	}
	//END_OVERRUN_WARNING


protected:
	char*	m_pMsg;
	size_t	m_nMsgLen;
};



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdVehicleDataLoader - constructor

\+---------------------------------------------------------------------*/
CmdVehicleDataLoader::CmdVehicleDataLoader
		(
		void
		)
		: inherited(),
		m_pFactory( 0 ),
		m_sServiceName(),
		m_pIActiveXML( 0 ),
		m_nSequence( -1 ),
		m_nLastNotify( 0 )
{
}

CmdVehicleDataLoader::CmdVehicleDataLoader
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_pFactory( 0 ),
		m_sServiceName(),
		m_pIActiveXML( 0 ),
		m_nSequence( -1 ),
		m_nLastNotify( 0 )
{
}

CmdVehicleDataLoader::CmdVehicleDataLoader
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_pFactory( 0 ),
		m_sServiceName(),
		m_pIActiveXML( 0 ),
		m_nSequence( -1 ),
		m_nLastNotify( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CmdVehicleDataLoader - destructor

\+---------------------------------------------------------------------*/
CmdVehicleDataLoader::~CmdVehicleDataLoader
		(
		void
		)
{

	if ( m_pIActiveXML )
		m_pIActiveXML->Release();
	m_pIActiveXML = 0;


	delete m_pFactory;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult	CmdVehicleDataLoader::NotifyXMLAvailable
		(
		void
		)
{
	CVariantData	v = 1L;

	if ( -1 < m_nSequence )
	{
		VDictionaryPtr	pDict = m_pApplication->Dictionary();

		if ( pDict->PutData( m_nCmdLoadData, &v ) )
		{
			long	nMilli = milliseconds();
			//if ( 100 < nMilli - m_nLastNotify )
			{
				m_nLastNotify = nMilli;
				m_pApplication->PostCalculateNeeded();
			}
			//LOCAL_PRINT( "NotifyXMLAvailable into port %ld\n",m_pApplication->GetUserIDNumber());
		}
		else
		{
			LOCAL_PRINT( "NotifyXMLAvailable: post already active\n" );
		}
	}

	return 0;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/










/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataLoader::CmdLoadData
		(
		ConstCVariantDataRef	//rData
		)
{
	int		nID;
	char*	pBuffer;
	size_t	nSize;
	size_t	nSeq;

	nID = m_pIActiveXML->FetchXMLData( &pBuffer, &nSize, &nSeq );

	if ( -1 < nID )
	{
		if ( 0 < nSize  &&  m_nSequence < (index_t)nSeq )	// we have fresh data
		{
			if ( m_nSequence < (index_t)nSeq )
			{
				//LOCAL_PRINT( "seq=%ld\n", nSeq );
				m_nSequence = (index_t)nSeq;
				CVehicleReadCallBack	callback( pBuffer, (long)nSize );
				bool b = m_pFactory->LoadData( &callback );
				if ( ! b )
				{
					LogPrint( "Error processing Vehicle Data - seq = %ld\n", nSeq );
					CCharDescriptor sd;
					CCharString s;
					sd = m_pFactory->ErrorString();
					s = sd;
					LogPrint( "%s\n", s.Pointer());
				}
			}
			else
			{
				LogPrint( "Stale Vehicle Data - nothing processed\n");
			}

		}
		else
		{
			LogPrint( "Empty Vehicle Data - nothing processed\n" );
		}

		m_pIActiveXML->ReleaseXMLData( nID );

		//m_pApplication->PostCalculateNeeded();
	}
	else
	{
		LogPrint( "...no data fetched\n" );
	}
	return true;
}



/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataLoader::CmdLoadInit
		(
		ConstCVariantDataRef	//rData
		)
{
	m_nSequence = 0;
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
void*	CmdVehicleDataLoader::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IActiveXMLClient )
			pI = INTERFACE_THIS( IActiveXMLClientPtr );
		else
			pI = 0;
	}

	return pI;
}





/*---------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataLoader::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	bool	bResult;
	bResult = VPluginCommand::Initialize( pApplication, pCommandSetup );

	LOCAL_PRINT( "CmdVehicleDataLoader::Initialize\n" );

	if ( bResult )
	{
		if ( ! m_pFactory )
			m_pFactory = new CFactoryVehicleData;

		m_pFactory->SpecifyActivePage( m_pApplication->DictPageActive() );
		m_pFactory->SpecifyNotifyPage( m_pApplication->DictPageNotify() );

		m_nCmdLoadData = pCommandSetup->RegisterCommand( "VEHICLE LOAD DATA" );
		m_nCmdLoadInit = pCommandSetup->RegisterCommand( "VEHICLE LOAD INIT" );


		CServiceManagerPtr	pSvcMgr = (CServiceManagerPtr)pApplication->FindObject( "ServiceManager" );
		if ( pSvcMgr )
		{
			m_pIActiveXML = (IActiveXMLPtr)pSvcMgr->FindServiceByIF ( IXID_IActiveXML );
			//ISupportsPtr	pIF
			//		= (ISupportsPtr)pSvcMgr->FindServiceByName( m_sServiceName );
			//if ( pIF )
			//{
			//	m_pIActiveXML = QI_( pIF, IActiveXML );
				if ( m_pIActiveXML )
				{
					m_pIActiveXML->RegisterXMLClient( (IActiveXMLClientPtr)INTERFACE_THIS( IActiveXMLClientPtr ) );

					CVariantData	v = 1L;

					pApplication->Dictionary()->PutData( m_nCmdLoadInit, &v );
					//m_hThread = ThreadCreate( (UThreadFunction)RunGlue, this );
					//if ( ! m_hThread )
					//{
					//	LogPrint( "Unable to start Vehicle Data Loader thread\n" );
					//}
				}
				else
				{
					LogPrint( "Unable to retrieve ActiveXML I/F\n" );
				}
			//	pIF->Release();
			//}
		}
		else
		{
			LogPrint( "Unable to find ServiceManager for VehicleDataLoader command\n" );
			bResult = false;
		}
	}


	return bResult;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataLoader::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	bool	bResult = true;
	if ( selCommand == m_nCmdLoadData )
		bResult = CmdLoadData( vData );
	else if ( selCommand == m_nCmdLoadInit )
		bResult = CmdLoadInit( vData );
	else
		bResult = false;
	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataLoader::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );

	if ( bResult )
	{

		m_sServiceName = pConfig->GetParameterAsString( "Service Name", "Vehicle Data Socket" );



	}


	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
