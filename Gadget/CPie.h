/*---------------------------------------------------------------------+\
|
|	CPie.h  --  brief description of what CPie.h is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Also fix the "virtual" designator for Calculate and Render
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPie
#define _H_CPie
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VGraphic.h"
#include "CPoint.h"
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
namespace Yogi { namespace Gadget {

typedef class CPie*		CPiePtr;
typedef class CPie&		CPieRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPie : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CPie();
					CPie( CPieRef r );	// copy constructor
	virtual			~CPie();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CPieRef	operator=( CPieRef r );		// assignment

	CPointValuePtr	Axis( void );
	CResultValuePtr	Radius();
	CResultValuePtr	StartAngle();
	CResultValuePtr	EndAngle();

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CPointValue		m_tAxis;
	CResultValue	m_tRadius;
	CResultValue	m_tStartAngle;
	CResultValue	m_tEndAngle;		// counter clockwise sweep from start angle

private:
//	private types  ------------------------------------------------------

	typedef	VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	virtual int		Calculate( VDictionaryPtr pDict );
	virtual bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );

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


#endif /* _H_CPie */
