/*---------------------------------------------------------------------+\
|
|	CArc.h  --  brief description of what CArc.h is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CArc
#define _H_CArc
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

typedef class CArc*			CArcPtr;
typedef class CArc&			CArcRef;
typedef const class CArc&	ConstCArcRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CArc : public VGraphic
{
//	class lifecycle  ----------------------------------------------------
public:
					CArc();
					CArc( CArcRef r );	// copy constructor
	virtual			~CArc();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CArcRef	operator=( ConstCArcRef r );		// assignment


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

	typedef VGraphic	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VRenderable
public:
	int		Calculate( VDictionaryPtr pDict );
	bool	Render( VDictionaryPtr pDict, Yogi::Common::VDrawPtr pDraw );

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


#endif /* _H_CArc */
