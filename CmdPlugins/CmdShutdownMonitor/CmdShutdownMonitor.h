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
|	CmdShutdownMonitor.h  --  Header for CmdShutdownMonitor Plugin
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
	12-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdShutdownMonitor
#define _H_CmdShutdownMonitor
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
typedef class CmdShutdownMonitor*		CmdShutdownMonitorPtr;
typedef class CmdShutdownMonitor&		CmdShutdownMonitorRef;
typedef const class CmdShutdownMonitor&	ConstCmdShutdownMonitorRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdShutdownMonitor : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdShutdownMonitor);

public:
//	supported interfaces  -----------------------------------------------


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	VDictionary::Selector	m_nCmdShutdownMonitor;




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



#endif /* _H_CmdShutdownMonitor */

