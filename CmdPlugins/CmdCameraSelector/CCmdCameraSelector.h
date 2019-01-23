/*---------------------------------------------------------------------+\
|
|	CCmdCCmdCameraSelector.h  --  Header for Camera Selector used with VCB inputs.
|
|	Purpose:
|	File Custodian:		S.Snider
|
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
	20-Sep-2010			J.Griswold		(Reviewed by: S.Graham) [2]
		Reworked to make compatible with Workbench
		Also remove hardcoded up, down, left, right values.
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea) [1]
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCmdCameraSelector
#define _H_CCmdCameraSelector
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CDictionarySelector.h"
#include "CDictPageSelector.h"





/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CCmdCameraSelector*		CCmdCameraSelectorPtr;
typedef class CCmdCameraSelector&		CCmdCameraSelectorRef;
typedef const class CCmdCameraSelector&	ConstCCmdCameraSelectorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCmdCameraSelector : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CCmdCameraSelector);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  ----------------------------------------------------

	VDictionaryPtr				m_pDictionary;

	Yogi::Core::CCharString		m_sName;
	CDictionarySelector			m_selCEditCamera;
	CDictPageSelector			m_pagDEditCamera;
	CDictPageSelector			m_pagDCameraSelector;
	CDictionarySelector			m_selUCurrentVideoFeed;
	Yogi::Common::THashTable<Yogi::Core::CCharString, Yogi::Common::CVariantData>	m_aList;
	Yogi::Common::THashTable<long, CDictPageSelector>		m_aTransitions;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
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
			VDictionary::Selector				selCommand,
			Yogi::Common::ConstCVariantDataRef	vData
			);

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



#endif /* _H_CCmdCameraSelector */
