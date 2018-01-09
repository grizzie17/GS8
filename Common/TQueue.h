/*---------------------------------------------------------------------+\
|
|	TQueue.h  --  circular queue (ring buffer)
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
	12-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TQueue
#define _H_TQueue
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CMutex.h"
#include "CSemaphore.h"
#include "UMath.h"
#include "LogFile.h"

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
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

template < class T >
class TQueue
{
//	class lifecycle  ----------------------------------------------------
public:
			TQueue();
	virtual	~TQueue();

public:
//	public types  -------------------------------------------------------

	typedef	T	ThisType;

	typedef struct Descriptor
	{
		ThisType*	p;		// pointer to entries
		size_t		n;		// number of entries

		Descriptor() : p(0), n(0) {};
	} Descriptor;

	typedef struct Enumerator
	{
		Descriptor	v[2];	// vector of descriptors
		int			i;		// index to vectors
		ThisType*	p;
		ThisType*	pEnd;

		Enumerator() : v(), i(-1), p(0), pEnd(0) {};

		void	Reset()
		{
			v[0].p = 0;
			v[0].n = 0;
			v[1].p = 0;
			v[1].n = 0;
			i = -1;
			p = 0;
			pEnd = 0;
		};

		inline
		size_t	Length() { return v[0].n + v[1].n; };
		inline
		bool	IsEnd() { return 1 < i; };
		inline
		bool	MoveNext()
		{
			bool	bResult = false;

			if ( i < 0 )
			{
				i = 0;
				p = v[i].p;
				pEnd = p + v[i].n;
				if ( p )
					bResult = true;
			}
			else
			{
				++p;
				if ( p < pEnd )
				{
					bResult = true;
				}
				else
				{
					++i;
					if ( i < 2 )
					{
						if ( 0 < v[i].n )
						{
							p = v[i].p;
							pEnd = p + v[i].n;
							bResult = true;
						}
						else
						{
							p = 0;
							pEnd = 0;
						}
					}
				}
			}
			return bResult;
		};

		inline T*	Current() { return p; };

	} Enumerator;



//	public functions  ---------------------------------------------------

	/**
	 * @brief operator assign - append operand to queue
	 */
	TQueue<T>&
			operator = ( const T& r );

	/**
	 * @brief operator T - Fetch next entry from the queue
	 *
	 * @see FetchEntry
	 */
			operator T ();

	/**
	 * @brief WaitForReadData - wait until data has been written to buffer
	 *
	 * This function uses a semaphore to coordinate access to the buffer
	 */
	bool	WaitForReadData					///@return is data available
			(
			unsigned int	nTimeout = 0	///< [in] milliseconds to wait (zero is infinite)
			);

	/**
	 * @brief ReleaseReadData - will force the semaphore to be released
	 *
	 * This function should be called only when you need to notify
	 * the receiver that you are done.
	 *
	 * Under normal circumstances WriteAdvance or Append will do this
	 * for you.
	 */
	void	ReleaseReadData
			(
			void
			);

	/**
	 * @brief GetReadEnumerator - get an Enumerator to the data that is ready to be read
	 *
	 * It should be noted that this function does NOT advance the read pointer.
	 * Once you have completed using the vec call ReadAdvance.
	 */
	size_t	GetReadEnumerator	///@return number of items identified
			(
			Enumerator&	rEnum	///< [out] enumerator for read
			);

	/**
	 * @brief ReadAdvance - advance the read position by count
	 */
	size_t	ReadAdvance		///@return should be the same as nCount
			(
			size_t	nCount	///< [in] number of entries to consume
			);

	/**
	 * @brief ReadAdvance - advance the read position by QDescVec
	 */
	size_t	ReadAdvance			///@return how much the read pointer was advanced
			(
			Enumerator&	rEnum	///< [in] assume that the entire enumerator was read
			);

	/**
	 * @brief FetchEntry - fetch one entry
	 */
	bool	FetchEntry		///@return true if an entry is fetched
			(
			T& rEntry		///< [out] reference to receive the entry
			);

	/**
	 * @brief FetchEntries - get a requested set of entries
	 *
	 * This function will request a number of entries to be copied into
	 * the receiving pList.
	 */
	size_t	FetchEntries		///@return actual count of retrieved entries
			(
			T*		pList,		///< [out] buffer to receive entries
			size_t	nCount		///< [in] count of entries requested
			);


	/**
	 * @brief WaitForWriteData - wait until data has been written to buffer
	 *
	 * This function uses a semaphore to coordinate access to the buffer
	 */
	bool	WaitForWriteData				///@return is writeable available
			(
			unsigned int	nTimeout = 0	///< [in] milliseconds to wait (zero is infinite)
			);

	/**
	 * @brief ReleaseWriteData - will force the semaphore to be released
	 *
	 * This function should be called only when you need to notify
	 * the receiver that you are done.
	 *
	 * Under normal circumstances WriteAdvance or Append will do this
	 * for you.
	 */
	void	ReleaseWriteData
			(
			void
			);

	/**
	 * @brief GetWriteEnumerator - get an enumerator to the write buffer
	 */
	size_t	GetWriteEnumerator			///@return the number of available entries
			(
			Enumerator&	rEnum,			///< [out] an Enumerator
			size_t		nRequest = 0	///< [in] requested number of entries
			);

	/**
	 * @brief WriteAdvance - advance the write pointer
	 *
	 * This function identifies how many entries were written to the ring-buffer
	 * after the call to GetWriteVector.
	 */
	size_t	WriteAdvance		///@return amount the write pointer was advanced
			(
			size_t	nCount		///< [in] amount to advance the write pointer
			);

	/**
	 * @brief AppendEntry - add an item into the ring-buffer
	 */
	bool	AppendEntry			///@return the success of the append operation
			(
			const T& rEntry		///< [in] item to be appended
			);

	/**
	 * @brief AppendEntries - add a list of items to the queue (ring-buffer)
	 */
	bool	AppendEntries		///@return the success of the append operation
			(
			const T*	pList,	///< [in] the list of items to append
			size_t		nCount	///< [in] the count of items to be appended
			);

	/**
	 * @brief Length - get the number of entries ready to be read
	 */
	size_t	Length( void ) const;	///@return count of available entries

	/**
	 * @brief Available - get the number of entries available
	 */
	size_t	Available( void ) const;

	/**
	 * @brief IsEmpty - is the queue (ring-buffer) empty
	 */
	bool	IsEmpty( void ) const;

	/**
	 * @brief RemoveEntry - advance the read buffer by one entry
	 */
	bool	RemoveEntry( void );

	/**
	 * @brief Clear - empty and reset the queue (ring-buffer)
	 */
	void	Clear( void );


	void	SetBlockSize( size_t nSize );
	bool	SetInitialSize( size_t nSize );


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	bool	GrowQueue( size_t n = 1 );

