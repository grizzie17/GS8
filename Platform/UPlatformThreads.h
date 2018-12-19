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
//namespace Yogi { namespace Core {

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

//! start a thread
//!
//! @see UThreadFunction
//!
UThreadHdl
		ThreadCreate
		(								//!@return handle to the thread
		UThreadFunction	pFunc,			//!< [in] pointer to a UThreadFunction (see above)
		void*			pArg,			//!< [in] pointer to be passed to pFunc
		const char*		sName = NULL	//!< [in] optional name for thread
		);

//!	shutdown/close a thread
//!
void	ThreadClose
		(
		UThreadHdl	hThread		//!< [in] handle to thread to shutdown/close
		);


/*=====================================================================+\
||						
||	Inline Functions	
||						
\+=====================================================================*/

//}}



#endif /* _H_UPlatformThreads */

