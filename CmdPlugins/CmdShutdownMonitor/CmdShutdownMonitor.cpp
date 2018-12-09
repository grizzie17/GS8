/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CmdShutdownMonitor.cpp  --  Plugin to process touch screen points
|
|	Purpose:
|	File Custodian:		J.Griswold
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
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CmdShutdownMonitor.h"

#include "IExternalMonitor.h"
#include "UPlatform.h"

#include "VPluginFactory.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
USING_NAMESPACE_MONITOR
namespace Yogi { namespace Gadget {


// change the comment below to allow printing of the local information

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
PLUGIN_CREATE_FACTORY( CmdShutdownMonitor );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CmdShutdownMonitor - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
CmdShutdownMonitor::CmdShutdownMonitor
		(
		void
		)
		: VPluginCommand(),
		m_nCmdShutdownMonitor( 0 )
{
}

CmdShutdownMonitor::CmdShutdownMonitor
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner ),
		m_nCmdShutdownMonitor( 0 )
{
}

CmdShutdownMonitor::CmdShutdownMonitor
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner ),
		m_nCmdShutdownMonitor( 0 )
{
}



/**--------------------------------------------------------------------+\

 * <summary>~CmdShutdownMonitor - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
CmdShutdownMonitor::~CmdShutdownMonitor
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

/**--------------------------------------------------------------------+\

 * <summary>Initialize - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
bool	CmdShutdownMonitor::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	LOCAL_PRINT("======CmdShutdownMonitor::Initialize: %s\n", m_sID.Pointer());

	m_nCmdShutdownMonitor = pCommandSetup->RegisterCommand( m_sID );

	return true;
}

/**--------------------------------------------------------------------+\

 * <summary>ProcessRequest - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
bool	CmdShutdownMonitor::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	bool	bResult = true;

	ISupportsPtr		pISup;
	IExternalMonitorPtr	pIMon;
	LOCAL_PRINT("======CmdShutdownMonitor::ProcessRequest: %s\n", m_sID.Pointer());

	pISup = m_pApplication->FindCOMObject("Monitor");
	if ( pISup )
	{
		pIMon = QI_( pISup, IExternalMonitor );
		if ( pIMon )
		{
			pIMon->Shutdown();
			pIMon->Release();
		}
		pISup->Release();
	}
	else
	{
		LOCAL_PRINT( "CmdShutdownMonitor-- Monitor not found\n");
	}


	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/**--------------------------------------------------------------------+\

 * <summary>Load - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
bool	CmdShutdownMonitor::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );

	LOCAL_PRINT("======CmdShutdownMonitor::Load: %s\n", m_sID.Pointer());

	return bResult;
}



}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  18-Jul-2010

\+---------------------------------------------------------------------*/
