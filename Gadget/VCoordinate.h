/*---------------------------------------------------------------------+\
|
|	VCoordinate.h  --  Class to encapsulate an X, Y pair
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VCoordinate
#define _H_VCoordinate
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
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class VCoordinate*		VCoordinatePtr;
typedef class VCoordinate&		VCoordinateRef;
typedef const class VCoordinate&	ConstVCoordinateRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class VCoordinate : public VRenderable
{
//	class lifecycle  ----------------------------------------------------
public:
				VCoordinate();
				VCoordinate( ConstVCoordinateRef r );	// copy constructor
	virtual		~VCoordinate();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	VCoordinateRef	operator=( ConstVCoordinateRef r );		// assignment

	void		SetValues( GFLOAT x, GFLOAT y );
	void		SetXValue( GFLOAT f );
	void		SetYValue( GFLOAT f );

	void		SetEquations( VEquationPtr pX, VEquationPtr pY );

	void		SetXEquation( VEquationPtr p );
	void		SetYEquation( VEquationPtr p );

	CResultValuePtr
				X( void );
	CResultValuePtr
				Y( void );

	GFLOAT		GetX( void );
	GFLOAT		GetY( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CResultValue	m_tX;
	CResultValue	m_tY;

private:
//	private types  ------------------------------------------------------

	typedef	VRenderable	inherited;

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

}}


#endif /* _H_VCoordinate */
