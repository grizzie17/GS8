/*---------------------------------------------------------------------+\
|
|	CDictPageEvents.h  --  Lazy Load of Variables
|
|	Purpose:

		Dynamically creates variables when requesting selector.

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
	17-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Better support the "standard" update functions
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDictPageEvents
#define _H_CDictPageEvents
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CDictPageLazyLoad.h"
#include "CQueue.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CDictPageEvents*			CDictPageEventsPtr;
typedef class CDictPageEvents&			CDictPageEventsRef;
typedef const class CDictPageEvents&	ConstCDictPageEventsRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDictPageEvents : public CDictPageLazyLoad
{
//	class lifecycle  ----------------------------------------------------
public:
					CDictPageEvents();
	virtual			~CDictPageEvents();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void		SetEventQueue( CQueuePtr p );
	CQueuePtr	EventQueue( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CQueuePtr	m_pEventQueue;	// memory managed elswhere

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VDictionaryPage
public:
	virtual bool	PutData( unsigned long nSel, Yogi::Common::ConstCVariantDataPtr pData );

	virtual bool	UpdateByName( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Common::ConstCVariantDataRef rData );
	virtual bool	UpdateEntry( unsigned long nSel, Yogi::Common::ConstCVariantDataRef rData );

	virtual bool	AddAlias( Yogi::Core::ConstCCharDescriptorRef rKey, Yogi::Core::ConstCCharDescriptorRef rAlias );

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



#endif /* _H_CDictPageEvents */
