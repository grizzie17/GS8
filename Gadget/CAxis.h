/*---------------------------------------------------------------------+\
|
|	CAxis.h  --  brief description of what CAxis.h is for
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
	17-Jul-2009			J.Griswold
		Change to new VCoordinate class for parent
	29-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CAxis
#define _H_CAxis
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VCoordinate.h"
#include "TPointer.h"
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

typedef class CAxis*		CAxisPtr;
typedef TPointer<CAxis>		CAxisAutoPtr;
typedef class CAxis&		CAxisRef;
typedef const class CAxis&	ConstCAxisRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CAxis : public VCoordinate
{
//	class lifecycle  ----------------------------------------------------
public:
					CAxis();
					CAxis( ConstCAxisRef r );	// copy constructor
	virtual			~CAxis();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CAxisRef	operator=( ConstCAxisRef r );		// assignment

	void		SetPointValue( float x, float y );
	void		SetPointEquation( VEquationPtr pX, VEquationPtr pY );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef VCoordinate	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VRenderable
public:
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );

	//	VOwnership

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
CAxisRef
		CAxis::operator=
		(
		ConstCAxisRef	r
		)
{
	VCoordinate::operator=( ConstVCoordinateRef(r) );
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
inline
void	CAxis::SetPointValue
		(
		float	x,
		float	y
		)
{
	SetValues( x, y );
}

/*---------------------------------------------------------------------+\

 * SetPointEquation -

\+---------------------------------------------------------------------*/
inline
void	CAxis::SetPointEquation
		(
		VEquationPtr pX,
		VEquationPtr pY
		)
{
	SetEquations( pX, pY );
}



NAMESPACE_GADGET_END


#endif /* _H_CAxis */

