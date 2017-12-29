/*---------------------------------------------------------------------+\
|
|	CmdReturnTrue.h  --  brief description of what CmdReturnTrue.h is for
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
#ifndef _H_CmdReturnTrue
#define _H_CmdReturnTrue
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
typedef class CmdReturnTrue*		CmdReturnTruePtr;
typedef class CmdReturnTrue&		CmdReturnTrueRef;
typedef const class CmdReturnTrue&	ConstCmdReturnTrueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdReturnTrue : public VPluginCommand
{
//	class lifecycle  ----------------------------------------------------
public:
					CmdReturnTrue();
					CmdReturnTrue( ISupportsPtr pOwner );
					CmdReturnTrue( const char* sName, ISupportsPtr pOwner );
protected:
	virtual			~CmdReturnTrue();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	THashTable<CCharString, CVariantData>	m_aList;

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



#endif /* _H_CmdReturnTrue */

