/*---------------------------------------------------------------------+\
|
|	TDictionaryIndexed.h  --  indexed collection (similar to VB Dictionary object)
|
|	Purpose:
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
	26-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Change return for enumerator to be by reference
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		new function "AddAlias" that will insert a new entry
		in key table pointing to existing entry.
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	11-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TDictionaryIndexed
#define _H_TDictionaryIndexed
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TArray.h"
#include "THash.h"

#include "LogFile.h"

namespace Yogi { namespace Common {
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
// template < class TKey, class TData >
// class TDictionaryIndexedEnumerator;		// forward declaration
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/
template < class TKey, class TData >
class TDictionaryIndexed;				// forward declaration

template < class TKey, class TData >
class TDictionaryIndexedEnumerator : public Yogi::Core::TEnumerator<TData>
{
//	class lifecycle  ----------------------------------------------------
public:
				TDictionaryIndexedEnumerator( void );
				TDictionaryIndexedEnumerator( const TDictionaryIndexed<TKey,TData>* p );
	virtual		~TDictionaryIndexedEnumerator( void );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	TDictionaryIndexedEnumerator<TKey, TData>&	operator=( const TDictionaryIndexedEnumerator<TKey,TData>& r );		// assignment

	virtual long			ID( void );
	virtual const TKey&		Key( void );
	virtual const TData&	Value( void );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	const TDictionaryIndexed<TKey, TData>*	m_pTable;
	THashTableEnumerator< TKey, index_t >	m_eKeys;
	Yogi::Core::TArrayEnumerator<TData>		m_eList;
	index_t									m_nIndex;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	TEnumerator
public:
	virtual bool			MoveNext( void );
	virtual void			Reset( void );
	virtual	const TData*	Current( void );


};




template < class TKey, class TData >
class TDictionaryIndexed
{
//	class lifecycle  ----------------------------------------------------
public:
			TDictionaryIndexed();
	virtual	~TDictionaryIndexed();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	SetHashTableSize( size_t nNewSize );

	bool	Add( const TKey& key, const TData& data );
	bool	AddAlias( const TKey& key, const TKey& alias );
	bool	Exists( const TKey& key );
	index_t	IndexOf( const TKey& key ) const;
	TData*	Items( void );
	TData*	PointArray( index_t nIndex = 0 );
	const TData* PointArrayConst( index_t nIndex = 0 ) const;

	size_t	Count( void );
	size_t	Length( void );
	TData*	Item( const TKey& key ) const;
	TData*	Find( const TKey& key ) const;
	TData*	ItemAtIndex( index_t idx ) const;

	TDictionaryIndexedEnumerator<TKey, TData>
			GetEnumerator( void );

	TData*	operator[] ( index_t idx );
	TData*	operator[] ( const TKey& key );

protected:
//	protected types  ----------------------------------------------------

	friend class TDictionaryIndexedEnumerator< TKey, TData >;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	Yogi::Core::TArray<TData>	m_aList;
	THashTable<TKey, index_t>	m_aKeys;

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

template < class TKey, class TData >
TDictionaryIndexedEnumerator<TKey, TData>::TDictionaryIndexedEnumerator
		(
		void
		)
		: m_pTable( 0 )
		, m_eKeys()
		, m_eList()
		, m_nIndex( -1 )
{
}

template < class TKey, class TData >
TDictionaryIndexedEnumerator<TKey, TData>::TDictionaryIndexedEnumerator
		(
		const TDictionaryIndexed<TKey, TData>*	p
		)
		: m_pTable( p ),
		m_eKeys(),
		m_eList(),
		m_nIndex( -1 )
{
}


template < class TKey, class TData>
TDictionaryIndexedEnumerator<TKey, TData>::~TDictionaryIndexedEnumerator
		(
		void
		)
{
	m_nIndex = -1;
}


template < class TKey, class TData >
TDictionaryIndexedEnumerator<TKey, TData>&
		TDictionaryIndexedEnumerator<TKey, TData>::operator =
		(
		const TDictionaryIndexedEnumerator<TKey, TData>& r
		)
{
	m_pTable = r.m_pTable;
	m_eKeys = r.m_eKeys;
	m_eList = r.m_eList;
	m_nIndex = r.m_nIndex;
	return *this;
}



template < class TKey, class TData >
bool	TDictionaryIndexedEnumerator<TKey, TData>::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( m_nIndex < 0 )
	{
		m_eKeys = m_pTable->m_aKeys.GetEnumerator();
		m_eList = m_pTable->m_aList.GetEnumerator();
		while ( m_eKeys.MoveNext() )
		{
			if ( m_eKeys.Current() )
			{
				m_nIndex = 0;
				bResult = true;
				break;
			}
		}
	}
	else
	{
		while ( m_eKeys.MoveNext() )
		{
			if ( m_eKeys.Current() )
			{
				++m_nIndex;
				bResult = true;
				break;
			}
		}
	}

	return bResult;
}


template < class TKey, class TData >
void	TDictionaryIndexedEnumerator<TKey, TData>::Reset
		(
		void
		)
{
	m_nIndex = -1;
}


template < class TKey, class TData >
const TData*
		TDictionaryIndexedEnumerator<TKey, TData>::Current
		(
		void
		)
{
	if ( m_nIndex < 0 )
	{
		return 0;
	}
	else
	{
		index_t	n = m_eKeys.Value();
		if ( n < 0 )
			return 0;
		else
			return m_pTable->m_aList.PointArrayConst( n );
	}
}


template < class TKey, class TData >
long	TDictionaryIndexedEnumerator<TKey, TData>::ID
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return long(m_eKeys.Value());
}


template < class TKey, class TData >
const TKey&
		TDictionaryIndexedEnumerator<TKey, TData>::Key
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_eKeys.Key();
}


template < class TKey, class TData >
const TData&
		TDictionaryIndexedEnumerator<TKey, TData>::Value
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	index_t	n = m_eKeys.Value();

	const TData*	p = m_pTable->m_aList.PointArrayConst( n );
	Yogi::Core::DbgAssert( 0 != p, "TDictionaryIndexedEnum::Value - bad internal pointer" );
	return *p;
}




/*---------------------------------------------------------------------+\

 * TDictionaryIndexed - constructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TDictionaryIndexed<TKey, TData>::TDictionaryIndexed
		(
		void
		)
		: m_aList()
		, m_aKeys()
{
}

/*---------------------------------------------------------------------+\

 * ~TDictionaryIndexed - class destructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TDictionaryIndexed<TKey, TData>::~TDictionaryIndexed
		(
		void
		)
{
}

/*---------------------------------------------------------------------+\

 * SetHashTableSize -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
void	TDictionaryIndexed<TKey, TData>::SetHashTableSize
		(
		size_t nNewSize
		)
{
	m_aKeys.SetHashTableSize( nNewSize );
}


/*---------------------------------------------------------------------+\

 * Add -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	TDictionaryIndexed<TKey, TData>::Add
		(
		const TKey&		key,
		const TData&	data
		)
{
	index_t	n = m_aList.AppendData( &data );

	return m_aKeys.Add( key, n );
}


/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	TDictionaryIndexed<TKey, TData>::AddAlias
		(
		const TKey&	key,
		const TKey&	alias
		)
{
	bool	bResult = false;
	index_t	n = this->IndexOf( key );
	if ( -1 < n )
	{
		if ( ! this->Find( alias ) )
		{
			bResult = m_aKeys.Add( alias, n );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * IndexOf -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
index_t	TDictionaryIndexed<TKey, TData>::IndexOf
		(
		const TKey&	key
		) const
{
	index_t			nIndex = -1;
	const index_t*	pd = m_aKeys.Find( key );
	if ( pd )
	{
		nIndex = *pd;
	}
	return nIndex;
}


/*---------------------------------------------------------------------+\

 * Items -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	TDictionaryIndexed<TKey, TData>::Items
		(
		void
		)
{
	return m_aList.PointArray();
}


/*---------------------------------------------------------------------+\

 * PointArray -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	TDictionaryIndexed<TKey, TData>::PointArray
		(
		index_t	nIndex
		)
{
	return m_aList.PointArray( nIndex );
}

/*---------------------------------------------------------------------+\

 * PointArrayConst -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
const TData*
		TDictionaryIndexed<TKey, TData>::PointArrayConst
		(
		index_t	nIndex
		) const
{
	return m_aList.PointArrayConst( nIndex );
}

/*---------------------------------------------------------------------+\

 * Item -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	TDictionaryIndexed<TKey, TData>::Item
		(
		const TKey &key
		) const
{
	index_t	n = IndexOf( key );
	if ( -1 < n )
		return ItemAtIndex( n );
	else
		return 0;
}

/*---------------------------------------------------------------------+\

 * Find -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
inline
TData*	TDictionaryIndexed<TKey, TData>::Find
		(
		const TKey &key
		) const
{
	return Item( key );
}

/*---------------------------------------------------------------------+\

 * ItemAtIndex -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	TDictionaryIndexed<TKey, TData>::ItemAtIndex
		(
		index_t	idx
		) const
{
	return m_aList.PointArray( idx );
}


template < class TKey, class TData >
TDictionaryIndexedEnumerator<TKey, TData>
		TDictionaryIndexed<TKey, TData>::GetEnumerator
		(
		void
		)
{
	return TDictionaryIndexedEnumerator<TKey, TData>( this );
}


/*---------------------------------------------------------------------+\

 * Count -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
size_t	TDictionaryIndexed<TKey, TData>::Count
		(
		void
		)
{
	return m_aList.Length();
}

/*---------------------------------------------------------------------+\

 * Length -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
size_t	TDictionaryIndexed<TKey, TData>::Length
		(
		void
		)
{
	return m_aList.Length();
}






}}



#endif /* _H_TDictionaryIndexed */
