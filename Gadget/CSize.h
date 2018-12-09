/*---------------------------------------------------------------------+\
|
|	CSize.h  --  brief description of what CSize.h is for
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
	23-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSize
#define _H_CSize
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VCoordinate.h"



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
namespace Yogi { namespace Gadget {

typedef class CSize*		CSizePtr;
typedef class CSize&		CSizeRef;
typedef const class CSize&	ConstCSizeRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CSize : public VCoordinate
{
//	class lifecycle  ----------------------------------------------------
public:
				CSize();
				CSize( ConstCSizeRef r );	// copy constructor
	virtual		~CSize();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CSize&		operator=( ConstCSizeRef r );		// assignment

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
	//	VRenderable
public:
	virtual bool	PreRender( VDictionaryPtr pDict, VDrawQueuePtr pQueue );
	virtual bool	Render( VDictionaryPtr pDict, VDrawPtr pDraw );
	virtual bool	GetSize( VDictionaryPtr pDict, long& rnWidth, long& rnHeight );

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
CSize&
		CSize::operator=
		(
		ConstCSizeRef	r
		)
{
	VCoordinate::operator=( ConstVCoordinateRef(r) );
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
inline
void	CSize::SetPointValue
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
void	CSize::SetPointEquation
		(
		VEquationPtr pX,
		VEquationPtr pY
		)
{
	SetEquations( pX, pY );
}


}}


#endif /* _H_CSize */
