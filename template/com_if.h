/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "filename" to be the name of this file (no suffix).
|	globally substitute "dd-mmm-9999" to be today's date.
|	globally substitute "F.Lastname" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "IInterface" to be your interface-name.
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
#include "ISupports.h"


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

typedef interface_ IInterface*			IInterfacePtr;

extern const IXID	IXID_IInterface;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

//!	@class IInterface
//!
//!	Description of IInterface and its overall expected behaviors
//!
interface_ IInterface : public ISupports
{
	//
	//!	SomeFunction
	//!
	//!	Description of what SomeFunction is used for along with any
	//!	operational restrictions.
	//!
	virtual
	NResult	SomeFunction		//!@return description of return values
			(
			SomeType	arg1,	//!< [out] description of arg1
			AnotherType	arg2	//!< [in] description of arg2
			) PURE;
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
