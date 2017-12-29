/*---------------------------------------------------------------------+\
|
|	CmdServiceClog.cpp  --  Plugin to activate sample vehicle data
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
#include "CmdServiceClog.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "CApplicationGauge.h"
#include "CScreen.h"
#include "CGauge.h"
#include "CFactoryPanel.h"
#include "CFactoryGauge.h"
#include "CSerial.h"
#include "CServiceManager.h"
#include "IDictionaryUser.h"

#include "VPluginFactory.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
//#define	LOCAL_PRINT( fmt, ... )


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
PLUGIN_CREATE_FACTORY( CmdServiceClog );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdServiceClog - constructor

\+---------------------------------------------------------------------*/
CmdServiceClog::CmdServiceClog
		(
		void
		)
		: inherited(),
		m_sServiceName()
{
}

CmdServiceClog::CmdServiceClog
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sServiceName()
{
}

CmdServiceClog::CmdServiceClog
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sServiceName()
{
}



/*---------------------------------------------------------------------+\

 * ~CmdServiceClog - destructor

\+---------------------------------------------------------------------*/
CmdServiceClog::~CmdServiceClog
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * cmdStart -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::cmdStart
		(
		ConstCVariantDataRef	//r
		)
{

	return true;
}


/*---------------------------------------------------------------------+\

 * cmdStop -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::cmdStop
		(
		ConstCVariantDataRef	//r
		)
{
	return true;
}



/*---------------------------------------------------------------------+\

 * cmdToggle -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::cmdToggle
		(
		ConstCVariantDataRef	//r
		)
{

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
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	bool	bResult = true;
	bResult = VPluginCommand::Initialize( pApplication, pCommandSetup );

	if ( bResult )
	{

		//m_nCmdStart = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE START" );
		//m_nCmdStop = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE STOP" );
		//m_nCmdToggle = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE TOGGLE" );
		//m_nCmdToggleLegacy = pCommandSetup->RegisterCommand( "Toggle Loader" );


		CServiceManagerPtr	pSvcMgr = (CServiceManagerPtr)pApplication->FindObject( "ServiceManager" );
		if ( pSvcMgr )
		{
			long	n = 0;

			loop_forever
			{
				CCharString	sClog;
				sClog.Format("Clog%ld", n );
				++n;

				ISupportsPtr	pI = (ISupportsPtr)pSvcMgr->FindServiceByName( sClog.Pointer() );
				if ( pI )
				{
					IDictionaryUserPtr	pIDict = QI_( pI, IDictionaryUser );
					if ( pIDict )
					{
						pIDict->SetDictionary( m_pApplication->Dictionary() );
						pIDict->Release();
					}
					pI->Release();
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			LogPrint( "Unable to find ServiceManager for ServiceClog command\n" );
			bResult = false;
		}
	}


	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	return false;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdServiceClog::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );

	if ( bResult )
	{

		m_sServiceName = pConfig->GetParameterAsString( "Service Name", "Vehicle Data Sample" );



	}


	return bResult;
}



NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

