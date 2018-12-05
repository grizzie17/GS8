/*---------------------------------------------------------------------+\
|
|	TPointer.h  --  Template for pointer that automatically destructs
|
|	Purpose:

		When this class' destructor is called what it is pointing to
		is deleted.

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
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Set function did not correctly set member variable
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	13-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TPointer
#define _H_TPointer
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UTypes.h"

namespace Yogi { namespace Core {
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
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/




template < class T >
class TPointer
{
//	class lifecycle  ----------------------------------------------------
public:

				TPointer();
				TPointer( T* p );
				TPointer( const TPointer<T>& r );	// copy constructor

				~TPointer();

public:
//	public types  -------------------------------------------------------

	typedef	T	element_type;

//	public functions  ---------------------------------------------------

	T&			operator=( T* p );
	T&			operator=( TPointer<T>& r );

	T&			operator*( void ) const;
	T*			operator->( void ) const;
				operator T*( void );
	T*			Get( void ) const;
	void		Set( T* p );
	void		Destroy( void );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	T*		m_p;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};

template < class T >
class TArrayPointer : public TPointer< T >
{
//	class lifecycle  ----------------------------------------------------
public:

	TArrayPointer();
	TArrayPointer( T* p );
	TArrayPointer( const TArrayPointer<T>& r );	// copy constructor

	~TArrayPointer();

public:
	//	public types  -------------------------------------------------------

	//	public functions  ---------------------------------------------------

	T&			operator [] ( index_t nIndex );
	const T&	operator [] ( index_t nIndex ) const;

	T&			operator=( T* p );

private:
//	private types  -----------------------------------------------------

	typedef TPointer<T>	inherited;
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


template < class T >
inline
TPointer<T>::TPointer
		(
		void
		)
		: m_p( 0 )
{
}


template < class T >
inline
TPointer<T>::TPointer
		(
		T *p
		)
		: m_p( p )
{
}




template < class T >
inline
TPointer<T>::TPointer
		(
		const TPointer<T> &r
		)
		: m_p( r.m_p )
{
}


template < class T >
inline
TPointer<T>::~TPointer
		(
		void
		)
{
	if ( m_p )
		delete m_p;
	m_p = 0;
}



template < class T >
inline
T&		TPointer<T>::operator =
		(
		T*	p
		)
{
	m_p = p;
	return *m_p;
}


template < class T >
inline
T&		TPointer<T>::operator =
		(
		TPointer<T>&	r
		)
{
	m_p = r.m_p;
	return *m_p;
}


template < class T >
inline
T&		TPointer<T>::operator*
		(
		void
		) const
{
	return *m_p;
}

template < class T >
inline
T*		TPointer<T>::operator->
		(
		void
		) const
{
	return m_p;
}


template < class T >
inline
		TPointer<T>::operator T*
		(
		void
		)
{
	return m_p;
}


template < class T >
inline
T*		TPointer<T>::Get
		(
		void
		) const
{
	return m_p;
}


template < class T >
void	TPointer<T>::Set
		(
		T*	p
		)
{
	m_p = p;
	return m_p;
}


template < class T >
void	TPointer<T>::Destroy
		(
		void
		)
{
	if ( m_p )
	{
		delete m_p;
		m_p = 0;
	}
}

//////////////////////////////////////////////////////


template < class T >
inline
TArrayPointer<T>::TArrayPointer
		(
		void
		)
		: inherited()
{
}


template < class T >
inline
TArrayPointer<T>::TArrayPointer
		(
		T *p
		)
		: inherited( p )
{
}




template < class T >
inline
TArrayPointer<T>::TArrayPointer
		(
		const TArrayPointer<T> &r
		)
		: inherited( r )
{
}


template < class T >
inline
TArrayPointer<T>::~TArrayPointer
		(
		void
		)
{
	if ( this->m_p )
		delete [] this->m_p;
	this->m_p = 0;
}


/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
template< class T >
inline
T&
		TArrayPointer<T>::operator []
		(
		index_t	nIndex
		)
{
	return this->m_p[ nIndex ];
}


/*--------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
template< class T >
inline
const T&
		TArrayPointer<T>::operator []
		(
		index_t	nIndex
		) const
{
	return this->m_p[ nIndex ];
}

template < class T >
inline
T&		TArrayPointer<T>::operator =
		(
		T*	p
		)
{
	this->m_p = p;
	return *this->m_p;
}



}}



#endif /* _H_TPointer */

