/*---------------------------------------------------------------------+\
|
|	IHusk.h  --  interface for generalized Husk
|
|	Purpose:
|
		A container for other containers
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
	14-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IHusk
#define _H_IHusk
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"


namespace Yogi { namespace Gadget {
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

typedef interface_ IHusk*			IHuskPtr;

extern const Yogi::Common::IXID	IXID_IHusk;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IHusk : public Yogi::Common::ISupports
{
	//
	//	AddService
	//
	//	Add a new service to the Husk
	//
	virtual
	Yogi::Core::NResult	AddService
			(
			Yogi::Common::ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	Yogi::Common::ISupportsPtr
			FindServiceByName
			(
			const char* sName
			) PURE;

	virtual
	Yogi::Common::ISupportsPtr
			FindServiceByIF
			(
			Yogi::Common::ConstIXIDRef rIID
			) PURE;



	virtual
	Yogi::Core::NResult	AddStorage
			(
			Yogi::Common::ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	Yogi::Common::ISupportsPtr
			FindStorageByName
			(
			const char* sName
			) PURE;



	virtual
	Yogi::Core::NResult	AddWidget
			(
			Yogi::Common::ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	Yogi::Common::ISupportsPtr
			MakeWidget
			(
			const char*		sName
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


#endif /* _H_IHusk */
