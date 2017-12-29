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
#include "NamespaceGadget.h"
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

NAMESPACE_GADGET_BEGIN
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
NAMESPACE_GADGET_END






#endif /* _H_CCmdVcb */

