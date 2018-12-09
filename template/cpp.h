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
//=====================================================================//
//
//!	@file	filename.h
//!	@brief	description of what filename.h is for
//!
//!@if optional_topics (delete if not used)
//!	@details
//!	@author	F.Lastname
//
//!	@attention
//!	@warning
//!	@note
//!	@see someOtherFile.h
//!@endif
//
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_filename
#define _H_filename
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "BaseClass.h"


/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

typedef class DerivedClass*			DerivedClassPtr;
typedef class DerivedClass&			DerivedClassRef;
typedef const class DerivedClass&	ConstDerivedClassRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class DerivedClass : public BaseClass
{
//	class lifecycle  ----------------------------------------------------
public:
					DerivedClass();
					DerivedClass( ConstDerivedClassRef r );	// copy constructor
	virtual			~DerivedClass();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	DerivedClassRef	operator=( ConstDerivedClassRef r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private types  ------------------------------------------------------

	typedef BaseClass	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

};

/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/

}}



#endif /* _H_filename */
