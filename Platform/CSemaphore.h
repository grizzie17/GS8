/*==================================================================*//**
*
*	@file	CSemaphore.h
*	@brief	encapsulate platform specific semaphore implementations
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSemaphore
#define _H_CSemaphore
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"
#if defined( SEMAPHORE_POSIX )  ||  defined( SEMAPHORE_MACINTOSH )
#	include <pthread.h>
#	include <semaphore.h>
#endif
#include "UDeclSpec.h"

namespace Yogi { namespace Core {
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
typedef class CSemaphore*		CSemaphorePtr;
typedef class CSemaphore&		CSemaphoreRef;
typedef const class CSemaphore&	ConstCSemaphoreRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS CSemaphore
{
//	class lifecycle  ----------------------------------------------------
public:
			CSemaphore();
	virtual	~CSemaphore();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


	//!	Wait for signal to be triggered
	//!
	bool	Wait
			(							//!@return true=signal, false=timeout
			unsigned	nTimeout = 0	//!< [in] milliseconds (0 == infinite)
			);


	//! Signal a semaphore
	//!
	void	Signal
			(
			void
			);



protected:
//	protected types  ----------------------------------------------------

#if defined(SEMAPHORE_WINDOWS)
	typedef	HANDLE	XSEM;
#elif defined(SEMAPHORE_POSIX)
	typedef sem_t	XSEM;
#elif defined(SEMAPHORE_MACINTOSH)
	typedef sem_t*	XSEM;
#endif

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	XSEM	m_sem;

#if defined( OS_MSWIN_WCE )
	WCHAR	m_sName[32];
#elif defined( SEMAPHORE_WINDOWS )  ||  defined( SEMAPHORE_MACINTOSH )
	char	m_sName[32];
#endif

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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



#endif /* _H_CSemaphore */

