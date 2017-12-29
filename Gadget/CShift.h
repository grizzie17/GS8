/*---------------------------------------------------------------------+\
|
|	CShift.h  --  brief description of what CShift.h is for
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
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Maximum and Minimum limits on the Shift
		object.
	17-Jul-2009			J.Griswold
		Use new VCoordinate class
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CShift
#define _H_CShift
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VRenderable.h"

#include "CResultValue.h"
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

typedef class CShift*		CShiftPtr;
typedef class CShift&		CShiftRef;
typedef const class CShift&	ConstCShiftRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CShift : public VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
					CShift();
					CShift( ConstCShiftRef r );	// copy constructor
	virtual			~CShift();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CShiftRef	operator=( ConstCShiftRef r );		// assignment

	void		SetPointValue( float x, float y );
	void		SetPointEquation( VEquationPtr pX, VEquationPtr pY );

	CResultValuePtr	Expression( void );
	CResultValuePtr	Minimum( void );
	CResultValuePtr	Maximum( void );
	GFLOAT*			ScaleX( void );
	GFLOAT*			ScaleY( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue	m_tExpression;
	CResultValue	m_tMinimum;
	CResultValue	m_tMaximum;
	GFLOAT			m_fScaleX;
	GFLOAT			m_fScaleY;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Layout( VDictionaryPtr pDict );
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
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
/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
inline
CShiftRef
		CShift::operator=
		(
		ConstCShiftRef	r
		)
{
	VRenderable::operator=( ConstVRenderableRef(r) );
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
inline
void	CShift::SetPointValue
		(
		float	,//x,
		float	//y
		)
{
	//SetValues( x, y );
}

/*---------------------------------------------------------------------+\

 * SetPointEquation -

\+---------------------------------------------------------------------*/
inline
void	CShift::SetPointEquation
		(
		VEquationPtr ,//pX,
		VEquationPtr //pY
		)
{
	//SetEquations( pX, pY );
}


NAMESPACE_GADGET_END


#endif /* _H_CShift */

