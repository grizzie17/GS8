/*---------------------------------------------------------------------+\
|
|	IDrawTmx.h  --  brief description of what IDrawTmx.h is for
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
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IDrawTmx
#define _H_IDrawTmx
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UFloat.h"
#include "CMatrix3x3.h"


namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/

typedef interface_ IDrawTmx*			IDrawTmxPtr;
typedef interface_ IDrawTmx2*			IDrawTmx2Ptr;

extern const IXID	IXID_IDrawTmx;
extern const IXID	IXID_IDrawTmx2;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IDrawTmx : public ISupports
{
	virtual
	bool	begin
			(
			void
			) PURE;

	virtual
	bool	end
			(
			void
			) PURE;

	virtual
	bool	margin
			(
			int		nLeft,
			int		nTop,
			int		nRight,
			int		nBottom
			) PURE;

	virtual
	bool	push
			(
			GFLOAT	xPosition,
			GFLOAT	yPosition,
			GFLOAT	xShift,
			GFLOAT	yShift,
			GFLOAT	xAxis,
			GFLOAT	yAxis,
			GFLOAT	rotation,
			GFLOAT	scale
			) PURE;
	virtual
	bool	pop
			(
			void
			) PURE;
};


interface_ IDrawTmx2 : public IDrawTmx
{

	virtual void	SetInitialMatrix
					(
					CMatrix3x3&	r
					) PURE;

	virtual void	TransformPoint
					(
					GFLOAT&	rfXOut,
					GFLOAT&	rfYOut,
					GFLOAT	fXIn,
					GFLOAT	fYIn
					) PURE;

	virtual GFLOAT	TransformLength
					(
					GFLOAT	fInLength
					) PURE;

	virtual void	GenActiveMatrix( void ) PURE;
	virtual void	ResetWorld( void ) PURE;

	virtual GFLOAT	normalizeAngle( GFLOAT r ) PURE;	// input is radians
};


/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/

inline
int		intFromFloat
		(
		GFLOAT	x
		)
{
	return (int)(x + (x < GFLOAT_0 ? GFLOAT_NEG1_2 : GFLOAT_1_2 ));
}



}}


#endif /* _H_IDrawTmx */
