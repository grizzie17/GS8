/*---------------------------------------------------------------------+\
|
|	TComPointer.h  --  Template for pointer that automatically destructs
|
|	Purpose:

		When this class' destructor is called what it is pointing to
		is released.

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
	03-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TComPointer
#define _H_TComPointer
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "IXID.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

// most of the time you will want to use the following macro instead
//	of using just the template

#define	TIP(ifname)	\
	TComPointer<ifname,&IXID_##ifname>


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/




template < class TI, const IXID* TID = 0 >
class TComPointer
{
//	class lifecycle  ----------------------------------------------------
public:

				TComPointer();
				TComPointer( ISupportsPtr p );
				TComPointer( const TComPointer<TI,TID>& r );	// copy constructor

				~TComPointer();

public:
//	public types  -------------------------------------------------------

	//typedef	TI	element_type;

//	public functions  ---------------------------------------------------

	TI*			operator=( TI* p );
	TI*			operator=( ISupportsPtr p );
	TI*			operator=( TComPointer<TI, TID>& r );

	TI*			operator->( void ) const;
				operator TI*( void );
	TI*			Get( void ) const;
	void		Set( TI* p );

	// put pointer without addref
	void		Attach( TI* p );

	// get pointer without release
	TI*			Detach( void );

	NRefCount	Release( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TI*		m_p;

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


template < class TI, const IXID* TID >
inline
TComPointer<TI,TID>::TComPointer
		(
		void
		)
		: m_p( 0 )
{
}


template < class TI, const IXID* TID >
inline
TComPointer<TI,TID>::TComPointer
		(
		ISupportsPtr	p
		)
		: m_p( 0 )
{
	if ( p )
		m_p = (TI*)p->QueryInterface( *TID );
}




template < class TI, const IXID* TID >
TComPointer<TI,TID>::TComPointer
		(
		const TComPointer<TI,TID>&	r
		)
		: m_p( 0 )
{
	if ( r.m_p )
	{
		m_p = r.m_p;
		m_p->AddRef();
	}
}


template < class TI, const IXID* TID >
TComPointer<TI,TID>::~TComPointer
		(
		void
		)
{
	if ( m_p )
		m_p->Release();

	m_p = 0;
}



template < class TI, const IXID* TID >
TI*		TComPointer<TI,TID>::operator =
		(
		TI*	p
		)
{
	TI*	pI = m_p;
	m_p = p;
	if ( m_p )
		m_p->AddRef();
	if ( pI )
		pI->Release();
	return m_p;
}


template < class TI, const IXID* TID >
TI*		TComPointer<TI,TID>::operator =
		(
		ISupportsPtr	p
		)
{
	TI*	pI = m_p;
	if ( p )
	{
		m_p = (TI*)p->QueryInterface( *TID );
	}
	else
	{
		m_p = 0;
	}
	if ( pI )
		pI->Release();
	return m_p;
}


template < class TI, const IXID* TID >
TI*		TComPointer<TI,TID>::operator =
		(
		TComPointer<TI,TID>&	r
		)
{
	TI*	pI = m_p;

	if ( r.m_p )
	{
		m_p = r.m_p;
		m_p->AddRef();
	}
	else
	{
		m_p = 0;
	}
	if ( pI )
		pI->Release();
	return m_p;
}



template < class TI, const IXID* TID >
inline
TI*		TComPointer<TI,TID>::operator->
		(
		void
		) const
{
	return m_p;
}


template < class TI, const IXID* TID >
inline
		TComPointer<TI,TID>::operator TI*
		(
		void
		)
{
	return m_p;
}


template < class TI, const IXID* TID >
inline
TI*		TComPointer<TI,TID>::Get
		(
		void
		) const
{
	return m_p;
}


template < class TI, const IXID* TID >
void	TComPointer<TI,TID>::Set
		(
		TI*	p
		)
{
	TI*	pI = m_p;
	m_p = p;
	if ( m_p )
		m_p->AddRef();
	if ( pI )
		pI->Release();
	return *m_p;
}



template < class TI, const IXID* TID >
TI*		TComPointer<TI,TID>::Detach
		(
		void
		)
{
	TI*	pI = m_p;
	m_p = 0;
	return pI;
}


template < class TI, const IXID* TID >
void	TComPointer<TI,TID>::Attach
		(
		TI*	p
		)
{
	TI*	pI = m_p;
	m_p = p;
	if ( pI )
		pI->Release();
}



template < class TI, const IXID* TID >
NRefCount
		TComPointer<TI,TID>::Release
		(
		void
		)
{
	NRefCount	n = 0;

	if ( m_p )
		n = m_p->Release();
	m_p = 0;

	return n;
}




NAMESPACE_COMMON_END



#endif /* _H_TComPointer */

