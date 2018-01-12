/*==================================================================*//**
*
*	@file	TArray.h
*	@brief	Template class that implements an array
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	11-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed complier error, added "=" operator
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Correct Sort algorythm
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TArray
#define _H_TArray
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TEnumerator.h"
#include "UTypes.h"

#include "NamespaceRoot.h"
NAMESPACE_ROOT_BEGIN
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
template < class T >
class TArrayEnumerator;		// forward declaration
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

//---------------
//  Exceptions
//---------------

class TArrayRange
{
public:
	index_t	nIndex;
	TArrayRange( index_t i ) : nIndex( i ) {}
};

class TArrayAlloc
{
public:
	size_t	nAllocSize;
	TArrayAlloc( size_t i ) : nAllocSize( i ) {}
};

//------------------
//  Template Class
//------------------


template< class T >
class TArray
{
//	class lifecycle  ----------------------------------------------------
public:
				TArray();
				TArray( const TArray<T>& r );	// copy constructor
				TArray( const T* pData, size_t nDataCount );
				TArray( size_t nInitialAlloc );
	virtual		~TArray();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	TArray<T>&	operator = ( const TArray<T>& r );
	T&			operator [] ( index_t nIndex );
	const T&	operator [] ( index_t nIndex ) const;
				operator T* ();
				operator const T* () const;


	void		SetBlockSize( size_t nSize );

	size_t		Length( void ) const;
	void		Clear( void );
	void		Truncate( void );
	void		AdjustUsed( size_t nSize );
	void		DeleteEntry( index_t nIndex );
	void		Sort( void );


	T*			PointArray( index_t nIndex = 0 ) const;
	T*			PointItem( index_t nIndex = 0 );


	void		LoadData( const T* pData, size_t nDataCount );
	void		LoadDataAt( index_t nIndex, const T* pData, size_t nDataCount );
	index_t		AppendData( const T* pData );
	T*			AppendArray( void );

	TArrayEnumerator<T>
				GetEnumerator( void ) const;






protected:
//	protected types  ----------------------------------------------------

	friend class TArrayEnumerator<T>;

//	protected functions  ------------------------------------------------

	void		AssureIndex( index_t nIndex );
	void		AdjustAlloc( size_t nSize );

//	protected data  -----------------------------------------------------

	T*			m_pArray;
	size_t		m_nAlloc;
	size_t		m_nUsed;
	size_t		m_nBlockSize;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


};


template < class T >
class TArrayEnumerator : public TEnumerator<T>
{
//	class lifecycle  ----------------------------------------------------
public:
				TArrayEnumerator( void );
				TArrayEnumerator( const TArray<T>* p );
	virtual		~TArrayEnumerator( void );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	TArrayEnumerator<T>&	operator=( const TArrayEnumerator<T>& r );		// assignment

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	const TArray<T>*	m_pArray;
	index_t				m_nIndex;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	TEnumerator
public:
	virtual bool	MoveNext( void );
	virtual void	Reset( void );
	virtual	T*		Current( void );


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



/*---------------------------------------------------------------------+\

 * TArray - Constructor

\+---------------------------------------------------------------------*/
template< class T >
TArray<T>::TArray
		(
		void
		)
		: m_pArray( 0 ),
		m_nAlloc( 0 ),
		m_nUsed( 0 ),
		m_nBlockSize( 4 )
{
}


/*---------------------------------------------------------------------+\

 * TArray - Copy Constructor

\+---------------------------------------------------------------------*/
template< class T >
TArray<T>::TArray
		(
		const TArray<T> &r
		)
		: m_pArray( 0 ),
		m_nAlloc( 0 ),
		m_nUsed( 0 ),
		m_nBlockSize( 4 )
{
	LoadData( r.m_pArray, r.m_nUsed );
}


/*---------------------------------------------------------------------+\

 * TArray - Loading Constructor

\+---------------------------------------------------------------------*/
template< class T >
TArray<T>::TArray
		(
		const T*	pData,
		size_t		nDataCount
		)
		: m_pArray( 0 ),
		m_nAlloc( 0 ),
		m_nUsed( 0 ),
		m_nBlockSize( 4 )
{
	LoadData( pData, nDataCount );
}


