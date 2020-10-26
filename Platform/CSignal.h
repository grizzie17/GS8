/*---------------------------------------------------------------------+\
|
|	CSignal.h  --  portable wrapper class for signals/events
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
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	23-Feb-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CSignal_Root
#define _H_CSignal_Root
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UPlatform.h"
#if defined( SIGNAL_POSIX )
#    include <pthread.h>
#endif
#include "UDeclPlatform.h"

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
typedef class CSignal*       CSignalPtr;
typedef class CSignal&       CSignalRef;
typedef const class CSignal& ConstCSignalRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CORE_CLASS CSignal
{
    //	class lifecycle  ----------------------------------------------------
public:
    CSignal();
    virtual ~CSignal();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    void
    Set();

    bool
    Wait();

    void
    Clear();

    bool
    IsCreated();

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

private:
    //	private types  ------------------------------------------------------

    //	private functions  --------------------------------------------------

    //	private data  -------------------------------------------------------

    bool m_bCreated;

#if defined( SIGNAL_WINDOWS )
    HANDLE m_hEvent;
    char   m_sName[32];
#elif defined( SIGNAL_POSIX )
    pthread_cond_t  m_ready;
    pthread_mutex_t m_lock;
#endif
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

}}  // namespace Yogi::Core


#endif /* _H_CSignal */
