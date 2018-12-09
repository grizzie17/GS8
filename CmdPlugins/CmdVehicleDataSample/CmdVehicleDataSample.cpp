/*---------------------------------------------------------------------+\
|
|	CmdVehicleDataSample.cpp  --  Plugin to activate sample vehicle data
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
#include "CmdVehicleDataSample.h"

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
namespace Yogi { namespace Gadget {
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
PLUGIN_CREATE_FACTORY( CmdVehicleDataSample );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdVehicleDataSample - constructor

\+---------------------------------------------------------------------*/
CmdVehicleDataSample::CmdVehicleDataSample
		(
		void
		)
		: inherited(),
		m_sServiceName(),
		m_pIVDS( 0 )
{
}

CmdVehicleDataSample::CmdVehicleDataSample
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sServiceName(),
		m_pIVDS( 0 )
{
}

CmdVehicleDataSample::CmdVehicleDataSample
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sServiceName(),
		m_pIVDS( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CmdVehicleDataSample - destructor

\+---------------------------------------------------------------------*/
CmdVehicleDataSample::~CmdVehicleDataSample
		(
		void
		)
{

	if ( m_pIVDS )
		m_pIVDS->Release();
	m_pIVDS = 0;
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
bool	CmdVehicleDataSample::cmdStart
		(
		ConstCVariantDataRef	//r
		)
{
	if ( m_pIVDS )
		m_pIVDS->StartDataFlow();

	return true;
}


/*---------------------------------------------------------------------+\

 * cmdStop -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataSample::cmdStop
		(
		ConstCVariantDataRef	//r
		)
{
	if ( m_pIVDS )
		m_pIVDS->StopDataFlow();

	return true;
}



/*---------------------------------------------------------------------+\

 * cmdToggle -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataSample::cmdToggle
		(
		ConstCVariantDataRef	//r
		)
{

	if ( m_pIVDS )
		m_pIVDS->ToggleDataFlow();

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
bool	CmdVehicleDataSample::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	bool	bResult;
	bResult = VPluginCommand::Initialize( pApplication, pCommandSetup );

	if ( bResult )
	{

		m_nCmdStart = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE START" );
		m_nCmdStop = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE STOP" );
		m_nCmdToggle = pCommandSetup->RegisterCommand( "VEHICLE SAMPLE TOGGLE" );
		m_nCmdToggleLegacy = pCommandSetup->RegisterCommand( "Toggle Loader" );


		CServiceManagerPtr	pSvcMgr = (CServiceManagerPtr)pApplication->FindObject( "ServiceManager" );
		if ( pSvcMgr )
		{
			m_pIVDS = (IVehicleDataSamplePtr)pSvcMgr->FindServiceByIF( IXID_IVehicleDataSample );
			if ( m_pIVDS )
			{
				IDictionaryUserPtr	pIDict = QI_( m_pIVDS, IDictionaryUser );
				if ( pIDict )
				{
					pIDict->SetDictionary( m_pApplication->Dictionary() );
					pIDict->Release();
				}
			}
			else
			{
				LogPrint( "Unable to retrieve VehicleDataSample I/F\n" );
			}
		}
		else
		{
			LogPrint( "Unable to find ServiceManager for VehicleDataSample command\n" );
			bResult = false;
		}
	}


	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdVehicleDataSample::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	bool	bResult = true;
	if ( selCommand == m_nCmdStart )
		bResult = cmdStart( vData );
	else if ( selCommand == m_nCmdStop )
		bResult = cmdStop( vData );
	else if ( selCommand == m_nCmdToggle )
		bResult = cmdToggle( vData );
	else if ( selCommand == m_nCmdToggleLegacy )
		bResult = cmdToggle( vData );
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
bool	CmdVehicleDataSample::Load
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



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
