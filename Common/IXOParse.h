/*---------------------------------------------------------------------+\
|
|	IXOParse.h  --  brief description of what IXOParse.h is for
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
	18-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IXOParse
#define _H_IXOParse
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

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

typedef interface_ IXOParse*			IXOParsePtr;
typedef interface_ IXOParseType*		IXOParseTypePtr;
typedef interface_ IXOParseAttribute*	IXOParseAttributePtr;
typedef interface_ IXOParseProperty*	IXOParsePropertyPtr;
typedef interface_ IXOParseNProperty*	IXOParseNPropertyPtr;
typedef interface_ IXOParseSet*			IXOParseSetPtr;
typedef interface_ IXOParseRoot*		IXOParseRootPtr;

extern const IXID	IXID_IXOParse;
extern const IXID	IXID_IXOParseType;
extern const IXID	IXID_IXOParseAttribute;
extern const IXID	IXID_IXOParseProperty;
extern const IXID	IXID_IXOParseNProperty;
extern const IXID	IXID_IXOParseSet;
extern const IXID	IXID_IXOParseRoot;


typedef int	SomeType;
typedef int	AnotherType;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IXOParse : public ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseType : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseAttribute : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseProperty : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseNProperty : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseSet : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
};


interface_ IXOParseRoot : public IXOParse
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult
			SomeFunction2
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			) PURE;
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


#endif /* _H_IXOParse */

