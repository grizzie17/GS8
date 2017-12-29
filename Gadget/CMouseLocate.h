/*---------------------------------------------------------------------+\
|
|	CMouseLocate.h  --  brief description of what CMouseLocate.h is for
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
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for Hover
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseDown, MouseUp, and MouseMove
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMouseLocate
#define _H_CMouseLocate
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDrawTmx.h"

#include "NamespaceGadget.h"
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
typedef class CMouseLocate*			CMouseLocatePtr;
typedef class CMouseLocate&			CMouseLocateRef;
typedef const class CMouseLocate&	ConstCMouseLocateRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMouseLocate : public VDrawTmx
{
//	class lifecycle  ----------------------------------------------------
public:
					CMouseLocate();
	virtual			~CMouseLocate();
private:
					CMouseLocate( ConstCMouseLocateRef r );	// copy constructor

public:
//	public types  -------------------------------------------------------

	typedef enum E_TYPE
	{
		M_DOWN,
		M_UP,
		M_CLICK,
		M_MOVE,		// DRAG
		M_HOVER
	} E_TYPE;

//	public functions  ---------------------------------------------------

	CMouseLocateRef	operator=( ConstCMouseLocateRef r );		// assignment

	void		SetAction( E_TYPE t );
	E_TYPE		GetAction( void );

	void		SetPoint( GFLOAT x, GFLOAT y );

	bool		Locate
				(
				GFLOAT	fLeft,
				GFLOAT	fTop,
				GFLOAT	fRight,
				GFLOAT	fBottom
				);

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	E_TYPE	m_action;
	GFLOAT	m_x;	// original mouse input
	GFLOAT	m_y;

	GFLOAT	m_tx;	// transformed mouse point
	GFLOAT	m_ty;



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	VDrawTmx-1
	//	VDrawTmx
public:
	virtual bool	push
					(
					GFLOAT	xPosition,
					GFLOAT	yPosition,
					GFLOAT	xShift,
					GFLOAT	yShift,
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	rotation,
					GFLOAT	scale
					);
	virtual bool	pop( void );


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



#endif /* _H_CMouseLocate */

