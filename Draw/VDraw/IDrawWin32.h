/*---------------------------------------------------------------------+\
|
|	IDrawWin32.h  --  brief description of what IDrawWin32.h is for
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
#ifndef _H_IDrawWin32
#define _H_IDrawWin32
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UOSIncludes.h"



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
#if ! defined( OS_MSWIN )
	typedef long	HWND;
	typedef long	HDC;
	typedef long*	LPRECT;
#endif

typedef interface_ IDrawWin32*			IDrawWin32Ptr;

extern const IXID	IXID_IDrawWin32;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IDrawWin32 : public ISupports
{
	virtual
	void	SetHDC
			(
			HWND	wd,
			HDC		dc,
			LPRECT	pRect = NULL
			) PURE;

	virtual
	void	UpdateRect
			(
			LPRECT	pRect
			) PURE;

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


#endif /* _H_IDrawWin32 */
