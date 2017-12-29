/*---------------------------------------------------------------------+\
|
|	CRectangle.h  --  Rectangle object
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
		Rectangle
			Width=
			Height=
			FillColor=
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Change to support V2 schema
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Also fix the "virtual" designation for Calculate and Render
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Rectangle object
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CRectangle
#define _H_CRectangle
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"

#include "CPoint.h"
#include "CSize.h"
#include "CResultValue.h"
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

typedef class CRectangle*		CRectanglePtr;
typedef class CRectangle&		CRectangleRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CRectangle : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CRectangle();
					CRectangle( CRectangleRef r );	// copy constructor
	virtual			~CRectangle();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CRectangleRef	operator=( CRectangleRef r );		// assignment

	CPointValuePtr	Origin( void );
	CSizePtr		Size( void );
	CResultValuePtr	Width( void );
	CResultValuePtr	Height( void );
	void			SetCornerStyle( VDraw::CORNERSTYLE c );
	CResultValuePtr	Corner( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CPointValue			m_tOrigin;
	CSize				m_tSize;
	VDraw::CORNERSTYLE	m_eCornerStyle;
	CResultValue		m_tCorner;	// size of bevel or rounding

private:
//	private types  ------------------------------------------------------

	typedef	VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );

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


#endif /* _H_CRectangle */

