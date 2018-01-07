/*---------------------------------------------------------------------+\
|
|	VPluginWithAggregateList.h  --  brief description of what VPluginWithAggregateList.h is for
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
	07-Jun-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginWithAggregateList
#define _H_VPluginWithAggregateList
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPlugin.h"
#include "TArray.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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
typedef class VPluginWithAggregateList*			VPluginWithAggregateListPtr;
typedef class VPluginWithAggregateList&			VPluginWithAggregateListRef;
typedef const class VPluginWithAggregateList&	ConstVPluginWithAggregateListRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VPluginWithAggregateList : public VPlugin
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VPluginWithAggregateList );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray<ISupportsPtr>	m_aAggregateList;

private:
//	private types  ------------------------------------------------------

	typedef VPlugin		inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
protected:
	//	VSupports

	virtual
	void*	FindExternalInterface
			(
			ConstIXIDRef	rIID,
			NResultPtr		pResult
			);

public:
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

NAMESPACE_COMMON_END



#endif /* _H_VPluginWithAggregateList */
