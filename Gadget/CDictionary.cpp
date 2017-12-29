/*---------------------------------------------------------------------+\
|
|	CDictionary.cpp  --  brief description of what CDictionary.cpp is for
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
	26-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for the psuedo-interface VVariable
	23-Jan-2010			M.Rose			(Reviewed by: N.Graham)
		Fix compile warning
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	14-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fixed a warning regarding possible loss of data using time_t
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	06-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add functionality deal with an immediate millisecond calculation
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Protect from null pointer in LocateEntry function
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		changed to use gmtime_s to resolve compiler warning in MSVC
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetMilliseconds
	28-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <ctype.h>

#include "CDictionary.h"

#include "CDictPageVariant.h"
#include "CDictPageLazyLoad.h"

#include "UPlatform.h"
#include "UPlatformTime.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

NAMESPACE_GADGET_BEGIN
//USING_NAMESPACE_COMMON


const unsigned long	K_BITS_CHAR = 8;
const unsigned long	K_BITS_LONG = sizeof(long) * K_BITS_CHAR;
const unsigned long K_OFS_PAGEID = K_BITS_LONG - K_BITS_CHAR;
const unsigned long K_MSK_VARID = (unsigned long) ~0 >> K_BITS_CHAR;

//#define	K_OFS_PAGEID	(sizeof(long)-sizeof(char))			// number of bits to offset to page-id
//#define	K_MSK_VARID		((unsigned long)~0 >> sizeof(char))	// mask to get variable's id

//#define MAKE_SELECTOR( nPage, nVar )	(((nPage) << K_OFS_PAGEID) | (nVar))
//#define	GET_PAGEID( nSel )	(nSel >> K_OFS_PAGEID)
//#define	GET_VARID( nSel )	(nSel & K_MSK_VARID)

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
inline
VDictionary::Selector
		MAKE_SELECTOR
		(
		unsigned long	nPage,
		unsigned long	nVar
		)
{
	return (nPage << K_OFS_PAGEID)  |  nVar;
}

inline
unsigned long
		GET_PAGEID
		(
		VDictionary::Selector	nSel
		)
{
	return (nSel >> K_OFS_PAGEID);
}

inline
unsigned long
		GET_VARID
		(
		VDictionary::Selector	nSel
		)
{
	return (nSel & K_MSK_VARID);
}


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictionary - constructor

\+---------------------------------------------------------------------*/
CDictionary::CDictionary
		(
		void
		)
		: VDictionaryPageServer(),
		m_bDirty( false ),
		m_cPushPage( 'G' ),
		m_nPushCount( 0 )
{
	VDictionaryPagePtr*	p = m_aPages;
	VDictionaryPagePtr*	pEnd = m_aPages + kPageCount;
	while ( p < pEnd )
		*p++ = 0;

	m_nMilli = milliseconds();

}


