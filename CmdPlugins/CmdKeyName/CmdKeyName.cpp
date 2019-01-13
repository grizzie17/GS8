/*---------------------------------------------------------------------+\
|
|	CmdKeyName.cpp  --  Plugin to process touch screen points
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
#include "stdafx.h"
#include "CmdKeyName.h"

#include "UPlatform.h"

#include "VPluginFactory.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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
PLUGIN_CREATE_FACTORY( CmdKeyName );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdKeyName - constructor

\+---------------------------------------------------------------------*/
CmdKeyName::CmdKeyName
		(
		void
		)
		: VPluginCommand()
		, m_pDictionary( 0 )
		, m_nCmdKeyName( 0 )
		, m_nDictKeyCode( 0 )
		, m_nDictKeyName( 0 )
		, m_aKeys()
{
}

CmdKeyName::CmdKeyName
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner )
		, m_pDictionary( 0 )
		, m_nCmdKeyName( 0 )
		, m_nDictKeyCode( 0 )
		, m_nDictKeyName( 0 )
		, m_aKeys()
{
}

CmdKeyName::CmdKeyName
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner )
		, m_pDictionary( 0 )
		, m_nCmdKeyName( 0 )
		, m_nDictKeyCode( 0 )
		, m_nDictKeyName( 0 )
		, m_aKeys()
{
}



/*---------------------------------------------------------------------+\

 * ~CmdKeyName - destructor

\+---------------------------------------------------------------------*/
CmdKeyName::~CmdKeyName
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

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdKeyName::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	m_nCmdKeyName = pCommandSetup->RegisterCommand( m_sID );

	m_pDictionary = m_pApplication->Dictionary();
	if ( m_pDictionary )
	{
		m_nDictKeyCode = m_pDictionary->LocateEntry( "I:Key Code" );
		m_nDictKeyName = m_pDictionary->LocateEntry( "U:Key Name" );
	}

	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdKeyName::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	bool	bResult = true;

	CVariantData		v;
	const CVariantData*	pv;
	pv = m_pDictionary->GetData( m_nDictKeyCode );
	if ( pv )
	{
		int	n = pv->GetValueInteger();

		CCharString	s;
		s = m_aKeys.GetName( (unsigned)n );
		v = s;
		m_pDictionary->PutData( m_nDictKeyName, &v );
	}

	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdKeyName::Load
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