/*---------------------------------------------------------------------+\

 * TArray - Parameter Constructor

\+---------------------------------------------------------------------*/
template< class T >
TArray<T>::TArray
		(
		size_t	nInitialAlloc
		)
		: m_pArray( 0 ),
		m_nAlloc( 0 ),
		m_nUsed( 0 ),
		m_nBlockSize( 4 )
{
	AdjustAlloc( nInitialAlloc );
}


/*---------------------------------------------------------------------+\

 * ~TArray - Destructor

\+---------------------------------------------------------------------*/
template< class T >
TArray<T>::~TArray
		(
		void
		)
{
	if ( m_pArray )
	{
		Clear();
	}
}


/*---------------------------------------------------------------------+\

 * Length - used length

\+---------------------------------------------------------------------*/
template< class T >
inline
size_t	TArray<T>::Length
		(
		void
		)
		const
{
	return m_nUsed;
}

/*---------------------------------------------------------------------+\

 * Clear - free up memory

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::Clear
		(
		void
		)
{
	if ( m_pArray )
	{
		delete [] m_pArray;
		m_pArray = 0;
	}
	m_nUsed = 0;
	m_nAlloc = 0;
}


/*---------------------------------------------------------------------+\

 * Truncate - set used length to zero

\+---------------------------------------------------------------------*/
template< class T >
inline
void	TArray<T>::Truncate
		(
		void
		)
{
	m_nUsed = 0;
}