/*---------------------------------------------------------------------+\

 * ~CDictionary - destructor

\+---------------------------------------------------------------------*/
CDictionary::~CDictionary
		(
		void
		)
{
	VDictionaryPagePtr*	p = m_aPages;
	VDictionaryPagePtr*	pEnd = m_aPages + kPageCount;
	while ( p < pEnd )
	{
		if ( *p )
		{
			(*p)->Release();
			*p = 0;
		}
		p++;
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetPushPage -

\+---------------------------------------------------------------------*/
void	CDictionary::SetPushPage
		(
		char	c
		)
{
	char	uc = static_cast<char>(::toupper( c ));
	if ( 'A' <= uc  &&  uc <= 'Z' )
		m_cPushPage = uc;
}


/*---------------------------------------------------------------------+\

 * SetDictionaryPage -

\+---------------------------------------------------------------------*/
void	CDictionary::SetDictionaryPage
		(
		char				c,
		VDictionaryPagePtr	pPage
		)
{
	char	uc = static_cast<char>(::toupper( c ));
	if ( 'A' <= uc  &&  uc <= 'Z' )
	{
		int					i = uc - 'A';
		VDictionaryPagePtr	p;

		p = m_aPages[i];
		if ( p )
			p->SetDictionary( 0 );

		if ( pPage )
		{
			pPage->AddRef();
			pPage->SetDictionary( this );
			pPage->SetPageID( uc );
		}

		if ( p )
			p->Release();

		m_aPages[i] = pPage;
	}
}

/*---------------------------------------------------------------------+\

 * BeginCalculate -

\+---------------------------------------------------------------------*/
void	CDictionary::BeginCalculate
		(
		void
		)
{
	SetDirty( false );

	LazyMilliseconds();

	VDictionaryPagePtr*	p = m_aPages;
	VDictionaryPagePtr*	pEnd = m_aPages + kPageCount;
	while ( p < pEnd )
	{
		if ( *p )
		{
			(*p)->BeginCalculate();
		}
		p++;
	}
}


/*---------------------------------------------------------------------+\

 * EndCalculate -

\+---------------------------------------------------------------------*/
void	CDictionary::EndCalculate
		(
		void
		)
{
	VDictionaryPagePtr*	p = m_aPages;
	VDictionaryPagePtr*	pEnd = m_aPages + kPageCount;
	while ( p < pEnd )
	{
		if ( *p )
		{
			(*p)->EndCalculate();
		}
		p++;
	}
	m_nMilli = 0;
}


/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CDictionary::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	const char*	sName = rName.Pointer();
	return LocateEntry( sName );
}



/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CDictionary::LocateEntry
		(
		const char*	sName
		)
{
	CDictionary::Selector	nSel = 0;

	if ( sName )
	{
		if ( ':' == sName[1] )
		{
			char	c = sName[0];
			if ( 'A' <= c  &&  c <= 'Z' )
			{
				unsigned int	i = static_cast<unsigned int>(c - 'A');
				VDictionaryPagePtr p = m_aPages[i];
				if ( p )
				{
					long n = p->LocateEntry( sName+2 );
					if ( -1 < n )
						nSel = MAKE_SELECTOR( i+1, (unsigned long)n );
				}
			}
		}
	}
	return nSel;
}


/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CDictionary::GetData
		(
		Selector nSel
		)
{
	CVariantDataPtr	pData = 0;
	unsigned long	nPage = GET_PAGEID( nSel );
	if ( nPage )
	{
		unsigned long		n = GET_VARID( nSel );
		VDictionaryPagePtr	p = *(m_aPages + nPage - 1);
		if ( p )
			pData = p->GetData( n );
	}

	return pData;
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictionary::PutData
		(
		Selector nSel,
		CVariantDataPtr pData
		)
{
	bool			bResult = false;
	unsigned long	nPage = GET_PAGEID( nSel );
	if ( nPage )
	{
		unsigned long		n = GET_VARID( nSel );
		VDictionaryPagePtr	p = *(m_aPages + nPage - 1);
		if ( p )
			bResult = p->PutData( n, pData );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * IsDataLocked -

\+---------------------------------------------------------------------*/
bool	CDictionary::IsDataLocked
		(
		VDictionary::Selector nSel
		)
{
	bool			bResult = false;
	unsigned long	nPage = GET_PAGEID( nSel );
	if ( nPage )
	{
		unsigned long		n = GET_VARID( nSel );
		VDictionaryPagePtr	p = *(m_aPages + nPage - 1);
		if ( p )
			bResult = p->IsDataLocked( n );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * PushDictionaryPage -

\+---------------------------------------------------------------------*/
bool	CDictionary::PushDictionaryPage
		(
		VDictionaryPage* pDict
		)
{
	SetDictionaryPage( m_cPushPage, pDict );
	return true;
}

/*---------------------------------------------------------------------+\

 * PopDictionaryPage -

\+---------------------------------------------------------------------*/
bool	CDictionary::PopDictionaryPage
		(
		void
		)
{
	SetDictionaryPage( m_cPushPage, 0 );
	return true;
}


/*---------------------------------------------------------------------+\

 * GetMilliseconds -

\+---------------------------------------------------------------------*/
long	CDictionary::GetMilliseconds
		(
		void
		)
{
	if ( 0 == m_nMilli )
		LazyMilliseconds();

	return m_nMilli;
}


/*---------------------------------------------------------------------+\

 * ClearMilliseconds -

\+---------------------------------------------------------------------*/
void	CDictionary::ClearMilliseconds
		(
		void
		)
{
	m_nMilli = 0;
}




/*---------------------------------------------------------------------+\

 * IsDirty -

\+---------------------------------------------------------------------*/
bool	CDictionary::IsDirty
		(
		void
		)
{
	return m_bDirty;
}



/*---------------------------------------------------------------------+\

 * SetDirty -

\+---------------------------------------------------------------------*/
void	CDictionary::SetDirty
		(
		bool	bDirty
		)
{
	m_bDirty = bDirty;
}


/*---------------------------------------------------------------------+\

 * GetType -

\+---------------------------------------------------------------------*/
int		CDictionary::GetType
		(
		void
		)
{
	return 'A';
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictionary::GetEnumerator
		(
		void
		)
{
	CDictionaryEnumerator*	p = new CDictionaryEnumerator( this );
	return p;
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictionary::GetPageEnumerator
		(
		char	cPageID
		)
{
	VDictionaryEnumerator*	pEnum = 0;

	if ( 'A' <= cPageID  &&  cPageID <= 'Z' )
	{
		int	n = cPageID - 'A';

		if ( m_aPages[n] )
		{
			pEnum = m_aPages[n]->GetEnumerator();
		}
	}

	return pEnum;
}


VVariablePtr
		CDictionary::GetVariableIF
		(
		void
		)
{
	return (VVariablePtr)this;
}

/*---------------------------------------------------------------------+\

 * SetDirty -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CDictionary::MakeSelector
		(
		char	cPageID,
		long	id
		)
{
	VDictionary::Selector	nSel = 0;

	char	c = static_cast<char>(::toupper( cPageID ));
	if ( 'A' <= c  &&  c <= 'Z' )
	{
		unsigned	i = static_cast<unsigned>(c - 'A');
		VDictionaryPagePtr p = m_aPages[i];
		if ( p )
		{
			if ( -1 < id )
				nSel = MAKE_SELECTOR( i+1, (unsigned long)id );
		}
	}
	return nSel;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * LazyMilliseconds -

\+---------------------------------------------------------------------*/
void	CDictionary::LazyMilliseconds
		(
		void
		)
{
	m_nMilli = milliseconds();
}


CCharString
		CDictionary::ResolveVariable
		(
		ConstCCharDescriptorRef r
		)
{
	CCharString	sResult;
	CCharString	s = r;
	VDictionary::Selector	sel;

	sel = LocateEntry( s );
	if ( sel )
	{
		CVariantDataPtr	pv;
		pv = GetData( sel );
		if ( pv )
		{
			sResult = pv->GetValueCCharString();
		}
	}

	return sResult;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/



CDictionaryEnumerator::CDictionaryEnumerator
		(
		CDictionary*	p
		)
		: m_pDictionary( p ),
		m_pEnumPage( 0 ),
		m_nIndex( -1 )
{
}

CDictionaryEnumerator::~CDictionaryEnumerator
		(
		void
		)
{
	if ( m_pEnumPage )
		delete m_pEnumPage;
}

bool	CDictionaryEnumerator::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( m_nIndex < 0 )
	{
		m_nIndex = -1;	// this will get changed into zero in the next step

		forever_loop
		{
			++m_nIndex;
			if ( ('Z' - 'A') < m_nIndex )
				break;

			if ( m_pDictionary->m_aPages[ m_nIndex ] )
			{
				VDictionaryEnumerator*	p;
				p = m_pDictionary->m_aPages[ m_nIndex ]->GetEnumerator();
				if ( p )
				{
					if ( m_pEnumPage )
						delete m_pEnumPage;
					m_pEnumPage = p;
					bResult = m_pEnumPage->MoveNext();
					if ( bResult )
						break;
				}
			}
		}
	}
	else
	{
		bResult = m_pEnumPage->MoveNext();
		if ( ! bResult )
		{
			long	nTopIndex = CDictionary::kPageCount - 1;
			forever_loop
			{
				++m_nIndex;
				if ( nTopIndex < m_nIndex )
					break;

				if ( m_pDictionary->m_aPages[ m_nIndex ] )
				{
					VDictionaryEnumerator*	p;
					p = m_pDictionary->m_aPages[ m_nIndex ]->GetEnumerator();
					if ( p )
					{
						if ( m_pEnumPage )
							delete m_pEnumPage;
						m_pEnumPage = p;
						bResult = m_pEnumPage->MoveNext();
						if ( bResult )
							break;
					}
				}
			}
		}
	}

	return bResult;
}


void	CDictionaryEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
	if ( m_pEnumPage )
		delete m_pEnumPage;
	m_pEnumPage = 0;
}


CVariantData*
		CDictionaryEnumerator::Current
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_pEnumPage->Current();
}

CVariantData
		CDictionaryEnumerator::Value
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_pEnumPage->Value();
}

long	CDictionaryEnumerator::ID
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_pEnumPage->ID();
}

CCharString
		CDictionaryEnumerator::Key
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_pEnumPage->Key();
}

char	CDictionaryEnumerator::Page
		(
		void
		)
{
	if ( m_nIndex < 0 )
		MoveNext();

	return m_pEnumPage->Page();
}






NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

