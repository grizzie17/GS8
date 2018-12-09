/*---------------------------------------------------------------------+\
|
|	CmdSystemShutdown.cpp  --  Plugin to process touch screen points
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
#include "CmdSystemShutdown.h"

#include "UPlatform.h"

#include "VPluginFactory.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

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
PLUGIN_CREATE_FACTORY( CmdSystemShutdown );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdSystemShutdown - constructor

\+---------------------------------------------------------------------*/
CmdSystemShutdown::CmdSystemShutdown
		(
		void
		)
		: VPluginCommand(),
		m_pDictionary( 0 ),
		m_nCmdSystemShutdown( 0 )
{
}

CmdSystemShutdown::CmdSystemShutdown
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner ),
		m_pDictionary( 0 ),
		m_nCmdSystemShutdown( 0 )
{
}

CmdSystemShutdown::CmdSystemShutdown
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner ),
		m_pDictionary( 0 ),
		m_nCmdSystemShutdown( 0 )
{
}



/*---------------------------------------------------------------------+\

 * ~CmdSystemShutdown - destructor

\+---------------------------------------------------------------------*/
CmdSystemShutdown::~CmdSystemShutdown
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


bool	CmdSystemShutdown::Shutdown
		(
		void
		)
{
#if defined( OS_MSWIN )

	HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    BOOL bShutdownInitiated = FALSE;

    // Get a token for this process.

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        // ToDo: print error message?
        return false;
    }

    // Get the LUID for the shutdown privilege.

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;  // one privilege to set
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Get the shutdown privilege for this process.

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
    {
        // ToDo: print error message?
        return false;
    }

    // Shut down the system and force all applications to close.
    bShutdownInitiated = InitiateSystemShutdownEx(NULL, // NULL => shutdown local computer
                                                  NULL, // No dialog message
                                                  0,    // No wait - immediate shutdown
                                                  TRUE, // Apps with unsave changes are force to close
                                                  FALSE, // No reboot after shutdown
                                                  SHTDN_REASON_MAJOR_POWER | SHTDN_REASON_MINOR_POWER_SUPPLY // dwReason - power down

        );

    if (bShutdownInitiated)
    {

        //shutdown was successful
        return true;
    }

#endif

    // ToDo: print error message?
    return false;
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
bool	CmdSystemShutdown::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	m_nCmdSystemShutdown = pCommandSetup->RegisterCommand( m_sID );

	m_pDictionary = m_pApplication->Dictionary();
	if ( m_pDictionary )
	{
	}

	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdSystemShutdown::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	bool	bResult = true;

		Shutdown();

	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdSystemShutdown::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );


	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
