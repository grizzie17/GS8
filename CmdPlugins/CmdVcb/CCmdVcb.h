/*---------------------------------------------------------------------+\
|
|	CCmdVcb.h  --  brief description of what CCmdVcb.h is for
|
|	Purpose:
|	File Custodian:		R.Hosea
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
	08-Jul-2010			R.Hosea		(Reviewed by: S.Snider)
		Initial Revision, unable to unit test because of lack of menu control
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCmdVcb
#define _H_CCmdVcb
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "IVideoFeedCntl.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CApplicationGaugeVDDS.h"

#include "NamespaceVideoSource.h"

#include "VPluginWithAggregateList.h"
#include "IGraphicsEvent.h"
#include "IDataMessage.h"
#include "IDataStream.h"
#include "IPluginLoadConfiguration.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
USING_NAMESPACE_GRAPHICS_EVENT
USING_NAMESPACE_COMMUNICATION

namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CCmdVcb*		CCmdVcbPtr;
typedef class CCmdVcb&		CCmdVcbRef;
typedef const class CCmdVcb&	ConstCCmdVcbRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCmdVcb : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE(CCmdVcb);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	DECLARE_ISUPPORTS;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


	IDataStream*	m_pDataStream;
	IGraphicsEvent*	m_pGraphicsEvent;
	VDictionary::Selector m_cBackLight;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);


public:
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
			ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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






#endif /* _H_CCmdVcb */