/*---------------------------------------------------------------------+\

 * Sort - sort the contents of the array

 * depends upon the less-than (<) operator

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
template< class T >
void	TArray<T>::Sort
		(
		void
		)
{
	bool	bFlag = true;
	T		tTemp;

	size_t	iEnd = m_nUsed;
	size_t	jEnd = m_nUsed - 1;
	for ( size_t i = 1; i < iEnd  &&  bFlag; ++i )
	{
		bFlag = false;
		for ( size_t j = 0; j < jEnd; ++j )
		{
			if ( m_pArray[j+1] < m_pArray[j] )
			{
				tTemp = m_pArray[j];
				m_pArray[j] = m_pArray[j+1];
				m_pArray[j+1] = tTemp;
				bFlag = true;
			}
		}
	}
}
//END_OVERRUN_WARNING





/*---------------------------------------------------------------------+\

 * PointArray - get pointer to array base

 * can return null if index is out of used bounds

\+---------------------------------------------------------------------*/
template< class T >
T*		TArray<T>::PointArray
		(
		index_t nIndex
		) const
{
	if ( nIndex < 0 )
		throw TArrayRange( nIndex );

	if ( m_nUsed < 1 )
		return 0;
	else if ( 0 <= nIndex  &&  nIndex < index_t(m_nUsed) )
		return m_pArray + nIndex;
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * PointItem - get pointer to array item

 * Assures array allocation (can return null if index negative)

\+---------------------------------------------------------------------*/
template< class T >
inline
T*		TArray<T>::PointItem
		(
		index_t	nIndex
		)
{
	AssureIndex( nIndex );
	return m_pArray + nIndex;
}


/*---------------------------------------------------------------------+\

 * LoadData - load array contents

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::LoadData
		(
		const T*	pData,
		size_t		nDataCount
		)
{
	if ( pData  &&  0 < nDataCount )
	{
		AssureIndex( (index_t)nDataCount - 1 );
		const T*	p = pData;
		const T*	pEnd = p + nDataCount;
		index_t		i = 0;
		while ( p < pEnd )
		{
			m_pArray[i++] = *p++;
		}
	}
}


/*---------------------------------------------------------------------+\

 * LoadDataAt - load list starting at index

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::LoadDataAt
		(
		index_t		nIndex,
		const T*	pData,
		size_t		nDataCount
		)
{
	if ( pData  &&  0 <= nIndex  &&  0 < nDataCount )
	{
		AssureIndex( nIndex + (index_t)(nDataCount) - 1 );

		size_t	nNewSize = nIndex + nDataCount + 1;

		const T*	p = pData;
		const T*	pEnd = p + nDataCount;
		index_t		i = nIndex;
		while ( p < pEnd )
		{
			m_pArray[i++] = *p++;
		}

		if ( nNewSize < m_nUsed )
			m_nUsed = (size_t)(nIndex) + 1;
	}
}

/*---------------------------------------------------------------------+\

 * AppendData - Append a data item

\+---------------------------------------------------------------------*/
template< class T >
index_t	TArray<T>::AppendData
		(
		const T*	pData
		)
{
	index_t	n = (index_t)Length();
	T*		p = PointItem( n );
	if ( p )
		*p = *pData;
	return n;
}


/*---------------------------------------------------------------------+\

 * AppendArray - append space and return pointer

\+---------------------------------------------------------------------*/
template< class T >
inline
T*		TArray<T>::AppendArray
		(
		void
		)
{
	index_t	n = (index_t)Length();
	return PointItem( n );
}



/*---------------------------------------------------------------------+\

 * operator = - assign copy

\+---------------------------------------------------------------------*/
template< class T >
inline
TArray<T>&
		TArray<T>::operator =
		(
		const TArray<T>&	r
		)
{
	LoadData( r.PointArray(), r.Length() );
	return *this;
}



/*---------------------------------------------------------------------+\

 * SetBlockSize - Set growth factor

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::SetBlockSize
		(
		size_t nSize
		)
{
	m_nBlockSize = nSize;
}


/*---------------------------------------------------------------------+\

 * GetEnumerator - Get an enumerator for the array

\+---------------------------------------------------------------------*/
template< class T >
TArrayEnumerator<T>
		TArray<T>::GetEnumerator
		(
		void
		) const
{
	return TArrayEnumerator<T>( this );
}


/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
template< class T >
inline
T&		TArray<T>::operator []
		(
		index_t	nIndex
		)
{
	AssureIndex( nIndex );

	return m_pArray[ nIndex ];
}


/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
template< class T >
inline
const T&
		TArray<T>::operator []
		(
		index_t	nIndex
		) const
{
	if ( index_t(m_nAlloc) < nIndex )
		throw TArrayRange( nIndex );

	return m_pArray[ nIndex ];
}

/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//T&		TArray<T>::operator []
//		(
//		int	nIndex
//		)
//{
//	AssureIndex( nIndex );
//
//	return m_pArray[ nIndex ];
//}

/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//const T&
//		TArray<T>::operator []
//		(
//		int	nIndex
//		) const
//{
//	if ( m_nAlloc < nIndex )
//		throw TArrayRange( nIndex );
//	//AssureIndex( nIndex );
//
//	return m_pArray[ nIndex ];
//}

/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//inline
//T&		TArray<T>::operator []
//		(
//		short nIndex
//		)
//{
//	return operator []( long(nIndex) );
//}

/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//T		TArray<T>::operator []
//		(
//		int nIndex
//		)
//{
//	AssureIndex( nIndex );
//
//	return m_pArray[ nIndex ];
//}

/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//inline
//T		TArray<T>::operator []
//		(
//		short nIndex
//		) const
//{
//	AssureIndex( nIndex );
//
//	return m_pArray[ nIndex ];
//}


/*---------------------------------------------------------------------+\

 * operator [] -

\+---------------------------------------------------------------------*/
//template< class T >
//inline
//T		TArray<T>::operator []
//		(
//		long nIndex
//		)
//{
//	AssureIndex( nIndex );
//
//	return m_pArray[ nIndex ];
//}



/*---------------------------------------------------------------------+\

 * operator T* -

\+---------------------------------------------------------------------*/
template< class T >
inline
		TArray<T>::operator T*
		(
		void
		)
{
	return m_pArray;
}


/*---------------------------------------------------------------------+\

 * operator const T* -

\+---------------------------------------------------------------------*/
template< class T >
inline
		TArray<T>::operator const T*
		(
		void
		)
		const
{
	return m_pArray;
}


/*---------------------------------------------------------------------+\

 * AssureIndex - assure used location

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::AssureIndex
		(
		index_t	nIndex
		)
{
	if ( nIndex < 0 )
		throw TArrayRange( nIndex );

	if ( nIndex < index_t(m_nUsed) )
		return;		// we are within range so just return

	size_t	nSize = static_cast<size_t>(nIndex + 1);

	if ( m_nBlockSize < 1 )
		m_nBlockSize = 2;

	size_t	nNewAlloc = nSize + (m_nBlockSize - nSize % m_nBlockSize);
	T*		pNew;

	if ( 0 < m_nAlloc )
	{
		if ( nIndex < index_t(m_nAlloc) )
		{
			m_nUsed = nSize;
		}
		else
		{
			// we need to adjust the array buffer

			pNew = new T[nNewAlloc];
			if ( ! pNew )
				throw TArrayAlloc( nNewAlloc );

			if ( 0 < m_nUsed )
			{
				T*	d = pNew;
				T*	s = m_pArray;
				T*	sEnd = s + m_nUsed;
				while ( s < sEnd )
					*d++ = *s++;
			}

			delete [] m_pArray;
			m_pArray = pNew;
			m_nAlloc = nNewAlloc;
			m_nUsed = nSize;
		}
	}
	else
	{
		// we need to allocate the array

		pNew = new T[nNewAlloc];
		if ( ! pNew )
			throw TArrayAlloc( nNewAlloc );

		m_pArray = pNew;
		m_nAlloc = nNewAlloc;
		m_nUsed = nSize;
	}
}




/*---------------------------------------------------------------------+\

 * AdjustAlloc - change allocated memory

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::AdjustAlloc
		(
		size_t nSize
		)
{
	if ( 0 <= nSize )
	{
		size_t	nNewAlloc;

		if ( m_nBlockSize < 1 )
			m_nBlockSize = 2;
		nNewAlloc = nSize + (m_nBlockSize - nSize % m_nBlockSize);

		if ( m_pArray )
		{
			if ( m_nAlloc < nNewAlloc )
			{
				T*	p;

				p = new T[ nNewAlloc ];
				if ( 0 == p )
					throw TArrayAlloc( nNewAlloc );

				if ( 0 < m_nUsed )
				{
					T*	s = m_pArray;
					T*	sEnd = s + m_nUsed;
					T*	d = p;
					while ( s < sEnd )
						*d++ = *s++;
				}

				delete [] m_pArray;
				m_pArray = p;
			}
			else
			{
				nNewAlloc = m_nAlloc;
			}
			if ( nNewAlloc < m_nUsed )
				m_nUsed = nNewAlloc;
		}
		else
		{
			m_pArray = new T[ nNewAlloc ];
			if ( 0 == m_pArray )
				throw TArrayAlloc( nNewAlloc );
		}
		m_nAlloc = nNewAlloc;
	}
}

/*---------------------------------------------------------------------+\

 * AdjustUsed - change the number of used entries

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::AdjustUsed
		(
		size_t nSize
		)
{
	if ( 0 <= nSize )
	{
		if ( m_nAlloc < nSize )
			AdjustAlloc( nSize );

		m_nUsed = nSize;
	}
}


/*---------------------------------------------------------------------+\

 * DeleteEntry - Delete entry and compress array

\+---------------------------------------------------------------------*/
template< class T >
void	TArray<T>::DeleteEntry
		(
		index_t	nIndex
		)
{
	if ( -1 < nIndex  &&  nIndex < m_nUsed )
	{
		T*	t = m_pArray + nIndex;
		T*	p = t + 1;
		T*	pEnd = m_pArray + m_nUsed;
		while ( p < pEnd )
			*t++ = *p++;
		--m_nUsed;
	}
}



/*=====================================================================+\
||	TArrayEnumerator Implementation
\+=====================================================================*/



template< class T >
TArrayEnumerator<T>::TArrayEnumerator
		(
		void
		)
		: m_pArray( 0 ),
		m_nIndex( -1 )
{
}


template< class T >
TArrayEnumerator<T>::TArrayEnumerator
		(
		const TArray<T>*	p
		)
		: m_pArray( p ),
		m_nIndex( -1 )
{
}

template < class T >
TArrayEnumerator<T>::~TArrayEnumerator
		(
		void
		)
{
}

template < class T >
TArrayEnumerator<T>&
		TArrayEnumerator<T>::operator =
		(
		const TArrayEnumerator<T>&	r
		)
{
	m_pArray = r.m_pArray;
	m_nIndex = r.m_nIndex;
	return *this;
}

template< class T >
bool	TArrayEnumerator<T>::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_pArray->m_nUsed )
	{
		bResult = true;
		if ( m_nIndex < 0 )
			m_nIndex = 0;
		else if ( m_nIndex < index_t(m_pArray->m_nUsed-1) )
			++m_nIndex;
		else
			bResult = false;
	}
	return bResult;
}


template< class T >
void	TArrayEnumerator<T>::Reset
		(
		void
		)
{
	m_nIndex = -1;
}


template< class T >
inline
T*		TArrayEnumerator<T>::Current
		(
		void
		)
{
	if ( m_nIndex < 0 )
		return 0;
	else
		return m_pArray->PointArray( m_nIndex );
}






NAMESPACE_ROOT_END




#endif /* _H_TArray */

