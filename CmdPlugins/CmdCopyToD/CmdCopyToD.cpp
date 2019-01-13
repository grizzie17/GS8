/*---------------------------------------------------------------------+\
|
|	CmdCopyToD.cpp  --  brief description of what CmdCopyToD.cpp is for
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
	17-May-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CmdCopyToD.h"

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
PLUGIN_CREATE_FACTORY( CmdCopyToD );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdCopyToD - constructor

\+---------------------------------------------------------------------*/
CmdCopyToD::CmdCopyToD
		(
		void
		)
		: VPluginCommand()
		, m_aList()
		, m_aCommands()
{
}

CmdCopyToD::CmdCopyToD
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner )
		, m_aList()
		, m_aCommands()
{
}

CmdCopyToD::CmdCopyToD
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner )
		, m_aList()
		, m_aCommands()
{
}


/*---------------------------------------------------------------------+\

 * ~CmdCopyToD - destructor

\+---------------------------------------------------------------------*/
CmdCopyToD::~CmdCopyToD
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
/*----------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdCopyToD::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	CVariantData	v;
	CCharString		s;
	VDictionary::Selector	sel;
	long					n;
	THashTableEnumerator<CCharString, CVariantData>	eLst = m_aList.GetEnumerator();

	while ( eLst.MoveNext() )
	{
		s = eLst.Key();
		v = eLst.Value();

		sel = pCommandSetup->RegisterCommand( s );
		if ( sel )
		{
			m_pDataPage->AddEntry( s, v );
			n = m_pDataPage->LocateEntry( s );
			if ( -1 < n )
				m_aCommands.Add( sel, n );
		}
	}


	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdCopyToD::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	long*	pn;
	pn = m_aCommands.Find( selCommand );
	if ( pn )
	{
		CVariantData	v = vData;
		m_pDataPage->UpdateEntry( (unsigned long)*pn, v );
	}
	return true;
}

/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdCopyToD::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );
	if ( bResult )
	{
		CVariantData	v;
		CCharString		s;
		VPluginConfiguration::ParamEnum	eCfg = pConfig->GetParamEnum();

		while ( eCfg.MoveNext() )
		{
			v = eCfg.Value();
			s = eCfg.Key();

			m_aList.Add( s, v );
		}
	}
	//CCharString	s = pConfig->GetParameterAsString("Test");
	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
