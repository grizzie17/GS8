/*---------------------------------------------------------------------+\
|
|	CPanelDivision.h  --  Sub-Panel division block
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
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPanelDivision
#define _H_CPanelDivision
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPanelChild.h"

#include "CVisible.h"
#include "TArray.h"
#include "NamespaceGadget.h"
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
NAMESPACE_GADGET_BEGIN

typedef class CPanelDivision*		CPanelDivisionPtr;
typedef class CPanelDivision&		CPanelDivisionRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPanelDivision : public VPanelChild
{
//	class lifecycle  ----------------------------------------------------
public:
					CPanelDivision();
					CPanelDivision( CPanelDivisionRef r );	// copy constructor
	virtual			~CPanelDivision();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPanelDivisionRef	operator=( CPanelDivisionRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray<VPanelChildPtr>	m_aList;
	CVisiblePtr				m_pVisible;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );

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


#endif /* _H_CPanelDivision */

