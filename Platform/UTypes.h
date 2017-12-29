//=====================================================================//
//!
//!	@file	UTypes.h
//!	@brief	define a set of portable data types
//!
//!	@note
//!
//!		size_t		unsigned integer (result of sizeof operator)
//!		SIZE_T
//!		rsize_t		restricted size_t
//!		uintptr_t	unsigned integer that can safely store pointer
//!		UINT_PTR
//!		ULONG_PTR
//!		DWORD_PTR
//!
//!		ptrdiff_t	signed integer (result of subtracting two pointers)
//!		intptr_t	signed integer that can safely store pointer
//!		INT_PTR
//!		SSIZE_T
//!		LONG_PTR
//!
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	18-Nov-2015			J.Griswold
		Allow stdint.h to be included on MSVC compiler
	22-Jan-2013			J.Griswold
		Hopefully made compatible with Apple Macintosh
	22-Jun-2011			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UTypes_Root
#define _H_UTypes_Root
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <cstddef>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <stddef.h>
//#if !defined(_MSC_VER)
#include <stdint.h>
//#endif

//#include "UMachine.h"
//#if defined( CSTD_CRTDEFS )
//#	include <crtdefs.h>
//#elif defined( CSTD_UNISTD )
//#	include <unistd.h>
//#endif
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#define	UTYPETEST( x )	typedef	x	x##_TYPETEST
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef	intptr_t	index_t;		///< used for indexing into lists/arrays
typedef	intptr_t	int_t;			///< integer type sized to handle pointers

typedef	size_t		uindex_t;
typedef	size_t		uint_t;

typedef unsigned char	byte_t;



#if !defined(errno_t)  &&  !defined( __errno_t_defined )  &&  !defined( _ERRNO_T )  &&  !defined( _ERRCODE_DEFINED )
	typedef int		errno_t;
#	define __errno_t_defined
#	define _ERRNO_T
#endif

#if !defined(error_t)  &&  !defined( __error_t_defined )  &&  !defined( _ERROR_T )
	typedef int		error_t;
#	define __error_t_defined
#	define _ERROR_T
#endif

#if !defined(int8_t)  &&  !defined( __int8_t_defined )  &&  !defined( _INT8_T )
	typedef signed char		int8_t;
	typedef unsigned char	uint8_t;
#	define	__int8_t_defined
#	define	_INT8_T
#endif

#if !defined(int16_t)  &&  !defined( __int16_t_defined)  &&  !defined( _INT16_T )
#	if SHRT_MAX == 0x7FFF
		typedef short			int16_t;
		typedef unsigned short	uint16_t;
#	elif INT_MAX == 0x7FFF
		typedef int				int16_t;
		typedef unsigned int	uint16_t;
#	else
#		error no definition for int16_t;
#	endif
#	define	__int16_t_defined
#	define	_INT16_T
#endif

#if !defined(int32_t)  &&  !defined( __int32_t_defined)  &&  !defined( _INT32_T )
#	if INT_MAX == 0x7FFFFFFFL
		typedef int				int32_t;
		typedef unsigned int	uint32_t;
#	elif LONG_MAX == 0x7FFFFFFFL
		typedef long			int32_t;
		typedef unsigned long	uint32_t;
#	else
#		error no definition for int32_t or uint32_t
#	endif
#	define	__int32_t_defined
#	define	_INT32_T
#endif

#if !defined(int64_t)  &&  !defined( __int64_t_defined)  &&  !defined( _INT64_T )
#	if LONG_MAX == 0x7FFFFFFFFFFFFFFFLL
		typedef long int			int64_t;
		typedef unsigned long int	uint64_t;
#	elif LLONG_MAX == 0x7FFFFFFFFFFFFFFFLL
		typedef long long			int64_t;
		typedef unsigned long long	uint64_t;
#	else
#		error no definition for int64_t
#	endif
#	define	__int64_t_defined
#	define	_INT64_T
#endif

#if !defined(rsize_t)  &&  !defined( __rsize_t_defined )  &&  !defined( _RSIZE_T )
	typedef size_t	rsize_t;
#	define	__rsize_t_defined
#	define	_RSIZE_T
#endif


// the following provides proof as to the identified types

	UTYPETEST(index_t);
	UTYPETEST(uindex_t);
	UTYPETEST(int_t);
	UTYPETEST(uint_t);
	UTYPETEST(byte_t);
	UTYPETEST(errno_t);
	UTYPETEST(error_t);
	UTYPETEST(int8_t);
	UTYPETEST(uint8_t);
	UTYPETEST(int16_t);
	UTYPETEST(uint16_t);
	UTYPETEST(int32_t);
	UTYPETEST(uint32_t);
	UTYPETEST(int64_t);
	UTYPETEST(uint64_t);
	//UTYPETEST(size_t);
	UTYPETEST(rsize_t);


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


#endif /* _H_UTypes */

