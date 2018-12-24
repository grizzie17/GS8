//=====================================================================//
//!
//!	@file	ISupports.h
//!	@brief	Base Class for all Interfaces
//!
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	03-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Move definition of IXID to cpp file
		Move NResult to its own file
		Add QI_ macro
	20-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_ISupports
#define _H_ISupports
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "IXID.h"
#include "UNResult.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


#ifndef	interface_
	//! macro to make interface declaration more readable
#	define	interface_	struct
#endif

#ifndef	implements_
	//! macro to make interface implementation more readable
#	define	implements_	public virtual
#endif



#ifndef PURE
#	define	PURE	= 0
#endif


#define QI_( pobj, ifname )	static_cast<ifname*>((pobj)->QueryInterface( IXID_##ifname ))

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {

typedef	unsigned long	NRefCount;


typedef interface_ ISupports*		ISupportsPtr;
typedef interface_ ISupports&		ISupportsRef;
typedef const interface_ ISupports&	ConstISupportsRef;

extern const IXID	IXID_ISupports;

//! this is a special ID that should always return the controlling
//!	ISupports of the local object (not the owner).
extern const IXID	IXID_IRootSupports;

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

//!	Base Interface for all other interfaces
interface_ ISupports
{
	//!	QueryInterface - find the supported interface
	virtual
	void*	QueryInterface						//!@return pointer to interface
			(
			ConstIXIDRef			rIID,		//!< [in] reference to requested interface ID
			Yogi::Core::NResultPtr	pResult = 0	//!< [out] optional result
			) PURE;

	//!	AddRef - call to bump reference count
	//!
	//!	@note	automatically called by QueryInterface
	virtual
	NRefCount
			AddRef			//!@return current reference count
			(
			void
			) PURE;

	//!	Release - decrement reference count (self destruct when zero)
	//!
	//!	@note	call when you are finished with the interface/component
	virtual
	NRefCount
			Release			//!@return current reference count
			(
			void
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



#endif /* _H_ISupports */