//	protected data  -----------------------------------------------------

	T*			m_pArray;
	size_t		m_nAlloc;
	size_t		m_nUsed;
	size_t		m_nBlockSize;

	size_t		m_nFront;	// index of next read
	size_t		m_nRear;	// index of next write

	NAMESPACE_ROOT_PREFIX CMutex		m_oMutex;
	NAMESPACE_ROOT_PREFIX CSemaphore	m_oSemaphoreRead;
	NAMESPACE_ROOT_PREFIX CSemaphore	m_oSemaphoreWrite;
	bool		m_bWaitingRead;	// is there is semaphore active
	bool		m_bWaitingWrite;

private:
//	private types  ------------------------------------------------------

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


/*---------------------------------------------------------------------+\

 * TQueue - Constructor

\+---------------------------------------------------------------------*/
template < class T >
TQueue<T>::TQueue
		(
		void
		)
		:
		m_pArray( 0 ),
		m_nAlloc( 0 ),
		m_nUsed( 0 ),
		m_nBlockSize( 4 ),
		m_nFront( 0 ),
		m_nRear( 0 ),
		m_oMutex(),
		m_oSemaphoreRead(),
		m_oSemaphoreWrite(),
		m_bWaitingRead( false ),
		m_bWaitingWrite( false )
{
}

