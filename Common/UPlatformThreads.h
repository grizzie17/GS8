//=====================================================================//
//
//!	@file	UPlatformThreads.h
//!	@brief	Provide an issolation layer for dealing with thread creation
//!
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	28-Nov-2015			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UPlatformThreads
#define _H_UPlatformThreads
#pragma once
/*---------------------------------------------------------------------+\
|						
|	Include Files		
|						
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#include "UMachine.h"
#include "NamespaceCommon.h"
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
NAMESPACE_ROOT_BEGIN

#if defined( THREADS_POSIX )

	typedef	pthread_t	UThreadHdl;

	typedef void*		UThreadRtn;
	typedef	UThreadRtn	(*UThreadFunction)( void* pArg );
#	define THREADAPI

#elif defined( THREADS_WINDOWS )

	typedef	HANDLE		UThreadHdl;

	typedef	DWORD		UThreadRtn;
	typedef UThreadRtn	(WINAPI *UThreadFunction)( void* pArg );
#	define THREADAPI	WINAPI

#endif
/*---------------------------------------------------------------------+\
|						
|	Class Definitions	
|						
\+---------------------------------------------------------------------*/


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

/**
 *	@brief	ThreadCreate - start a thread
 *
 *	@see UThreadFunction
 */
UThreadHdl
		ThreadCreate					///@return handle to the thread
		(
		UThreadFunction	pFunc,			///< [in] pointer to a UThreadFunction (see above)
		void*			pArg,			///< [in] pointer to be passed to pFunc
		const char*		sName = NULL	///< [in] optional name for thread
		);

/**
 *	@brief	ThreadClose - shutdown/close a thread
 */
void	ThreadClose
		(
		UThreadHdl	hThread		///< [in] handle to thread to shutdown/close
		);


/*=====================================================================+\
||						
||	Inline Functions	
||						
\+=====================================================================*/

NAMESPACE_ROOT_END



#endif /* _H_UPlatformThreads */

