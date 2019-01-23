/*---------------------------------------------------------------------+\
|
|	CmdReturnTrue.cpp  --  brief description of what CmdReturnTrue.cpp is for
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
#include "CmdReturnTrue.h"

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
PLUGIN_CREATE_FACTORY( CmdReturnTrue );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdReturnTrue - constructor

\+---------------------------------------------------------------------*/
CmdReturnTrue::CmdReturnTrue
		(
		void
		)
		: VPluginCommand()
		, m_aList()
{
}

CmdReturnTrue::CmdReturnTrue
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner )
		, m_aList()
{
}

CmdReturnTrue::CmdReturnTrue
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner )
		, m_aList()
{
}


/*---------------------------------------------------------------------+\

 * ~CmdReturnTrue - destructor

\+---------------------------------------------------------------------*/
CmdReturnTrue::~CmdReturnTrue
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
bool	CmdReturnTrue::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	CVariantData	v;
	CCharString		s;
	THashTableEnumerator<CCharString, CVariantData>	eLst = m_aList.GetEnumerator();

	while ( eLst.MoveNext() )
	{
		s = eLst.Key();
		v = eLst.Value();

		pCommandSetup->RegisterCommand( s );
	}

	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdReturnTrue::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	return true;
}

/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdReturnTrue::Load
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
	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