/*---------------------------------------------------------------------+\

 * ~TQueue - Destructor

\+---------------------------------------------------------------------*/
template < class T >
TQueue<T>::~TQueue
		(
		void
		)
{
	delete [] this->m_pArray;
}


/*---------------------------------------------------------------------+\

 * operator = - append queue

\+---------------------------------------------------------------------*/
template < class T >
inline
TQueue<T>&
		TQueue<T>::operator =
		(
		const T&	r
		)
{
	AppendEntry( r );
	return *this;
}


/*---------------------------------------------------------------------+\

 * operator T - fetch entry

\+---------------------------------------------------------------------*/
template < class T >
TQueue<T>::operator T
		(
		void
		)
{
	T	tTemp;

	FetchEntry( tTemp );

	return tTemp;
}


/*---------------------------------------------------------------------+\

 * WaitForWriteData - wait for data in the queue

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::WaitForWriteData
		(
		unsigned int	nTimeout // = 0
		)
{
	bool	bResult = false;

	if ( 0 < this->Available() )
	{
		CMutexLocker	locker( &this->m_oMutex );
		this->m_bWaitingWrite = false;
		bResult = true;
	}
	else
	{
		{
			CMutexLocker	locker( &this->m_oMutex );
			this->m_bWaitingWrite = true;
		}
		//DbgPrint( "w" );
		bResult = this->m_oSemaphoreWrite.Wait( nTimeout );
		this->m_bWaitingWrite = false;
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * GetWriteEnumerator

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::GetWriteEnumerator
		(
		Enumerator&	rEnum,
		size_t		nRequested // = 0
		)
{
	size_t	nResult = 0;

	bool	b = true;

	rEnum.Reset();

	CMutexLocker	lock( &this->m_oMutex );

	if ( 0 < nRequested )
	{
		if ( 0 < this->m_nBlockSize )
		{
			if ( this->m_nAlloc < this->m_nUsed + nRequested )
				b = GrowQueue( nRequested );
		}
		else
		{
			if ( this->m_nAlloc < this->m_nUsed + nRequested )
			{
				nRequested = this->m_nAlloc - this->m_nUsed;
				if ( nRequested < 1 )
					b = false;
			}
		}
	}
	else
	{
		nRequested = this->m_nAlloc - this->m_nUsed;
	}

	if ( 0 < this->m_nAlloc  && b )	// (b) make sure grow queue was successful
	{
		if ( this->m_nRear < this->m_nFront )
		{
			rEnum.v[0].p = this->m_pArray + this->m_nRear;
			rEnum.v[0].n = umin( this->m_nFront - this->m_nRear, nRequested );
			nResult += rEnum.v[0].n;
		}
		else
		{
			rEnum.v[0].p = this->m_pArray + this->m_nRear;
			rEnum.v[0].n = umin( this->m_nAlloc - this->m_nRear, nRequested );
			nResult += rEnum.v[0].n;
			nRequested -= rEnum.v[0].n;
			if ( 0 < m_nFront  &&  0 < nRequested )
			{
				rEnum.v[1].p = this->m_pArray;
				rEnum.v[1].n = umin( this->m_nFront + 1, nRequested );
				nResult += rEnum.v[1].n;
			}
		}
	}

	return nResult;
}

/*---------------------------------------------------------------------+\

 * WriteAdvance - advance the write pointer

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::WriteAdvance
		(
		size_t	nCount
		)
{
	size_t	nResult = 0;

	if ( 0 < nCount )
	{
		{ // scope mutex
			CMutexLocker	locker( &this->m_oMutex );
			nCount = umin( nCount, this->m_nAlloc - this->m_nUsed );
			size_t	n = this->m_nRear + nCount;
			this->m_nRear = n % this->m_nAlloc;
			this->m_nUsed += nCount;
			nResult = nCount;
		}
		if ( this->m_bWaitingRead )
			this->m_oSemaphoreRead.Signal();
	}

	return nResult;
}


/*---------------------------------------------------------------------+\

 * AppendEntry - append queue

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::AppendEntry
		(
		const T&	rItem
		)
{
	bool	bResult = true;

	CMutexLocker	lock( &this->m_oMutex );

	if ( this->m_nAlloc < this->m_nUsed + 1 )
		bResult = GrowQueue( 1 );

	if ( bResult )
	{
		size_t	n = this->m_nRear;

		this->m_nRear = (this->m_nRear + 1) % this->m_nAlloc;

		this->m_pArray[n] = rItem;
		++this->m_nUsed;
		if ( this->m_bWaitingRead )
			this->m_oSemaphoreRead.Signal();

		//DbgPrint( "TQueue<T>::AppendEntry alloc = %ld, used = %ld\n", m_nAlloc, m_nUsed );
		DbgAssert( ((this->m_nFront != this->m_nRear) && (this->m_nUsed < this->m_nAlloc))
				|| ((this->m_nRear == this->m_nFront) && (this->m_nUsed == this->m_nAlloc)),
				"TQueue<T>::AppendEntry - Front=%d & Rear=%d index problems (used=%d)\n",
				this->m_nFront, this->m_nRear, this->m_nUsed );
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * AppendEntries - append ring buffer

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::AppendEntries
		(
		const T*	pList,
		size_t		nCount
		)
{
	bool	bResult = true;

	CMutexLocker	lock( &this->m_oMutex );

	if ( this->m_nAlloc < this->m_nUsed + nCount )
		bResult = GrowQueue( nCount );

	if ( bResult )
	{
		const T*	p = pList;
		const T*	pEnd = p + nCount;


		while ( p < pEnd )
		{
			this->m_pArray[this->m_nRear] = *p;
			this->m_nRear = (this->m_nRear + 1) % this->m_nAlloc;
			++p;
		}

		this->m_nUsed += nCount;
		if ( this->m_bWaitingRead )
			this->m_oSemaphoreRead.Signal();

	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * WaitForData - wait for data in the queue

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::WaitForReadData
		(
		unsigned int	nTimeout // = 0
		)
{
	bool	bResult = false;

	if ( 0 < this->Length() )
	{
		CMutexLocker	locker( &this->m_oMutex );
		this->m_bWaitingRead = false;
		bResult = true;
	}
	else
	{
		{
			CMutexLocker	locker( &this->m_oMutex );
			this->m_bWaitingRead = true;
		}
		//DbgPrint( "w" );
		bResult = this->m_oSemaphoreRead.Wait( nTimeout );
		this->m_bWaitingRead = false;
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * ReleaseReadData - force the data to be released even if nothing is there

\+---------------------------------------------------------------------*/
template < class T >
void	TQueue<T>::ReleaseReadData
		(
		void
		)
{
	if ( this->m_bWaitingRead )
	{
		this->m_oSemaphoreRead.Signal();
		this->m_bWaitingRead = false;
	}
}

