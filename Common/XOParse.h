/*---------------------------------------------------------------------+\
|
|	XOParse.h  --  brief description of what XOParse.h is for
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_XOParse
#define _H_XOParse
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VSupports.h"
#include "IXOParse.h"
#include "UDeclSpec.h"

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
typedef class XOParse*			XOParsePtr;
typedef class XOParse&			XOParseRef;
typedef const class XOParse&	ConstXOParseRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS XOParse : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParse );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};



class DECL_CLASS XOParseType : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseType );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};




class DECL_CLASS XOParseAttribute : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseAttribute );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};



class DECL_CLASS XOParseRoot : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseRoot );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};

class DECL_CLASS XOParseSet : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseSet );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};


class DECL_CLASS XOParseProperty : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseProperty );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

};


class DECL_CLASS XOParseNProperty : public VSupports,
					implements_ IXOParse
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( XOParseNProperty );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IInterface
	virtual
	NResult	SomeFunction
			(
			SomeType	arg1,	// OUT:	description of arg1
			AnotherType	arg2	// IN:	description of arg2
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

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


#endif /* _H_XOParse */
