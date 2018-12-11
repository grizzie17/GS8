/*---------------------------------------------------------------------+\
|
|	CQueue.cpp  --  brief description of what CQueue.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	30-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CQueue.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CQueue - constructor

\+---------------------------------------------------------------------*/
CQueue::CQueue
		(
		void
		)
		: inherited()
{
}

/*---------------------------------------------------------------------+\

 * CQueue - copy constructor

\+---------------------------------------------------------------------*/
CQueue::CQueue
		(
		ConstCQueueRef	r
		)
		: inherited(r)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CQueue - destructor

\+---------------------------------------------------------------------*/
CQueue::~CQueue
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CQueueRef
		CQueue::operator=
		(
		ConstCQueueRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * Push -

\+---------------------------------------------------------------------*/
bool	CQueue::Push
		(
		VDictionary::Selector vItem
		)
{
	bool	bResult = false;
	bool	bFound = false;
	if ( m_pArray  &&  0 < m_nUsed )
	{
		VDictionary::Selector*	p = 0;
		VDictionary::Selector*	pEnd = 0;

		//DbgPrint( "CQueue::Push nFront = %d, nRear = %d, nUsed = %d, nAlloc = %d\n", m_nFront, m_nRear, m_nUsed, m_nAlloc );

		//	make sure that event is not already in queue
		if ( m_nFront < m_nRear )
		{
			p = m_pArray + m_nFront;
			pEnd = m_pArray + m_nRear;

			while ( p < pEnd )
			{
				if ( *p == vItem )
				{
					bFound = true;
					break;
				}
				p++;
			}
		}
		else
		{
			p = m_pArray + m_nFront;
			pEnd = m_pArray + m_nAlloc;


			while ( p < pEnd )
			{
				if ( *p == vItem )
				{
					bFound = true;
					break;
				}
				p++;
			}

			if ( ! bFound )
			{
				p = m_pArray;
				pEnd = m_pArray + m_nRear;

				while ( p < pEnd )
				{
					if ( *p == vItem )
					{
						bFound = true;
						break;
					}
					p++;
				}
			}
		}
	}
	if ( ! bFound )
	{
		bResult = AppendEntry( vItem );
	}
	return bResult;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
