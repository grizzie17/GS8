/*---------------------------------------------------------------------+\
|
|	CVisible.h  --  brief description of what CVisible.h is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	19-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVisible
#define _H_CVisible
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VRenderable.h"
#include "CResultValue.h"
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
typedef class CVisible*			CVisiblePtr;
typedef class CVisible&			CVisibleRef;
typedef const class CVisible&	ConstCVisibleRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CVisible : public VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
					CVisible();
					CVisible( ConstCVisibleRef r );	// copy constructor
	virtual			~CVisible();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CVisibleRef	operator=( ConstCVisibleRef r );		// assignment

	void		SetEquation( VEquationPtr p );

	bool		GetValue( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue	m_tValue;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VRenderable-1
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render(VDictionaryPtr pDict, VDrawPtr pDraw);
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );
	virtual bool	IsDisplayed( VDictionaryPtr pDict );

	virtual
	bool	ProcessEvent
			(
			VDictionaryPtr			pDict,
			VDictionary::Selector	vEvent
			);

	/*
		Process a Mouse click.
	*/
	virtual
	bool	ProcessMouse
			(
			VDictionaryPtr	pDict,
			CMouseLocatePtr	pMouseLocate
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



#endif /* _H_CVisible */