/*---------------------------------------------------------------------+\

 * ReleaseWriteData - force the data to be released even if nothing is there

\+---------------------------------------------------------------------*/
template < class T >
void	TQueue<T>::ReleaseWriteData
		(
		void
		)
{
	if ( this->m_bWaitingWrite )
	{
		this->m_oSemaphoreWrite.Signal();
		this->m_bWaitingWrite = false;
	}
}


/*---------------------------------------------------------------------+\

 * GetReadEnumerator - append queue

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::GetReadEnumerator
		(
		Enumerator&	rEnum
		)
{
	size_t	nResult = 0;

	rEnum.Reset();

	if ( 0 < this->m_nUsed )
	{
		CMutexLocker	lock( &this->m_oMutex );
		if ( this->m_nFront < this->m_nRear )
		{
			rEnum.v[0].p = this->m_pArray + this->m_nFront;
			rEnum.v[0].n = this->m_nUsed;
			nResult = this->m_nUsed;
		}
		else
		{
			rEnum.v[0].p = this->m_pArray + this->m_nFront;
			rEnum.v[0].n = this->m_nAlloc - this->m_nFront;
			rEnum.v[1].p = this->m_pArray;
			rEnum.v[1].n = this->m_nRear;
			nResult = rEnum.Length();
		}
	}

	return nResult;
}

/*---------------------------------------------------------------------+\

 * ReadAdvance - Advance the read index

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::ReadAdvance
		(
		size_t	nCount			///< [in] number of entries to consume
		)
{
	size_t	nResult = 0;

	if ( 0 < nCount )
	{
		{
		CMutexLocker	locker( &this->m_oMutex);
		nCount = umin( nCount, this->m_nUsed );
		size_t	n = this->m_nFront + nCount;
		this->m_nFront = n % this->m_nAlloc;
		this->m_nUsed -= nCount;
		nResult = nCount;
		}
		if ( this->m_bWaitingWrite )
			this->m_oSemaphoreWrite.Signal();
	}

	return nResult;
}

/*---------------------------------------------------------------------+\

 * ReadAdvance - Advance the read index

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::ReadAdvance
		(
		Enumerator&	rEnum
		)
{
	return this->ReadAdvance( rEnum.Length() );
}


/*---------------------------------------------------------------------+\

 * FetchEntry - Fetch next entry in queue

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::FetchEntry
		(
		T&	rEntry
		)
{
	bool	bResult = false;

	if ( 0 < this->m_nUsed )
	{
		CMutexLocker	lock( &this->m_oMutex );
		T		tTemp = 0;
		size_t	n = this->m_nFront;

		bResult = true;
		this->m_nUsed--;
		if ( 0 < this->m_nUsed )
		{
			this->m_nFront = (this->m_nFront + 1) % this->m_nAlloc;
		}
		else
		{
			this->m_nFront = 0;
			this->m_nRear = 0;
		}

		rEntry = this->m_pArray[n];
		this->m_pArray[n] = tTemp;

		if ( this->m_bWaitingWrite )
			this->m_oSemaphoreWrite.Signal();

		//DbgPrint( "TQueue<T>::FetchEntry used = %ld\n", m_nUsed );
		DbgAssert( ((this->m_nFront != this->m_nRear) && (this->m_nUsed < this->m_nAlloc))
				|| ((this->m_nRear == this->m_nFront) && (0 == this->m_nUsed)),
			"TQueue<T>::FetchEntry - Front=%d & Rear=%d index problems (used=%d)\n",
			this->m_nFront, this->m_nRear, this->m_nUsed );
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * FetchEntries - Fetch a list of entries from the queue

\+---------------------------------------------------------------------*/
template < class T >
size_t	TQueue<T>::FetchEntries
		(
		T*		pList,
		size_t	nCount
		)
{
	size_t	nResult = 0;

	if ( 0 < this->m_nUsed )
	{
		CMutexLocker	lock( &this->m_oMutex );
		T		tTemp = 0;
		size_t	n = this->m_nFront;
		T*		p = pList;
		T*		pEnd = p + nCount;

		while ( p < pEnd  &&  0 < this->m_nUsed )
		{
			*p = this->m_pArray[n];
			this->m_pArray[n] = tTemp;
			n = (n + 1) % this->m_nAlloc;
			++p;
			++nResult;
			--this->m_nUsed;
		}

		this->m_nFront = n;

		if ( this->m_bWaitingWrite )
			this->m_oSemaphoreWrite.Signal();
	}

	return nResult;
}


