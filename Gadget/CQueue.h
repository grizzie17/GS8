/*---------------------------------------------------------------------+\
|
|	CQueue.h  --  brief description of what CQueue.h is for
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
	30-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CQueue
#define _H_CQueue
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TQueue.h"
#include "VDictionary.h"
#include "TArray.h"
#include "NamespaceGadget.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CQueue*		CQueuePtr;
typedef class CQueue&		CQueueRef;
typedef const class CQueue&	ConstCQueueRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CQueue : public TQueue<VDictionary::Selector>
{
//	class lifecycle  ----------------------------------------------------
public:
					CQueue();
					CQueue( ConstCQueueRef r );	// copy constructor
	virtual			~CQueue();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CQueueRef	operator=( ConstCQueueRef r );		// assignment

	bool		Push( VDictionary::Selector vItem );
	VDictionary::Selector
				Pop( void );
	bool		IsEmpty( void ) const;

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	//TArray<VDictionary::Selector>	m_aList;

private:
//	private types  ------------------------------------------------------

	typedef	TQueue<VDictionary::Selector>	inherited;

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

/*---------------------------------------------------------------------+\

 * IsEmpty -

\+---------------------------------------------------------------------*/
inline
bool	CQueue::IsEmpty
		(
		void
		) const
{
	return inherited::IsEmpty();
}

/*---------------------------------------------------------------------+\

 * Pop -

\+---------------------------------------------------------------------*/
inline
VDictionary::Selector
		CQueue::Pop
		(
		void
		)
{
	VDictionary::Selector	vItem = 0;
	FetchEntry( vItem );

	return vItem;
}



NAMESPACE_GADGET_END



#endif /* _H_CQueue */

