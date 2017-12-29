/*---------------------------------------------------------------------+\
|
|	TList.h  --  List template
|
|	Purpose:
|	File Custodian:		P.Hogan
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
|	Revision History:				(most recent entries first)
|
	21-Jul_2010			P.Hogan		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_TList
#define _H_TList
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TArray.h"

#include "NamespaceCommon.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMON_BEGIN
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
//------------------
//  Template Class
//------------------


template< class T >
class TList
{
//	class lifecycle  ----------------------------------------------------
public:
					TList();
					TList( int maxLength );
	virtual			~TList();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------
	void Initialize( int maxListLength );
	int Add( T* pListItem );
	void Remove( int listItemID );
	T* Get( int listItemID );
	int GetUsedCount( void );
	T* GetFirstUsedEntry( int *pListItemID );
	T* GetNextUsedEntry( int *pListItemID );

protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------

private:
//	private functions  --------------------------------------------------
	int Encode( int i, int seqNum );
	void Decode ( int id, int *pIdx, int *pSeqNum );
	int GenerateSeqNum( void );
	int FindUnusedEntry( void );


//	private data  -------------------------------------------------------
	TArray< T > m_list;
	TArray< int > m_listSeqNum;
	int m_maxLength;
	int m_seqNum;
	int m_seqNumMask;
	int m_seqNumShift;
	int m_maxSeqNum;
	int m_idxMask;
	int m_nUsed;
	int m_lastUsedItem;
	int m_idxUsedEntry;

//============================== Overrides ==============================
	// -- delete this section if this is a root class --
	//	root
	//	BaseClass-1
	//	BaseClass

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



/**--------------------------------------------------------------------+\

 * <summary>TArray - Constructor</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
TList<T>::TList
		(
		void
		)
{
	// Default list length is 64
	Initialize(64);
}



/**--------------------------------------------------------------------+\

 * <summary>TArray - Constructor</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
TList<T>::TList
		(
		int maxLength
		)
{
	Initialize( maxLength );
}



/**--------------------------------------------------------------------+\

 * <summary>TArray - Constructor</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
TList<T>::~TList()
{
}



/**--------------------------------------------------------------------+\

 * <summary>Initialize - Initialize list</summary>

 * <remarks>
	Due to the list ID encoding contraints, the maximum length of the
	list is 32768 items (0 to 32767).
   <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
void TList<T>::Initialize
		(
		int maxLength
		)
{
	m_nUsed = 0;
	m_seqNum = 0;
	m_idxUsedEntry = -1;

	if (maxLength <= 32768)
	{
		m_maxLength = maxLength;
	}
	else
	{
		m_maxLength = 32768;
	}
	m_lastUsedItem = m_maxLength;

	// NOTE: the m_maxSeqNum value below is 1-bit less than the full length
	//       of the encoded sequence number field to prevent the encoded list
	//       ID values from being negative. This allows for quick validity
	//       checks.
	//
	if ( m_maxLength < 16 )
	{
		m_seqNumMask  = 0xFFFFFFF0;
		m_maxSeqNum   = 0x07FFFFFF;
		m_seqNumShift = 4;
		m_idxMask     = 0x0000000F;
	}
	else if ( m_maxLength < 32 )
	{
		m_seqNumMask  = 0xFFFFFFE0;
		m_maxSeqNum   = 0x03FFFFFF;
		m_seqNumShift = 5;
		m_idxMask     = 0x0000001F;
	}
	else if ( m_maxLength < 64 )
	{
		m_seqNumMask  = 0xFFFFFFC0;
		m_maxSeqNum   = 0x01FFFFFF;
		m_seqNumShift = 6;
		m_idxMask     = 0x0000003F;
	}
	else if ( m_maxLength < 128 )
	{
		m_seqNumMask  = 0xFFFFFF80;
		m_maxSeqNum   = 0x00FFFFFF;
		m_seqNumShift = 7;
		m_idxMask     = 0x0000007F;
	}
	else if ( m_maxLength < 256 )
	{
		m_seqNumMask  = 0xFFFFFF00;
		m_maxSeqNum   = 0x007FFFFF;
		m_seqNumShift = 8;
		m_idxMask     = 0x000000FF;
	}
	else if ( m_maxLength < 512 )
	{
		m_seqNumMask  = 0xFFFFFE00;
		m_maxSeqNum   = 0x003FFFFF;
		m_seqNumShift = 9;
		m_idxMask     = 0x000001FF;
	}
	else if ( m_maxLength < 1024 )
	{
		m_seqNumMask  = 0xFFFFFC00;
		m_maxSeqNum   = 0x001FFFFF;
		m_seqNumShift = 10;
		m_idxMask     = 0x000003FF;
	}
	else if ( m_maxLength < 2048 )
	{
		m_seqNumMask  = 0xFFFFF800;
		m_maxSeqNum   = 0x000FFFFF;
		m_seqNumShift = 11;
		m_idxMask     = 0x000007FF;
	}
	else if ( m_maxLength < 4096 )
	{
		m_seqNumMask  = 0xFFFFF000;
		m_maxSeqNum   = 0x0007FFFF;
		m_seqNumShift = 12;
		m_idxMask     = 0x00000FFF;
	}
	else if ( m_maxLength < 8192 )
	{
		m_seqNumMask  = 0xFFFFE000;
		m_maxSeqNum   = 0x0003FFFF;
		m_seqNumShift = 13;
		m_idxMask     = 0x00001FFF;
	}
	else if ( m_maxLength < 16384 )
	{
		m_seqNumMask  = 0xFFFFC000;
		m_maxSeqNum   = 0x0001FFFF;
		m_seqNumShift = 14;
		m_idxMask     = 0x00003FFF;
	}
	else
	{
		m_seqNumMask  = 0xFFFF8000;
		m_maxSeqNum   = 0x0000FFFF;
		m_seqNumShift = 15;
		m_idxMask     = 0x00007FFF;
	}

	// Allocate m_list items and initialize m_seqNum values.
	m_list.AdjustUsed(m_maxLength);
	m_listSeqNum.AdjustUsed(m_maxLength);
	for (int i = 0; i < m_maxLength; i++)
	{
		m_listSeqNum[i] = -1;
	}
}



/**--------------------------------------------------------------------+\

 * <summary>Add - Add an item to the list</summary>

 * <remarks
	This method returns the list item ID for the new item or -1 on failure
	(full list).
   <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
int TList<T>::Add( T* pListItem )
{
	int i = FindUnusedEntry();
	int listItemID = -1;

	if (i >= 0)
	{
		int seqNum = GenerateSeqNum();
		listItemID = Encode( i, seqNum );
		m_list[i] = *pListItem;
		m_listSeqNum[i] = seqNum;
		m_lastUsedItem = i;
		m_nUsed += 1;
	}

	return listItemID;
}



/**--------------------------------------------------------------------+\

 * <summary>Remove - Remove an item to the list</summary>

 * <remarks
	Argument listItemID is the value returned from Add().
   <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
void TList<T>::Remove( int listItemID )
{
	int i;
	int seqNum;

	Decode( listItemID, &i, &seqNum );
	if ( (i >= 0) && (i < m_maxLength) && (listItemID != -1) )
	{
		if ( m_listSeqNum[i] == seqNum )
		{
			m_listSeqNum[i] = -1;
			m_nUsed -= 1;
		}
	}
}



/**--------------------------------------------------------------------+\

 * <summary>Get - Get a list entry</summary>

 * <remarks
	Get will return a NULL (0) pointer if the list item ID is not valid or
	the item has been removed from the list.
   <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
T* TList<T>::Get( int listItemID )
{
	int i;
	int seqNum;
	T* pItem = 0;

	Decode( listItemID, &i, &seqNum );
	if ( (i >= 0) && (i < m_maxLength) && (listItemID != -1) )
	{
		if ( m_listSeqNum[i] == seqNum )
		{
			pItem = m_list.PointItem(i);
		}
	}

	return pItem;
}



/**--------------------------------------------------------------------+\

 * <summary>GetUsedCount - Get the number of valid items contained in the list</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
int TList<T>::GetUsedCount( void )
{
	return m_nUsed;
}



/**--------------------------------------------------------------------+\

 * <summary>GetFirstUsedEntry - Used entry list iterator. Moves the iterator
 to the first used entry in the list. If found, the function will return a pointer
 to the list entry and the list ID of the entry. If not found, the returned
 pointer will be NULL and the list ID will be set to -1.</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
T* TList<T>::GetFirstUsedEntry( int *pListItemID )
{
	T* pEntry = 0;
	*pListItemID = -1;

	if (m_nUsed > 0)
	{
		for (int i = 0; i < m_maxLength; i++)
		{
			if ( m_listSeqNum[i] != -1 )
			{
				m_idxUsedEntry = i;
				pEntry = m_list.PointItem(i);
				*pListItemID = Encode(i, m_listSeqNum[i]);
				break;
			}
		}
	}

	return pEntry;
}



/**--------------------------------------------------------------------+\

 * <summary>GetNextUsedEntry - Used entry list iterator. Moves the iterator
 to the next used entry in the list. If found, the function will return a pointer
 to the list entry and the list ID of the entry. If not found, the returned
 pointer will be NULL and the list ID will be set to -1.</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
T* TList<T>::GetNextUsedEntry( int *pListItemID )
{
	T* pEntry = 0;
	*pListItemID = -1;

	if (m_nUsed > 0)
	{
		int start = m_idxUsedEntry + 1;
		for (int i = start; i < m_maxLength; i++)
		{
			if ( m_listSeqNum[i] != -1 )
			{
				m_idxUsedEntry = i;
				pEntry = m_list.PointItem(i);
				*pListItemID = Encode(i, m_listSeqNum[i]);
				break;
			}
		}
	}

	return pEntry;
}



/**--------------------------------------------------------------------+\

 * <summary>Encode - Encode a list index and sequence number into a list item ID</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
int TList<T>::Encode( int i, int seqNum )
{
	int listItemID = (seqNum << m_seqNumShift) | (i & m_idxMask);

	return listItemID;
}



/**--------------------------------------------------------------------+\

 * <summary>Decode - Decode a list item ID into an index and sequenc number</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
void TList<T>::Decode ( int id, int *pIdx, int *pSeqNum )
{
	*pIdx = id & m_idxMask;
	*pSeqNum = id >> m_seqNumShift;
}



/**--------------------------------------------------------------------+\

 * <summary>GenerateSeqNum - Generate a list item sequence number</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
int TList<T>::GenerateSeqNum( void )
{
	m_seqNum += 1;
	if (m_seqNum > m_maxSeqNum)
	{
		m_seqNum = 0;
	}

	return m_seqNum;
}



/**--------------------------------------------------------------------+\

 * <summary>FindUnusedEntry - Returns the index of an unused list entry or
                              -1 (list is full)</summary>

 * <remarks/>

 * (author)P.Hogan  --  21-Jul_2010

\+---------------------------------------------------------------------*/
template< class T >
int TList<T>::FindUnusedEntry( void )
{
	int j = m_lastUsedItem; // m_lastUsedItem set by Add()
	int idxUnusedEntry = -1;


	for (int i = 0; i < m_maxLength; i++)
	{
		// Increment to the next list item
		j += 1;

		// Check for the end of the list
		if (j >= m_maxLength)
		{
			j = 0;
		}

		if (m_listSeqNum[j] == -1)
		{
			// Available entry
			idxUnusedEntry = j;
			break;
		}
	}

	return idxUnusedEntry;
}

NAMESPACE_COMMON_END



#endif /* _H_TList */

