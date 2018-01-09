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

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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
	NAMESPACE_ROOT_PREFIX CCharString
			ResolveVariable
			(
			NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef	r
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

	NAMESPACE_ROOT_PREFIX CCharString
			Substitute
			(
			NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef	rSource
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

	NAMESPACE_ROOT_PREFIX CCharString
			ProcessVariable
			(
			NAMESPACE_ROOT_PREFIX ConstCCharDescriptorRef	rVar
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

NAMESPACE_COMMON_END



#endif /* _H_CVariables */

