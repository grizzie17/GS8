/*---------------------------------------------------------------------+\
|
|	CmdConstant.cpp  --  Plugin used to add constants to the dictionary.
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
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CmdConstant.h"

#include "VPluginFactory.h"

NAMESPACE_GADGET_BEGIN

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
PLUGIN_CREATE_FACTORY( CmdConstant );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdConstant - constructor

\+---------------------------------------------------------------------*/
CmdConstant::CmdConstant
		(
		void
		)
		: VPluginCommand(),
		m_aList()
{
}

CmdConstant::CmdConstant
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner ),
		m_aList()
{
}

CmdConstant::CmdConstant
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner ),
		m_aList()
{
}



/*---------------------------------------------------------------------+\

 * ~CmdConstant - destructor

\+---------------------------------------------------------------------*/
CmdConstant::~CmdConstant
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
bool	CmdConstant::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	bool	bResult = false;

	VPluginCommand::Initialize( pApplication, pCommandSetup );

	VDictionaryPagePtr	pPageConstants = m_pApplication->DictPageConstants();

	CVariantData	v;
	CCharString		s;
	THashTableEnumerator<CCharString, CVariantData>	eLst = m_aList.GetEnumerator();

	while ( eLst.MoveNext() )
	{
		s = eLst.Key();
		v = eLst.Value();

		bResult = pPageConstants->AddEntry( s, v );
		if ( ! bResult )
			break;
	}


	return bResult;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdConstant::ProcessRequest
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
bool	CmdConstant::Load
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



NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

