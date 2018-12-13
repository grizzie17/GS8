/*---------------------------------------------------------------------+\
|
|	CAction.h  --  container for CTrigger objects
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
#ifndef _H_CAction
#define _H_CAction
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VAction.h"

#include "TArray.h"
#include "CTrigger.h"


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
typedef class CAction*			CActionPtr;
typedef class CAction&			CActionRef;
typedef const class CAction&	ConstCActionRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CAction : public VAction
{
//	class lifecycle  ----------------------------------------------------
public:
			CAction();
			CAction( ConstCActionRef r );	// copy constructor
	virtual	~CAction();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	CActionRef	operator=( ConstCActionRef r );		// assignment

	bool		AddTrigger( CTriggerPtr pTrigger );

	bool		Merge( CActionPtr p );

	//friend CAction;

protected:
//	protected types  ----------------------------------------------------

	typedef Yogi::Core::TArray<CTriggerPtr>	CTriggerList;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	CTriggerList	m_aTriggers;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	VAction
public:
	virtual bool	ProcessEvent( VDictionaryPtr pDict, VDictionary::Selector vEvent );

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



#endif /* _H_CAction */
