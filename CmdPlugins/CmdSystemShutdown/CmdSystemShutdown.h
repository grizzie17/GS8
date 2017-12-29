/*---------------------------------------------------------------------+\
|
|	CmdSystemShutdown.h  --  Header for CmdSystemShutdown Plugin
|
|	Purpose:

		Provide support for touch screen calibration

|	File Custodian:		J.Griswold
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
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdSystemShutdown
#define _H_CmdSystemShutdown
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
#include "CKeyNames.h"

#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN

#define	TOUCH_K_POINTCOUNT	5
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CmdSystemShutdown*		CmdSystemShutdownPtr;
typedef class CmdSystemShutdown&		CmdSystemShutdownRef;
typedef const class CmdSystemShutdown&	ConstCmdSystemShutdownRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdSystemShutdown : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdSystemShutdown);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool	Shutdown
			(
			void
			);

//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;

	VDictionary::Selector	m_nCmdSystemShutdown;




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



#endif /* _H_CmdSystemShutdown */

