/*==================================================================*//**
*
*	@file	CMutex.h
*	@brief	create execution mutecies (locks) for threaded coded
*
*	@see	CMutexLocker
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	31-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMutex
#define _H_CMutex
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "UPlatform.h"
#if ! defined( OS_MSWIN )
#include <pthread.h>
#endif

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
typedef class CMutex*		CMutexPtr;
typedef class CMutex&		CMutexRef;
typedef const class CMutex&	ConstCMutexRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CMutex
{
//	class lifecycle  ----------------------------------------------------
public:
			CMutex();
			~CMutex();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	/**
	 * 	Lock code section
	 *
	 *	Bounded code will only execute a single thread
	 */
	void	Lock( void );

	/**
	 *	Unlock the previously locked mutex
	 */
	void	Unlock( void );

protected:
//	protected types  ----------------------------------------------------

#if defined(OS_MSWIN)
	typedef	HANDLE			XMUTEX;
#else
	typedef pthread_mutex_t	XMUTEX;
#endif

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	XMUTEX		m_mutex;
	bool		m_bCreated;
#if defined( OS_MSWIN )
	char		m_sName[32];
#endif


private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};



/**
 *	@class	CMutexLocker
 * 	@brief	helper class to allow CMutex to operate in an exception
 * 			safe manner.
 *
 *	@code

		void class::somefunction()
		{
			try {
				CMutexLocker	oLocker( &amp;m_oMutex );
				// do some stuff that must be thread locked
				// notice that when 'oLock' goes out of scope
				// the mutex is unlocked.
			} catch ( ... ) {
				// do something
			}
		}

 *	@endcode
 */
class CMutexLocker
{
public:
	inline
	CMutexLocker( CMutexPtr p )
			: m_pMutex( p )
	{
		m_pMutex->Lock();
	}

	inline
	~CMutexLocker()
	{
		if ( m_pMutex )
			m_pMutex->Unlock();
	}

protected:
	CMutexPtr	m_pMutex;

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



#endif /* _H_CMutex */

