/*---------------------------------------------------------------------+\
|
|	CSelect.h  --  Implementation of a Select/Case construct
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
	27-Aug-2009			J.Griswold
		React to change for Case tag that allows an Expression instead
		of just an ExpressionResult.
	14-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSelect
#define _H_CSelect
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceGadget.h"
#include "VElement.h"
#include "CResultValue.h"
#include "VEquation.h"
#include "CSelectCase.h"
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
typedef class CSelect*			CSelectPtr;
typedef class CSelect&			CSelectRef;
typedef const class CSelect&	ConstCSelectRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CSelect : public VElement
{
//	class lifecycle  ----------------------------------------------------
public:
					CSelect();
					CSelect( ConstCSelectRef r );	// copy constructor
	virtual			~CSelect();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CSelectRef	operator=( ConstCSelectRef r );		// assignment


	void	SetEquation( VEquationPtr pEq );
	bool	AddCase( CSelectCasePtr	pCase );
	bool	SetCaseElse( CSelectCasePtr pCase );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue			m_tSelect;
	CSelectCasePtr			m_pCase;		// current case
	TArray<CSelectCasePtr>	m_aList;
	CSelectCasePtr			m_pCaseElse;


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
	virtual int		GetChildContext( void );

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



#endif /* _H_CSelect */

