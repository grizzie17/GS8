/*---------------------------------------------------------------------+\
|
|	THash.h  --  brief description of what THash.h is for
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
		Change enum returns to be passed by reference
	12-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add new 'Remove' function
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	11-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_THash
#define _H_THash
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TArray.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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
template < class TKey, class TData >
class THashTableEnumerator;		// forward declaration
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

// TKey must implement operation ==

template < class TKey, class TData >
class THashWallet
{
//	class lifecycle  ----------------------------------------------------
public:
					THashWallet();
	virtual			~THashWallet();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	TData*		Match( uintmax_t nSearchHash, const TKey& key );
	bool		Populate( uintmax_t nHash, const TKey& key, TData data );
	bool		Clear( void );

protected:
//	protected types  ----------------------------------------------------

	friend class THashTableEnumerator< TKey, TData >;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TKey		m_key;
	uintmax_t	m_hashValue;
	TData		m_data;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};



template < class TKey, class TData >
class THashBucket
{
//	class lifecycle  ----------------------------------------------------
public:
					THashBucket();
	virtual			~THashBucket();

public:
//	public types  -------------------------------------------------------

	typedef THashWallet< TKey, TData >	TWallet;
	typedef TWallet*					TWalletPtr;

//	public functions  ---------------------------------------------------

	TData*	Exists( uintmax_t nHash, const TKey& key );
	bool	Add( uintmax_t nHash, const TKey& key, TData data );
	bool	Remove( uintmax_t nHash, const TKey& key );

protected:
//	protected types  ----------------------------------------------------

	friend class THashTableEnumerator< TKey, TData >;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray< TWalletPtr >	m_tList;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};





template < class TKey, class TData >
class THashTable
{
//	class lifecycle  ----------------------------------------------------
public:
					THashTable();
	virtual			~THashTable();

public:
//	public types  -------------------------------------------------------

	typedef THashBucket< TKey, TData >	TBucket;
	typedef TBucket*					TBucketPtr;

//	public functions  ---------------------------------------------------

	void			SetHashTableSize( size_t nNewSize );
	uintmax_t		HashFromKey( const TKey& key );

	TData*			Find( const TKey& key );
	bool			Add( const TKey& key, TData data );
	bool			Remove( const TKey& key );
	THashTableEnumerator< TKey, TData >
					GetEnumerator( void ) const;

protected:
//	protected types  ----------------------------------------------------

	friend class THashTableEnumerator< TKey, TData >;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	TArray< TBucketPtr >	m_tBuckets;
	size_t					m_nTableSize; // size of hash table (size of Bucket list)

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

};


template < class TKey, class TData >
class THashTableEnumerator : public TEnumerator<TData>
{
//	class lifecycle  ----------------------------------------------------
public:
				THashTableEnumerator( void );
				THashTableEnumerator( const THashTable<TKey,TData>* p );
				THashTableEnumerator( const THashTableEnumerator<TKey, TData>& r );
	virtual		~THashTableEnumerator( void );

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	THashTableEnumerator<TKey, TData>&
							operator=( const THashTableEnumerator<TKey,TData>& r );		// assignment

	virtual const TKey&		Key( void );
	virtual const TData&	Value( void );

protected:
//	protected types  ----------------------------------------------------

	typedef	THashBucket< TKey, TData >*	TBucketPtr;
	typedef	THashWallet< TKey, TData >*	TWalletPtr;

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

	const THashTable<TKey, TData>*	m_pTable;
	TArrayEnumerator<TBucketPtr>	m_eBuckets;
	TArrayEnumerator<TWalletPtr>	m_eWallets;
	index_t							m_nIndex;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	TEnumerator
public:
	virtual bool	MoveNext( void );
	virtual void	Reset( void );
	virtual	TData*	Current( void );


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
template < typename TKey >
uintmax_t
		THashValueFromKey
		(
		const TKey&	//key
		)
{
	return 0;
}
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


template < class TKey, class TData >
THashTableEnumerator<TKey, TData>::THashTableEnumerator
		(
		void
		)
		: m_pTable( 0 ),
		m_eBuckets(),
		m_eWallets(),
		m_nIndex( -1 )
{
}


template < class TKey, class TData >
THashTableEnumerator<TKey, TData>::THashTableEnumerator
		(
		const THashTable< TKey, TData >* p
		)
		: m_pTable( p )
{
	m_nIndex = -1;
}

template < class TKey, class TData >
THashTableEnumerator<TKey, TData>::THashTableEnumerator
		(
		const THashTableEnumerator< TKey, TData >&	r
		)
		: m_pTable( r.m_pTable ),
		m_eBuckets( r.m_eBuckets ),
		m_eWallets( r.m_eWallets ),
		m_nIndex( r.m_nIndex )
{
}

template < class TKey, class TData >
THashTableEnumerator<TKey, TData>::~THashTableEnumerator
		(
		void
		)
{
}


template < class TKey, class TData >
THashTableEnumerator<TKey, TData>&
		THashTableEnumerator<TKey, TData>::operator =
		(
		const THashTableEnumerator<TKey,TData> &r
		)
{
	m_pTable = r.m_pTable;
	m_eBuckets = r.m_eBuckets;
	m_eWallets = r.m_eWallets;
	m_nIndex = r.m_nIndex;
	return *this;
}


template < class TKey, class TData >
bool	THashTableEnumerator<TKey, TData>::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( m_nIndex < 0 )
	{
		m_eBuckets = m_pTable->m_tBuckets.GetEnumerator();
		while ( m_eBuckets.MoveNext() )
		{
			TBucketPtr*	h;

			h = m_eBuckets.Current();
			if ( h )
			{
				if ( *h )
				{
					m_eWallets = (*h)->m_tList.GetEnumerator();
					if ( m_eWallets.MoveNext() )
					{
						m_nIndex = 0;
						bResult = true;
						break;
					}
				}
			}
		}
	}
	else
	{
		if ( m_eWallets.MoveNext() )
		{
			++m_nIndex;
			bResult = true;
		}
		else
		{
			while ( m_eBuckets.MoveNext() )
			{
				TBucketPtr*	h;

				h = m_eBuckets.Current();
				if ( h )
				{
					if ( *h )
					{
						m_eWallets = (*h)->m_tList.GetEnumerator();
						if ( m_eWallets.MoveNext() )
						{
							m_nIndex = 0;
							bResult = true;
							break;
						}
					}
				}
			}
		}
	}

	return bResult;
}

template < class TKey, class TData >
void	THashTableEnumerator<TKey, TData>::Reset
		(
		void
		)
{
	m_nIndex = -1;
}



template < class TKey, class TData >
TData*	THashTableEnumerator<TKey, TData>::Current
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
		TWalletPtr*	h;
		h = m_eWallets.Current();
		if ( h )
		{
			return &(*h)->m_data;
		}
		else
		{
			return 0;
		}
	}
}


template < class TKey, class TData >
const TKey&
		THashTableEnumerator<TKey, TData>::Key
		(
		void
		)
{
	if ( m_nIndex < 0 )
	{
		MoveNext();
	}

	TWalletPtr*	h;
	h = m_eWallets.Current();
	DbgAssert( 0 != h, "THashTableEnum::Key - bad internal pointer" );
	return (*h)->m_key;
}


template < class TKey, class TData >
const TData&
		THashTableEnumerator<TKey, TData>::Value
		(
		void
		)
{
	if ( m_nIndex < 0 )
	{
		MoveNext();
	}

	TWalletPtr*	h;
	h = m_eWallets.Current();
	DbgAssert( 0 != h, "THashTableEnumerator::Value - Bad pointer" );
	return (*h)->m_data;
}





/*=====================================================================+\
||	THashWallet Functions												|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * THashWallet - Constructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashWallet< TKey, TData >::THashWallet
		(
		void
		)
		: m_key(),
		m_hashValue( 0 ),
		m_data()
{
}

/*---------------------------------------------------------------------+\

 * ~THashWallet - Destructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashWallet< TKey, TData >::~THashWallet
		(
		void
		)
{
}

/*---------------------------------------------------------------------+\

 * Match -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	THashWallet< TKey, TData >::Match
		(
		uintmax_t	nSearchHash,
		const TKey&	key
		)
{
	TData*	pResult = 0;

	if ( nSearchHash == m_hashValue )
	{
		if ( m_key == key )
			pResult = &m_data;
	}

	return pResult;
}

/*---------------------------------------------------------------------+\

 * Populate -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	THashWallet< TKey, TData >::Populate
		(
		uintmax_t	nHash,
		const TKey&	key,
		TData		data
		)
{
	m_hashValue = nHash;
	m_key = key;
	m_data = data;
	return true;
}

template < class TKey, class TData >
bool	THashWallet< TKey, TData >::Clear
		(
		void
		)
{
	TKey	key;
	TData	data;

	m_key = key;
	m_hashValue = 0;
	m_data = data;
	return true;
}



/*=====================================================================+\
||	THashBucket Functions												|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * THashBucket - constructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashBucket< TKey, TData >::THashBucket
		(
		void
		)
		: m_tList()
{
}


/*---------------------------------------------------------------------+\

 * ~THashBucket - destructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashBucket< TKey, TData >::~THashBucket
		(
		void
		)
{
	TWalletPtr*	h = m_tList.PointArray();
	if ( h )
	{
		TWalletPtr*	hEnd = h + m_tList.Length();
		while ( h < hEnd )
		{
			if ( *h )
				delete *h;
			++h;
		}
	}
}


/*---------------------------------------------------------------------+\

 * Exists -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	THashBucket< TKey, TData >::Exists
		(
		uintmax_t	nHash,
		const TKey&	key
		)
{
	TData*		pResult = 0;
	TWalletPtr*	p = m_tList.PointArray();
	TWalletPtr*	pEnd = p + m_tList.Length();

	if ( p )
	{
		while ( p < pEnd )
		{
			if ( *p )
			{
				pResult = (*p)->Match( nHash, key );
				if ( pResult )
					break;
			}
			++p;
		}
	}
	return pResult;
}


/*---------------------------------------------------------------------+\

 * Add -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	THashBucket< TKey, TData >::Add
		(
		uintmax_t	nHash,
		const TKey&	key,
		TData		data
		)
{
	index_t		n = (index_t)m_tList.Length();
	TWalletPtr*	p = m_tList.PointItem( n );
	if ( p )
	{
		*p = new TWallet;
		if ( *p )
			(*p)->Populate( nHash, key, data );
	}

	return true;
}


/*---------------------------------------------------------------------+\

 * Remove -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	THashBucket< TKey, TData >::Remove
		(
		uintmax_t	nHash,
		const TKey&	key
		)
{
	bool		bResult = false;
	TWalletPtr*	pStart = m_tList.PointArray();
	TWalletPtr*	p = pStart;
	TWalletPtr*	pEnd = p + m_tList.Length();

	if ( p )
	{
		while ( p < pEnd )
		{
			if ( *p )
			{
				TData*	pResult = (*p)->Match( nHash, key );
				if ( pResult )
				{
					//index_t	i = p - pStart;
					//m_tList.DeleteEntry( i );
					delete *p;
					*p = 0;
					bResult = true;
					break;
				}
			}
			++p;
		}
	}
	return bResult;
}


/*=====================================================================+\
||	THash Functions														|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * THashTable - constructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashTable< TKey, TData >::THashTable
		(
		void
		)
		: m_tBuckets()
		, m_nTableSize( 0 )
{
	SetHashTableSize( 20 );
	m_tBuckets.SetBlockSize( m_nTableSize );
}


/*---------------------------------------------------------------------+\

 * ~THashTable - destructor

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashTable< TKey, TData >::~THashTable
		(
		void
		)
{
	TBucketPtr*	h = m_tBuckets.PointArray();
	if ( h )
	{
		TBucketPtr*	hEnd = h + m_tBuckets.Length();
		while ( h < hEnd )
		{
			if ( *h )
				delete *h;
			++h;
		}
	}
}


/*---------------------------------------------------------------------+\

 * SetHashTableSize -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
void	THashTable< TKey, TData >::SetHashTableSize
		(
		size_t nNewSize
		)
{
	m_nTableSize = nNewSize;
	m_tBuckets.SetBlockSize( nNewSize );
	TBucketPtr*	pEnd = m_tBuckets.PointItem( (index_t)nNewSize-1 );
	TBucketPtr*	p = m_tBuckets.PointArray();

	while ( p <= pEnd )
	{
		(*p++) = 0;
	}
}


/*---------------------------------------------------------------------+\

 * HashFromKey -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
uintmax_t
		THashTable< TKey, TData >::HashFromKey
		(
		const TKey&	key
		)
{
	return THashValueFromKey( key );
}

/*---------------------------------------------------------------------+\

 * Find -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
TData*	THashTable< TKey, TData >::Find
		(
		const TKey&	key
		)
{
	TData*			pResult = 0;
	uintmax_t		nHash = HashFromKey( key );
	index_t			nIdx = static_cast<index_t>(nHash % m_nTableSize);
	TBucketPtr*		p = m_tBuckets.PointArray( nIdx );

	if ( p )
	{
		if ( *p )
			pResult = (*p)->Exists( nHash, key );
	}

	return pResult;
}


/*---------------------------------------------------------------------+\

 * Add -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	THashTable< TKey, TData >::Add
		(
		const TKey&	key,
		TData		data
		)
{
	bool		bResult = false;
	uintmax_t	nHash = HashFromKey( key );
	index_t		nIdx = static_cast<index_t>(nHash % m_nTableSize);
	TBucketPtr*	p = m_tBuckets.PointArray( nIdx );

	if ( p  &&  *p )
	{
		TData*	pData = (*p)->Exists( nHash, key );
		if ( ! pData )
			bResult = (*p)->Add( nHash, key, data );
	}
	else
	{
		p = m_tBuckets.PointItem( nIdx );
		if ( p )
		{
			*p = new TBucket;
			if ( *p )
				bResult = (*p)->Add( nHash, key, data );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Remove -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
bool	THashTable< TKey, TData >::Remove
		(
		const TKey&	key
		)
{
	bool			bResult = false;
	uintmax_t		nHash = HashFromKey( key );
	index_t			nIdx = static_cast<index_t>(nHash % (uintmax_t)m_nTableSize);
	TBucketPtr*		p = m_tBuckets.PointArray( nIdx );

	if ( p  &&  *p )
	{
		bResult = (*p)->Remove( nHash, key );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
template < class TKey, class TData >
THashTableEnumerator< TKey, TData >
		THashTable< TKey, TData >::GetEnumerator
		(
		void
		) const
{
	return THashTableEnumerator< TKey, TData >( this );
}



NAMESPACE_COMMON_END



#endif /* _H_THash */
