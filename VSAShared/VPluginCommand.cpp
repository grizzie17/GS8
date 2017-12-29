/*---------------------------------------------------------------------+\
|
|	VPluginCommand.cpp  --  base class for command plugins
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
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea)
		Added page constants member.
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Allow commands to participate in Aggregation
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * VPluginCommand - constructor

\+---------------------------------------------------------------------*/
VPluginCommand::VPluginCommand
		(
		void
		)
		: inherited(),
		m_sID(),
		m_pApplication( 0 ),
		m_pDataPage( 0 ),
		m_pConstantsPage( 0 )
{
}

VPluginCommand::VPluginCommand
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_sID(),
		m_pApplication( 0 ),
		m_pDataPage( 0 ),
		m_pConstantsPage( 0 )
{
}

VPluginCommand::VPluginCommand
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_sID(),
		m_pApplication( 0 ),
		m_pDataPage( 0 ),
		m_pConstantsPage( 0 )
{
}

/*---------------------------------------------------------------------+\

 * ~VPluginCommand - destructor

\+---------------------------------------------------------------------*/
VPluginCommand::~VPluginCommand
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	VPluginCommand::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		//pCommandSetup
		)
{
	m_pApplication = pApplication;
	m_pDataPage = pApplication->DictPageData();
	m_pConstantsPage = pApplication->DictPageConstants();
	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	VPluginCommand::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	return false;
}

/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	VPluginCommand::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	m_sID = pConfig->GetID();
	return inherited::Load( pConfig, pLib );
}


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

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	VPluginCommand::FindInternalInterface
		(
		ConstIXIDRef rIID
		)
{
	void*	p = inherited::FindInternalInterface( rIID );
	if ( p )
		return p;

	if ( rIID == IXID_ICommandPlugin )
		return INTERFACE_THIS( ICommandPluginPtr );
	else
		return 0;
}


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

