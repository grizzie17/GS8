/*---------------------------------------------------------------------+\
|
|	VSupports.cpp  --  base class for our COM implementations
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	02-Jul-2010			J.Griswold		(Reviewed by: PJH) [1]
		Use result code values for NResult
	05-May-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UPlatform.h"
#include "VSupports.h"

NAMESPACE_COMMON_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
long	VBaseComObject::g_nObjectCount = 0;

/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * VBaseComObject - constructor

\+---------------------------------------------------------------------*/
VBaseComObject::VBaseComObject
		(
		const char*	//sName
		)
{
	// increment the number of active objects
	//	NOTE: this should be redone in a thread safe manner
	++g_nObjectCount;

#ifdef _DEBUG
	m_nCookie = 0;	// need to register creation of object
#endif
}


/*---------------------------------------------------------------------+\

 * VBaseComObject - constructor

\+---------------------------------------------------------------------*/
//VBaseComObject::VBaseComObject
//		(
//		const VBaseComObject& //r
//		)
//{
//	// do nothing
//}


/*---------------------------------------------------------------------+\

 * ~VBaseComObject - destructor

\+---------------------------------------------------------------------*/
VBaseComObject::~VBaseComObject
		(
		void
		)
{
	// decrement number of active objects
	//	NOTE: this should be redone in a thread safe manner
	--g_nObjectCount;
}


/*---------------------------------------------------------------------+\

 * VSupports - constructor

\+---------------------------------------------------------------------*/
// we know that we use "this" in the initializer
BEGIN_IGNORE_WARNING( 4355 )

VSupports::VSupports
		(
		void
		)
		: //VBaseComObject( "Unidentified" ),
		m_nRefCount( 1 ),
		m_pOwner( INTERFACE_THIS( ISupportsNonDelegatingPtr ) )
{
}

VSupports::VSupports
		(
		ISupportsPtr	pOwner
		)
		: //VBaseComObject( "Unidentified" ),
		m_nRefCount( 1 ),
		m_pOwner( pOwner ? pOwner : INTERFACE_THIS( ISupportsNonDelegatingPtr ) )
{
}


VSupports::VSupports
		(
		const char*	,//sName,
		ISupportsPtr pOwner
		)
		: //VBaseComObject( sName ),
		m_nRefCount( 1 ),
		m_pOwner( pOwner ? pOwner : INTERFACE_THIS( ISupportsNonDelegatingPtr ) )
{
}

END_IGNORE_WARNING

/*---------------------------------------------------------------------+\

 * ~VSupports - destructor

\+---------------------------------------------------------------------*/
VSupports::~VSupports
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * QueryInterface -

\+---------------------------------------------------------------------*/
//void*	VSupports::QueryInterface
//		(
//		ConstIXIDRef	rIID,
//		NResultPtr		pResult
//		)
//{
//	return InternalQueryInterface( rIID, pResult );
//}


/*---------------------------------------------------------------------+\

 * AddRef -

\+---------------------------------------------------------------------*/
//NRefCount
//		VSupports::AddRef
//		(
//		void
//		)
//{
//	return InternalAddRef();
//}


/*---------------------------------------------------------------------+\

 * Release -

\+---------------------------------------------------------------------*/
//NRefCount
//		VSupports::Release
//		(
//		void
//		)
//{
//	return InternalRelease();
//}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * ThisQueryInterface -

\+---------------------------------------------------------------------*/
void*	VSupports::ThisQueryInterface
		(
		ConstIXIDRef	rIID,
		NResultPtr		pResult
		)
{
	ISupportsPtr	pI = 0;

	pI = static_cast<ISupportsPtr>( InternalQueryInterface( rIID, pResult ) );
	if ( pI )
	{
		// release the interface so we don't get a strangle hold on ourselves
		pI->Release();
	}

	return pI;
}



/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	VSupports::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	if ( rIID == IXID_ISupports )
	{
		ISupportsPtr	pSup = INTERFACE_THIS(ISupportsNonDelegatingPtr);
		if ( m_pOwner != pSup )
			return m_pOwner;
		else
			return pSup;
	}
	else if ( rIID == IXID_IRootSupports )
	{
		return INTERFACE_THIS(ISupportsNonDelegatingPtr);
	}
	else
	{
		return 0;
	}
}


/*---------------------------------------------------------------------+\

 * FindExternalInterface -

\+---------------------------------------------------------------------*/
void*	VSupports::FindExternalInterface
		(
		ConstIXIDRef	,//rIID
		NResultPtr		pResult
		)
{
	// override this function to implement aggregates
	//

	if ( pResult )
		*pResult = NR_E_NOTIMPL;
	return 0;
}


/*---------------------------------------------------------------------+\

 * FinalRelease -

\+---------------------------------------------------------------------*/
void	VSupports::FinalRelease
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * InternalQueryInterface -

\+---------------------------------------------------------------------*/
void*	VSupports::InternalQueryInterface
		(
		ConstIXIDRef	rIID,
		NResultPtr		pResult	// = 0
		)
{
	ISupportsPtr	pI = 0;

	pI = static_cast<ISupportsPtr>( FindInternalInterface( rIID ) );
	if ( pI )
	{
		m_pOwner->AddRef();		// addref the owner

		if ( pResult )
			*pResult = NR_S_OK;
	}
	if ( ! pI )
		pI = static_cast<ISupportsPtr>( FindExternalInterface( rIID, pResult ) );


	return pI;
}


/*---------------------------------------------------------------------+\

 * InternalAddRef -

\+---------------------------------------------------------------------*/
NRefCount
		VSupports::InternalAddRef
		(
		void
		)
{
	return ++m_nRefCount;
}


/*---------------------------------------------------------------------+\

 * InternalRelease -

\+---------------------------------------------------------------------*/
NRefCount
		VSupports::InternalRelease
		(
		void
		)
{
	NRefCount	n = 0;

	if ( 0 < m_nRefCount )
		n = --m_nRefCount;

	if ( n < 1 )
	{
		FinalRelease();
		delete this;
	}

	return n;
}



/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

