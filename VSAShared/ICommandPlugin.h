/*---------------------------------------------------------------------+\
|
|	ICommandPlugin.h  --  deal with plugin commands
|
|	Purpose:
		Define functions that are necessary to be compatible with
		the command processor

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
	12-Jul-2010			J.Griswold		(Reviewed by: P.Hogan)
		Add optional InitialState pointer for the RegisterCommand func.
	03-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Move definition of IXID to cpp file
	16-May-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_ICommandPlugin
#define _H_ICommandPlugin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CApplicationGauge.h"
#include "CCharDescriptor.h"
#include "VDictionary.h"
#include "CVariantData.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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
typedef interface_ ICommandPlugin*			ICommandPluginPtr;

extern const IXID	IXID_ICommandPlugin;

typedef class VCommandSetup*		VCommandSetupPtr;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

// this "interface" is handed to the ICommandPlugin::Initialize function
class VCommandSetup
{
public:

	virtual
	VDictionary::Selector
			RegisterCommand
			(
			const char*		sCommandName,
			CVariantDataPtr	pInitialState = 0
			) = 0;

	virtual
	VDictionary::Selector
			RegisterCommand
			(
			ConstCCharDescriptorRef	rCommandName,
			CVariantDataPtr			pInitialState = 0
			) = 0;
};




interface_ ICommandPlugin : public ISupports
{

	//	Implementors of this function should call back on the
	//	VCommandSetupPtr to register the commands that this
	//	plugin supports.  Also any entries in the K and D pages
	//	should be added at this time.
	//
	//	You should also save pointers to any dictionary pages
	//	that you need.
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			) PURE;

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			ConstCVariantDataRef	vData
			) PURE;

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



#endif /* _H_ICommandPlugin */

