/*---------------------------------------------------------------------+\
|
|	CPointValue.h  --  Class to encapsulate an X, Y pair
|
|	Purpose:

		Create a class that defines an X, Y pair that may be either
		a set of discrete coordinates or a pair of equations.

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
		Change class hierarchy to derive from a new common class for coordinates
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPoint
#define _H_CPoint
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VCoordinate.h"
#include "CResultValue.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CPointValue*		CPointValuePtr;
typedef class CPointValue&		CPointValueRef;
typedef const class CPointValue&	ConstCPointValueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPointValue : public VCoordinate
{
//	class lifecycle  ----------------------------------------------------
public:
				CPointValue();
				CPointValue( ConstCPointValueRef r );	// copy constructor
	virtual		~CPointValue();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPointValueRef	operator=( ConstCPointValueRef r );		// assignment

	void		SetPointValue( float x, float y );
	void		SetPointEquation( VEquationPtr pX, VEquationPtr pY );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef	VCoordinate	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VGraphic-1
	//	VRenderable
public:


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
CPointValueRef
		CPointValue::operator=
		(
		ConstCPointValueRef	r
		)
{
	VCoordinate::operator=( ConstVCoordinateRef(r) );
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
inline
void	CPointValue::SetPointValue
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
void	CPointValue::SetPointEquation
		(
		VEquationPtr pX,
		VEquationPtr pY
		)
{
	SetEquations( pX, pY );
}




}}


#endif /* _H_CPoint */
