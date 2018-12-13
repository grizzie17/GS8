/*---------------------------------------------------------------------+\
|
|	IApplet.h  --  brief description of what IApplet.h is for
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
	15-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IApplet
#define _H_IApplet
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "IHusk.h"
#include "CCharString.h"


namespace Yogi { namespace Gadget {
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

typedef interface_ IApplet*			IAppletPtr;

extern const Yogi::Common::IXID	IXID_IApplet;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IApplet : public ISupports
{
	/// OnLoad - called right after applet is loaded
	///
	/// Typically includes Storage Broker Registration
	///
	virtual
	Yogi::Core::NResult	OnLoad
			(
			IHuskPtr	pHusk
			) PURE;

	virtual
	Yogi::Core::NResult	OnUnload
			(
			) PURE;

	/// OnStart - the applet is about to become visible
	///
	/// Typical operations include:
	///		* Start any threads that are required
	///		* Register with the box manager any boxes this application
	///			needs to display
	///
	virtual
	Yogi::Core::NResult	OnStart
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnStop
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnPause
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnResume
			(
			) PURE;


	virtual
	bool	IsRunning
			(
			void
			);

	virtual
	ConstYogi::Core::CCharStringRef
			GetID
			(
			void
			);

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


}}


#endif /* _H_IApplet */
