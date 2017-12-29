/*---------------------------------------------------------------------+\
|
|	CMouseAreaList.h  --  brief description of what CMouseAreaList.h is for
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
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMouseAreaList
#define _H_CMouseAreaList
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "CMouseArea.h"
#include "VDictionary.h"
#include "TArray.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CMouseAreaList*			CMouseAreaListPtr;
typedef class CMouseAreaList&			CMouseAreaListRef;
typedef const class CMouseAreaList&	ConstCMouseAreaListRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMouseAreaList
{
//	class lifecycle  ----------------------------------------------------
public:
					CMouseAreaList();
					CMouseAreaList( ConstCMouseAreaListRef r );	// copy constructor
	virtual			~CMouseAreaList();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CMouseAreaListRef	operator=( ConstCMouseAreaListRef r );		// assignment

	void	AddArea( CMouseAreaPtr p );

	bool	Calculate( VDictionaryPtr pDict );
	bool	ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouseLocate );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray<CMouseAreaPtr>	m_aList;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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



#endif /* _H_CMouseAreaList */

