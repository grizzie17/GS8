/*------------------------------------------------------------------*//**
*
*	@file UFloat.h
*
*	@brief Types for the portable machine
*
*//*-------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	05-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UFloat
#define _H_UFloat
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <float.h>

#include "fixed_t.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#ifdef FIXED_USE_FLOAT
#	define	GFLOAT_USE_FIXED	0
#else
#	if defined(OS_MSWIN)
#		define	GFLOAT_USE_FIXED	0
#	elif defined(OS_LINUX_VDDS)
#		define	GFLOAT_USE_FIXED	0
#	else
#		define	GFLOAT_USE_FIXED	0
#	endif
#endif

#if GFLOAT_USE_FIXED

#	define	GFLOAT			fixed_t
#	define	GFLOAT_CAST(f)	ToFixed_t(f)

#	define	GXFLOAT			local_fixed_t
#	define	GXFLOAT_CAST(f)	fixed_t_data(f)

#	define	GFLOAT_MAX		FXD_MAX
#	define	GFLOAT_MIN		FXD_MIN
#	define	GFLOAT_EPSILON	FXD_EPSILON

#	define	GFLOAT_0		fixed_t::k_0		//	0
#	define	GFLOAT_1_2		fixed_t::k_1_2		//	1/2
#	define	GFLOAT_NEG1_2	fixed_t::k_neg1_2	//	-1/2
#	define	GFLOAT_1_10		fixed_t::k_1_10		//	1/10
#	define	GFLOAT_1		fixed_t::k_1		//	1
#	define	GFLOAT_NEG1		fixed_t::k_neg1		//	-1
#	define	GFLOAT_2		fixed_t::k_2		//	2
#	define	GFLOAT_PI		fixed_t::k_PI		//	pi
#	define	GFLOAT_PI_2		fixed_t::k_PI_2		//	pi/2
#	define	GFLOAT_2PI		fixed_t::k_2PI		//	2*pi
#	define	GFLOAT_10		fixed_t::k_10		//	10
#	define	GFLOAT_180		fixed_t::k_180		//	180
#	define	GFLOAT_360		fixed_t::k_360		//	360

#else

#	define	GFLOAT			float
#	define	GFLOAT_CAST(f)	float(f)

#	define	GXFLOAT			float
#	define	GXFLOAT_CAST(f)	float(f)

#	define	GFLOAT_MAX		FLT_MAX
#	define	GFLOAT_MIN		FLT_MIN
#	define	GFLOAT_EPSILON	FLT_EPSILON

#	define	GFLOAT_0		(0.0f)		//	0
#	define	GFLOAT_1_2		(0.5f)		//	1/2
#	define	GFLOAT_NEG1_2	(-0.5f)		//	-1/2
#	define	GFLOAT_1_10		(0.1f)		//	1/10
#	define	GFLOAT_1		(1.0f)		//	1
#	define	GFLOAT_NEG1		(-1.0f)		//	-1
#	define	GFLOAT_2		(2.0f)		//	2
#	define	GFLOAT_PI_2		(kPI/2.0f)	//	pi/2
#	define	GFLOAT_PI		(kPI)		//	pi
#	define	GFLOAT_2PI		(kPI2)		//	2*pi
#	define	GFLOAT_10		(10.0f)		//	10
#	define	GFLOAT_180		(180.0f)
#	define	GFLOAT_360		(360.0f)

#endif
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
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
||	Function Macros														|
||																		|
\+=====================================================================*/
namespace Yogi { namespace Core {

/**
 *	check if two floating point numbers are equivalent
 *
 *	@note	floating point is an approximation on computers
 */
inline
bool	Equiv
		(
		const GFLOAT&	a,	///< [in] argument 1
		const GFLOAT&	b	///< [in] argument 2
		)
{
	return fabsf( a - b ) < GFLOAT_EPSILON;
}


}}

#endif /* _H_UFloat */

