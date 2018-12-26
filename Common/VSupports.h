//=====================================================================//
//!
//!	@file	VSupports.h
//!	@brief	Base Class for our COM implementations
//!
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		General cleanup
	05-May-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VSupports
#define _H_VSupports
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UWarnings.h"

#include "UDeclCommon.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

//!	NEW_OBJECT
//!
//!	Use this macro to create components and return the controlling ISupports
//!
#define NEW_OBJECT( classname )	\
		ROOT_ISUPPORTS( new classname() )


//!	INTERFACE_THIS
//!
//!	Helper macro for the FindInternalInterface implementation
//!
#define	INTERFACE_THIS( ifptr )	\
	BEGIN_IGNORE_WARNING(4946) \
	reinterpret_cast< Yogi::Common::ISupportsPtr>( static_cast<ifptr>( this ) ) \
	END_IGNORE_WARNING


#define	ROOT_ISUPPORTS( pThis )	\
		((Yogi::Common::ISupportsPtr)(Yogi::Common::ISupportsNonDelegatingPtr)(pThis))


#define	QI_THIS_( ifname )	static_cast<ifname*>(ThisQueryInterface( IXID_##ifname ))




//!	COM_LIFECYCLE
//!
//!	Helper macro for declaring a component class
//!
//!	Notice the copy constructor is disabled
//!
#define	COM_LIFECYCLE( sClassName )	\
public:								\
			sClassName();			\
			sClassName( Yogi::Common::ISupportsPtr pOwner );	\
			sClassName( const char* sName, Yogi::Common::ISupportsPtr pOwner );	\
protected:							\
	virtual	~sClassName();			\
private:							\
			sClassName( const sClassName& r )



//!	DECLARE_ISUPORTS
//!
//!	Helper macro for declaring component class' implments section
//!
#define	DECLARE_ISUPPORTS			\
public:								\
virtual								\
void*	QueryInterface( Yogi::Common::ConstIXIDRef rIID,  Yogi::Core::NResultPtr pResult = 0 )	\
{									\
	return GetOwner()->QueryInterface( rIID, pResult );	\
};									\
virtual								\
Yogi::Common::NRefCount	\
		AddRef( void )			\
{									\
	return GetOwner()->AddRef();	\
};									\
virtual								\
Yogi::Common::NRefCount	\
		Release( void )			\
{									\
	return GetOwner()->Release();	\
}

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {

typedef class VSupports*		VSupportsPtr;
typedef class VSupports&		VSupportsRef;
typedef const class VSupports&	ConstVSupportsRef;

// notice that we don't support an IXID for the Non-Delegating i/f
typedef interface_ ISupportsNonDelegating*	ISupportsNonDelegatingPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

// this interface is declared to remove some ambiguity from
//	the VSupports implementation.
//	Do not refer to ISupportsNonDelegating for uses outside of
//	the VSupports implementation.
interface_ ISupportsNonDelegating
{

	virtual
	void*	InternalQueryInterface
			(
			ConstIXIDRef			rIID,
			Yogi::Core::NResultPtr	pResult = 0
			) = 0;

	virtual
	NRefCount
			InternalAddRef
			(
			void
			) = 0;

	virtual
	NRefCount
			InternalRelease
			(
			void
			) = 0;
};

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS VBaseComObject
{
//	class lifecycle  ----------------------------------------------------
public:
	VBaseComObject( const char* sName );
private:
	// disable the copy constructor
	VBaseComObject( const VBaseComObject& r );
	//disable assignment operator
	void	operator = ( const VBaseComObject& r );
protected:
	virtual		~VBaseComObject();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	static long		ObjectsActive( void ) { return g_nObjectCount; };

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	static long		g_nObjectCount;

#if defined( _DEBUG )
	unsigned long	m_nCookie;
#endif

private:
//	private functions  --------------------------------------------------


//	private data  -------------------------------------------------------


};

//!	Base class used for all COM implementations
class DECL_CLASS VSupports : public ISupportsNonDelegating
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VSupports );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupportsNonDelegating
	virtual
	void*	InternalQueryInterface
			(
			ConstIXIDRef			rIID,
			Yogi::Core::NResultPtr	pResult = 0
			);

	virtual
	NRefCount
			InternalAddRef
			(
			void
			);

	virtual
	NRefCount
			InternalRelease
			(
			void
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	static long		ObjectsActive( void ) { return g_nObjectCount; };

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	void*	ThisQueryInterface
			(
			ConstIXIDRef			rIID,
			Yogi::Core::NResultPtr	pResult = 0
			);

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

	virtual
	void*	FindExternalInterface
			(
			ConstIXIDRef			rIID,
			Yogi::Core::NResultPtr	pResult
			);

	virtual
	void	FinalRelease
			(
			void
			);


	ISupportsPtr
			GetOwner
			(
			void
			) const;


	ISupportsPtr
			GetRoot
			(
			void
			);

//	protected data  -----------------------------------------------------

	volatile
	NRefCount		m_nRefCount;
	ISupportsPtr	m_pOwner;

	static long		g_nObjectCount;


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
inline
ISupportsPtr
		VSupports::GetOwner
		(
		void
		) const
{
	return m_pOwner;
}


inline
ISupportsPtr
		VSupports::GetRoot
		(
		void
		)
{
	return ROOT_ISUPPORTS(this);
}

}}



#endif /* _H_VSupports */