/*---------------------------------------------------------------------+\

 * Length - how many entries are in the queue

\+---------------------------------------------------------------------*/
template < class T >
inline
size_t	TQueue<T>::Length
		(
		void
		) const
{
	return this->m_nUsed;
}


/*---------------------------------------------------------------------+\

 * Available - how many empty entries are available

\+---------------------------------------------------------------------*/
template < class T >
inline
size_t	TQueue<T>::Available
		(
		void
		) const
{
	return this->m_nAlloc - this->m_nUsed;
}


/*---------------------------------------------------------------------+\

 * IsEmpty - Is Queue Empty

\+---------------------------------------------------------------------*/
template < class T >
inline
bool	TQueue<T>::IsEmpty
		(
		void
		) const
{
	return this->m_nUsed < 1;
}


/*---------------------------------------------------------------------+\

 * RemoveEntry - Remove next available entry

\+---------------------------------------------------------------------*/
template < class T >
bool	TQueue<T>::RemoveEntry
		(
		void
		)
{
	bool	bResult = false;

	if ( 1 < this->m_nUsed )
	{
		CMutexLocker	lock( &this->m_oMutex );
		T	tTemp = 0;

		bResult = true;
		this->m_nUsed--;
		this->m_pArray[this->m_nFront] = tTemp;
		if ( 0 < this->m_nUsed )
		{
			this->m_nFront = (this->m_nFront + 1) % this->m_nAlloc;
		}
		else
		{
			this->m_nFront = 0;
			this->m_nRear = 0;
		}
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Clear - Empty queue

\+---------------------------------------------------------------------*/
template < class T >
void	TQueue<T>::Clear
		(
		void
		)
{
	while ( ! IsEmpty() )
		RemoveEntry();
}




/*---------------------------------------------------------------------+\

 * SetBlockSize - Set growth factor

\+---------------------------------------------------------------------*/
template< class T >
void	TQueue<T>::SetBlockSize
		(
		size_t	nSize
		)
{
	this->m_nBlockSize = 1 < nSize ? nSize : 1;
}


template < class T >
bool	TQueue<T>::SetInitialSize
		(
		size_t	nSize
		)
{
	CMutexLocker	locker( &this->m_oMutex );

	return this->GrowQueue( nSize );
}



/*---------------------------------------------------------------------+\

 * GrowQueue - Assure queue will handle another entry

\+---------------------------------------------------------------------*/
template< class T >
bool	TQueue<T>::GrowQueue
		(
		size_t	n	// = 1
		)
{
	bool	bResult = false;

	if ( this->m_pArray )
	{
		if ( this->m_nAlloc <= this->m_nUsed + n )
		{
			// to do this we have to allocate a new queue
			//	and then copy the old entries such that 'm_nFront'
			//	is at index zero

			//DbgPrint( "GrowQueue: n = %ld\n", n );

			size_t	nNewAlloc = (this->m_nAlloc + this->m_nBlockSize + n) / this->m_nBlockSize * this->m_nBlockSize;
			T*		pNewArray = new T[nNewAlloc];

			if ( pNewArray )
			{

				T*	p1;
				T*	p1End;
				T*	p2 = pNewArray;

				if ( this->m_nFront < this->m_nRear )
				{
					p1 = this->m_pArray + this->m_nFront;
					p1End = this->m_pArray + this->m_nRear;

					while ( p1 < p1End )
						*p2++ = *p1++;
				}
				else
				{
					p1 = this->m_pArray + this->m_nFront;
					p1End = this->m_pArray + this->m_nAlloc;

					while ( p1 < p1End )
						*p2++ = *p1++;

					p1 = this->m_pArray;
					p1End = this->m_pArray + m_nRear;

					while ( p1 < p1End )
						*p2++ = *p1++;
				}

				this->m_nFront = 0;
				this->m_nRear = this->m_nUsed;

				delete [] this->m_pArray;
				this->m_pArray = pNewArray;
				this->m_nAlloc = nNewAlloc;

				bResult = true;
			}

		}
		else
		{
			// a new entry should fit
			bResult = true;
		}
	}
	else
	{
		if ( this->m_nBlockSize < 1 )
			this->m_nBlockSize = 4;
		if ( n < 1 )
			n = 1;

		size_t	nNewAlloc = (this->m_nBlockSize + n) / this->m_nBlockSize * this->m_nBlockSize;

		this->m_pArray = new T[nNewAlloc];
		if ( this->m_pArray )
		{
			bResult = true;

			this->m_nAlloc = nNewAlloc;
			this->m_nUsed = 0;
			this->m_nFront = 0;
			this->m_nRear = 0;
		}
	}

	return bResult;
}






NAMESPACE_COMMON_END



#endif /* _H_TQueue */

