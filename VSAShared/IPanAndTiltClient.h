/*---------------------------------------------------------------------+\
|
|	IPanAndTiltClient.h  --  interface for driving a Pan & Tilt module
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
#ifndef _H_IPanAndTiltClient
#define _H_IPanAndTiltClient
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UFloat.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define	EPTM_M_AcceptInput	0x0001
#define	EPTM_M_ScanActive	0x0002		// also known as auto-pan
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IPanAndTiltClient*			IPanAndTiltClientPtr;

extern const Yogi::Common::IXID	IXID_IPanAndTiltClient;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IPanAndTiltClient : public Yogi::Common::ISupports
{
	//
	//	State
	//
	//	Receive postion information
	//
	virtual
	Yogi::Core::NResult	EptmState
			(
			GFLOAT		fPan,
			GFLOAT		fTilt,
			long		mFlags		// see EPTM_M_xxx above
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


#endif /* _H_IPanAndTiltClient */
