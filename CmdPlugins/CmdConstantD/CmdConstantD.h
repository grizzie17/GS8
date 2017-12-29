/*---------------------------------------------------------------------+\
|
|	CmdConstantD.h  --  brief description of what CmdConstantD.h is for
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
	17-May-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdConstantD
#define _H_CmdConstantD
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
typedef class CmdConstantD*		CmdConstantDPtr;
typedef class CmdConstantD&		CmdConstantDRef;
typedef const class CmdConstantD&	ConstCmdConstantDRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdConstantD : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:
					CmdConstantD();
					CmdConstantD( ISupportsPtr pOwner );
					CmdConstantD( const char* sName, ISupportsPtr pOwner );
protected:
	virtual			~CmdConstantD();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	THashTable<CCharString, CVariantData>	m_aList;


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


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



#endif /* _H_CmdConstantD */

