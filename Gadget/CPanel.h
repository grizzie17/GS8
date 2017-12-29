/*---------------------------------------------------------------------+\
|
|	CPanel.h  --  brief description of what CPanel.h is for
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
	23-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Implement a "Layout" script capability that allows the
		use of registers and shared data during layout.
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change class hierarchy.
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPanel
#define _H_CPanel
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VControlEventMap.h"

#include "NamespaceGadget.h"
#include "VPanelChild.h"
#include "TArray.h"
#include "TPointer.h"
#include "CKeyEventMap.h"
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

typedef class CPanel*		CPanelPtr;
typedef TPointer<CPanel>	CPanelAutoPtr;
typedef class CPanel&		CPanelRef;
typedef const class CPanel&	ConstCPanelRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPanel : public VControlEventMap
{
//	class lifecycle  ----------------------------------------------------
public:
					CPanel();
					CPanel( CPanelRef r );	// copy constructor
	virtual			~CPanel();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPanelRef		operator=( CPanelRef r );		// assignment

	bool			AddChild( VPanelChildPtr pChild );

	bool			Layout( VDictionaryPtr pDict );


	void			SetLayoutScript( VEquationPtr pEq );



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray<VPanelChildPtr>	m_aChildren;
	TPointer<VEquation>		m_pLayout;		// always called for Layout

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );

	//	VControl
public:
	virtual bool	ProcessEvent( VDictionaryPtr pDict, VDictionary::Selector vEvent );
	virtual bool	ProcessMouse( VDictionaryPtr pDict, CMouseLocatePtr pMouseLocate );

	//	VControlEventMap
public:
	virtual int		CalculateDirtyRectangle
					(
					VDictionaryPtr	pDict,
					long*	pLeft,
					long*	pTop,
					long*	pRight,
					long*	pBottom
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


#endif /* _H_CPanel */

