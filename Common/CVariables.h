/*---------------------------------------------------------------------+\
|
|	CVariables.h  --  brief description of what CVariables.h is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CVariables
#define _H_CVariables
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "ISupports.h"

#include "CCharString.h"

namespace Yogi { namespace Common {
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
typedef class CVariables*		CVariablesPtr;
typedef class CVariables&		CVariablesRef;
typedef const class CVariables&	ConstCVariablesRef;


typedef class VVariable*		VVariablePtr;


/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

class VVariable
{
public:

	virtual
	Yogi::Core::CCharString
			ResolveVariable
			(
			Yogi::Core::ConstCCharDescriptorRef	r
			) = 0;
};

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CVariables
{
//	class lifecycle  ----------------------------------------------------
public:
					CVariables();
					CVariables( VVariablePtr pVariable );
	virtual			~CVariables();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	Yogi::Core::CCharString
			Substitute
			(
			Yogi::Core::ConstCCharDescriptorRef	rSource
			);


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	long	SpanConstant
			(
			const char*	pStart,
			const char*	pEnd
			);

	long	SpanVariable
			(
			const char*	pStart,
			const char*	pEnd
			);

	Yogi::Core::CCharString
			ProcessVariable
			(
			Yogi::Core::ConstCCharDescriptorRef	rVar
			);

//	protected data  -----------------------------------------------------

	VVariablePtr	m_pVariable;

private:
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



#endif /* _H_CVariables */

