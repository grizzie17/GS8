/*---------------------------------------------------------------------+\
|
|	CPosition.h  --  brief description of what CPosition.h is for
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
#ifndef _H_CPosition
#define _H_CPosition
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

typedef class CPosition*		CPositionPtr;
typedef TPointer<CPosition>		CPositionAutoPtr;
typedef class CPosition&		CPositionRef;
typedef const class CPosition&	ConstCPositionRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPosition : public VCoordinate
{
//	class lifecycle  ----------------------------------------------------
public:
					CPosition();
					CPosition( ConstCPositionRef r );	// copy constructor
	virtual			~CPosition();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPositionRef	operator=( ConstCPositionRef r );		// assignment

	void		SetPointValue( float x, float y );
	void		SetPointEquation( VEquationPtr pX, VEquationPtr pY );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
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
CPositionRef
		CPosition::operator=
		(
		ConstCPositionRef	r
		)
{
	VCoordinate::operator=( ConstVCoordinateRef(r) );
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
inline
void	CPosition::SetPointValue
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
void	CPosition::SetPointEquation
		(
		VEquationPtr pX,
		VEquationPtr pY
		)
{
	SetEquations( pX, pY );
}



NAMESPACE_GADGET_END


#endif /* _H_CPosition */

