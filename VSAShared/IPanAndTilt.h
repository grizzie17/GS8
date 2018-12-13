/*---------------------------------------------------------------------+\
|
|	IPanAndTilt.h  --  interface for driving a Pan & Tilt module
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:

		It is worth noting that the Pan&Tilt modules may have slight
		differences in implementation.  For instance specifying a speed
		value of 0.37 may be interpreted (or rounded) to a value that
		can be easily handled by the supporting module.


|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	14-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IPanAndTilt
#define _H_IPanAndTilt
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "IPanAndTiltClient.h"

#include "UFloat.h"


namespace Yogi { namespace Gadget {
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

typedef interface_ IPanAndTilt*			IPanAndTiltPtr;

extern const Yogi::Common::IXID	IXID_IPanAndTilt;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IPanAndTilt : public Yogi::Common::ISupports
{

	///	MoveViaSpeed
	///
	///	Move the Pan&Tilt module based on a relative speed.
	///	The values are normalized with 1.0 being the fastest speed
	///
	///	Pan - negative moves left, positive moves right
	///	Tilt - negavie moves down, positive moves up
	///
	///	This is an asyncronous request
	///
	virtual
	Yogi::Core::NResult	MoveViaSpeed
			(
			GFLOAT		fPanNorm,	//!< [in]	normalized speed for rotation
			GFLOAT		fTiltNorm	//!< [in]	normalized speed for elevation
			) PURE;


	///	MoveDelta
	///
	///	Move the Pan&Tilt module based on a relative number of degrees.
	///
	///	This is an asyncronous request
	///
	virtual
	Yogi::Core::NResult	MoveDelta
			(
			GFLOAT		fPan,		//!< [in]	degrees
			GFLOAT		fTilt,		//!< [in]	degrees
			GFLOAT		fSpeed		//!< [in]	0 .. 1
			) PURE;


	///	MoveAbsolute
	///
	///	Move the Pan&Tilt module to a specified rotation and azimuth
	///	specified in degrees.
	///
	///	The speed is specified as a normalized value where 1.0 is the
	///	fastest speed.
	///
	///	This is an asyncronous request
	///
	virtual
	Yogi::Core::NResult	MoveAbsolute
			(
			GFLOAT		fPan,		//!< [in]	degrees
			GFLOAT		fTilt,		//!< [in]	degrees
			GFLOAT		fSpeed		//!< [in]	0 .. 1
			) PURE;


	///	AutoPan
	///
	///	Cycle the Pan&Tilt module through a virtual window
	///
	///	This is an asyncronous request
	///
	virtual
	Yogi::Core::NResult	AutoPan
			(
			GFLOAT		fPanLeft,		//!< [in]	left side of virtual window
			GFLOAT		fTiltTop,		//!< [in]	top side of virtual window
			GFLOAT		fPanRight,		//!< [in]	right side of virtual window
			GFLOAT		fTiltBottom,	//!< [in]	bottom of virtual window
			GFLOAT		fSpeed			//!< [in]	normalized speed value
			) PURE;


	///	MoveHome
	///
	///	Move the Pan&Tilt module to its designated home position
	///
	///	This is an asyncronous request
	///
	virtual
	Yogi::Core::NResult	MoveHome
			(
			void
			) PURE;


	///	SetHome
	///
	///	Establishes the current Pan&Tilt position as the "home" position
	///	You should check the return value to make sure that the current
	///	Pan&Tilt module supports the SetHome command
	///
	virtual
	Yogi::Core::NResult	SetHome
			(
			void
			) PURE;


	///	GetPosition
	///
	///	Get the current Pan & Tilt angles
	///
	virtual
	Yogi::Core::NResult	GetPosition
			(
			GFLOAT*		pPan,	//!< [out]	rotation position in degrees
			GFLOAT*		pTilt	//!< [out]	elevation position in degrees
			) PURE;

	///	RegisterClient
	///
	///	Identify that the client want to be notified of position and status
	///	information for the current Pan & Tilt device
	///
	virtual
	Yogi::Core::NResult	RegisterClient
			(
			IPanAndTiltClientPtr	p
			) PURE;

	virtual
	Yogi::Core::NResult	UnregisterClient
			(
			IPanAndTiltClientPtr	p
			) PURE;
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


#endif /* _H_IPanAndTilt */
