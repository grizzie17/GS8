/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "DerivedClass" to be the name of this class.
|	substitute "BaseClass" to be the name of the base class.
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
/*=====================================================================*/
/**
*	@file	filename.cpp
* 	@see	filename.h
*/
/*=====================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "filename.h"
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Local defines / constants
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Local Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Public Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	 Code
||
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		void
		)
		: inherited()
{
}

/**--------------------------------------------------------------------+\

 * <summary>DerivedClass - copy constructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClass::DerivedClass
		(
		ConstDerivedClassRef	r
		)
		: inherited( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/**--------------------------------------------------------------------+\

 * <summary>~DerivedClass - destructor</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClass::~DerivedClass
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/**---------------------------------------------------------------------+\

 * <summary>operator= - assignment operator</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
DerivedClassRef
		DerivedClass::operator=
		(
		ConstDerivedClassRef	r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||
||	 Overrides
||
\+=====================================================================*/


}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/
