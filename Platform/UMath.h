/*------------------------------------------------------------------*//**
*
*	@file UMath.h
*
*	@brief Some helpful constants for math
*
*//*-------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		invert the file include between this and ufloat.h
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	16-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add a constant for 2*pi
	08-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UMath
#define _H_UMath
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <math.h>
#include <float.h>

#include "UOSIncludes.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


const float kPI = 3.14159265358979323846f;
const float kPI2 = kPI * 2.0f;


/*
#if ! defined( min )
#	define min( a, b )				umin( (a), (b) )
#endif
#if ! defined( max )
#	define max( a, b )				umax( (a), (b) )
#endif
*/

#if !defined(numberof)
#	define numberof( a )	(sizeof(a)/sizeof(a[0]))
#endif



#if defined( OS_MSWIN_WCE )

#	ifdef sinf
#		undef sinf
#	endif
#	define	sinf( n )	(float)sin( (double)(n) )

#	ifdef cosf
#		undef cosf
#	endif
#	define	cosf( n )	(float)cos( (double)(n) )

#	ifdef atanf
#		undef atanf
#	endif
#	define	atanf( n )	(float)atan( (double)(n) )

#	ifdef tanf
#		undef tanf
#	endif
#	define	tanf( n )	(float)tan( (double)(n) )

#endif


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/


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

/**
 *	umin - identify minimum argument
 *
 * 	@note	please note that both arguments must be of the same type
 */
template <typename T>
inline
const T&
	umin			///@return minimum argument
	(
	const T&	a,	///< [in] argument 1
	const T&	b	///< [in] argument 2
	)
{
	return a < b ? a : b;
}




/**
 *	umax - identify maximum argument
 *
 * 	@note	please note that both arguments must be of the same type
 */
template <typename T>
inline
const T&
	umax			///@return maximum argument
	(
	const T&	a,	///< [in] argument 1
	const T&	b	///< [in] argument 2
	)
{
	return a < b ? b : a;
}





#endif /* _H_UMath */

