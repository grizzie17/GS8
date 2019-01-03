/*---------------------------------------------------------------------+\
|
|	VPluginCommand.h  --  Base class for plugin commands
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
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
#ifndef _H_VPluginCommand
#define _H_VPluginCommand
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregateList.h"

#include "ICommandPlugin.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class VPluginCommand*		VPluginCommandPtr;
typedef class VPluginCommand&		VPluginCommandRef;
typedef const class VPluginCommand&	ConstVPluginCommandRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginCommand : public Yogi::Common::VPluginWithAggregateList,
						implements_ ICommandPlugin
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPluginCommand );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	ICommandPlugin
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			);

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			Yogi::Common::ConstCVariantDataRef	vData
			);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString	m_sID;
	CApplicationGaugePtr	m_pApplication;
	VDictionaryPagePtr		m_pDataPage;		// D - Data Response Page
	VDictionaryPagePtr		m_pConstantsPage;	// K - Data Response Page


private:
//	private types  ------------------------------------------------------

	typedef	Yogi::Common::VPluginWithAggregateList	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

public:
	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
			);

};

/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}



#endif /* _H_VPluginCommand */
