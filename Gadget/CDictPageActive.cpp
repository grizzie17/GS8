/*---------------------------------------------------------------------+\
|
|	CDictPageActive.cpp  --  implementation of "Active" Engineering page
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
	03-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Change the arguments to AddAlias to be 'const'
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	24-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the DatumEnum has the units set to 'enum'
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Make the ResetAllEntries function also set the time last
		updated member.
	14-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Don't let "date" entries set the dictionary to dirty.  We
		will pickup the date entries through our other timer related
		events.
	02-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Deal with the min/max values correctly when setting range and
		when doing a reset.
	31-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for logging time of last update
		Add support for reseting values back to defaults.
	20-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add checks for valid ranges to the UpdateData methods
	22-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support the date/time type
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	07-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for char-descriptors for add and update entry
	02-Sep-2009			R.Hosea			(Reviewed by: M.Rose)
		Mods for gcc compatibility
	10-Jul-2009			J.Griswold
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
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "CDictPageActive.h"

#include "UPlatform.h"
#include "CDateTime.h"
#include "UFloat.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

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
/*=====================================================================+\
||	 Enumerator															|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator -

\+---------------------------------------------------------------------*/
CDictPageActiveEnumerator::CDictPageActiveEnumerator
		(
		CDictPageActive*	p
		)
		: m_pPage( p )
		, m_nIndex( -1 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageActiveEnumerator -

\+---------------------------------------------------------------------*/
CDictPageActiveEnumerator::~CDictPageActiveEnumerator
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::MoveNext -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveEnumerator::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( m_nIndex < 0 )
	{
		m_nIndex = 0;
		m_eList = m_pPage->m_aContent.GetEnumerator();
		bResult = m_eList.MoveNext();
	}
	else
	{
		++m_nIndex;
		bResult = m_eList.MoveNext();
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::Reset -

\+---------------------------------------------------------------------*/
void	CDictPageActiveEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
}

/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::Current -

\+---------------------------------------------------------------------*/
const CVariantData*
		CDictPageActiveEnumerator::Current
		(
		void
		)
{
	VDictPageActiveDatum* const* h = m_eList.Current();
	if ( h )
	{
		VDictPageActiveDatumPtr	p = *h;
		return p->GetData( m_pPage );
	}
	else
	{
		return 0;
	}
}

/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::ID -

\+---------------------------------------------------------------------*/
long	CDictPageActiveEnumerator::ID
		(
		void
		)
{
	long	n = m_eList.ID();
	long	c = Page();
	long	i = c - 'A';

	long	id = ((i + 1) << 24)  |  n;

	return id;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::Key -

\+---------------------------------------------------------------------*/
CCharString
		CDictPageActiveEnumerator::Key
		(
		void
		)
{
	return m_eList.Key();
}

/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::Value -

\+---------------------------------------------------------------------*/
CVariantData
		CDictPageActiveEnumerator::Value
		(
		void
		)
{
	const CVariantData*	p = Current();
	return *p;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveEnumerator::Page -

\+---------------------------------------------------------------------*/
char	CDictPageActiveEnumerator::Page
		(
		void
		)
{
	return m_pPage->m_cPageID;
}






/*=====================================================================+\
||	 Active Engineering Dictionary Page									|
\+=====================================================================*/

VDictPageActiveDatum::VDictPageActiveDatum
		(
		)
		: m_tData()
		, m_nSelector( 0 )
		, m_bReferenced(false)
		, m_sReset()
		, m_sUnavailable()
{
}



VDictPageActiveDatum::~VDictPageActiveDatum
		(
		void
		)
{
}



/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::GetData -

\+---------------------------------------------------------------------*/
ConstCVariantDataPtr
		VDictPageActiveDatum::GetData
		(
		CDictPageActivePtr //pPage
		)
{
	return &m_tData;
}


/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::Reset -

\+---------------------------------------------------------------------*/
void	VDictPageActiveDatum::ResetData
		(
		CDictPageActivePtr	pPage
		)
{
	this->UpdateData( pPage, m_sReset.Pointer() );
}



/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::SetReset -

\+---------------------------------------------------------------------*/
void	VDictPageActiveDatum::SetReset
		(
		ConstCCharDescriptorRef	r
		)
{
	m_sReset = r;
}


/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::SetUnavailable -

\+---------------------------------------------------------------------*/
void	VDictPageActiveDatum::SetUnavailable
		(
		ConstCCharDescriptorRef	r
		)
{
	m_sUnavailable = r;
}




/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::SetUnits -

\+---------------------------------------------------------------------*/
bool	VDictPageActiveDatum::SetUnits
		(
		int nUnits
		)
{
	m_tData.SetUnits( nUnits );
	return true;
}



/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::SetReferenced -

\+---------------------------------------------------------------------*/
void	VDictPageActiveDatum::SetReferenced
		(
		void
		)
{
	m_bReferenced = true;
}


/*---------------------------------------------------------------------+\

 * VDictPageActiveDatum::UpdateData -

\+---------------------------------------------------------------------*/
bool	VDictPageActiveDatum::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	CCharString	sData = rData.GetValueCCharString();
	return UpdateData( pPage, sData.Pointer() );
}




/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumBool::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumBool::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	bool	bValue = false;
	switch ( ::toupper(*sData) )
	{
	case 'T':
	case 'Y':
	case '1':
		bValue = true;
	}
	if ( m_tData != bValue )
	{
		m_tData = bValue;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}

bool	CDictPageActiveDatumBool::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	bool	b = rData.GetValueBool();
	if ( m_tData != b )
	{
		m_tData = b;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumBool::ResetData -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumBool::ResetData
		(
		CDictPageActivePtr	pPage
		)
{
	UpdateData( pPage, "N" );
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumInteger::SetRange -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumInteger::SetRange
		(
		long	nLow,
		long	nHigh
		)
{
	m_nLow = nLow;
	m_nHigh = nHigh;
	m_nDelta = m_nHigh - m_nLow;
	if ( 0 < m_nDelta )
		m_nCheckType = 1;	// assume clip checking
	else
		m_nCheckType = 0;

	long	n = m_tData;
	if ( n < m_nLow )
		m_tData = m_nLow;
	else if ( m_nHigh < n )
		m_tData = m_nHigh;
}


long	CDictPageActiveDatumInteger::AdjustInRange
		(
		long	n
		)
{
	if ( 0 != m_nCheckType )
	{
		if ( 1 == m_nCheckType )	// clip
		{
			if ( n < m_nLow )
				n = m_nLow;
			else if ( m_nHigh < n )
				n = m_nHigh;
		}
		else	// circular
		{
			if ( n < m_nLow )
			{
				n = n % m_nDelta;
				while ( n < m_nLow )
					n += m_nDelta;
			}
			else if ( m_nHigh < n )
			{
				n = n % m_nDelta;
				while ( m_nHigh < n )
					n -= m_nDelta;
			}
		}
	}
	return n;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumInteger::SetCheckType -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumInteger::SetCheckType
		(
		int	nType
		)
{
	m_nCheckType = nType;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumInteger::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumInteger::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	long	n;
	//if ( m_sUnavailable == sData )
	//{
	//	n = ::atol( m_sReset );
	//}
	if ( m_sUnavailable != sData )
	{
		n = ::atol( sData );
		n = AdjustInRange( n );
	if ( m_tData != n )
	{
		m_tData = n;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	}
	return true;
}


bool	CDictPageActiveDatumInteger::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	long	n;
	//if ( rData == m_sUnavailable )
	//{
	//	n = ::atol( m_sReset );
	//}
	if ( rData != m_sUnavailable )
	{
		n = rData.GetValueInteger();
		n = AdjustInRange( n );
		if ( m_tData != n )
		{
			m_tData = n;
			if ( pPage  &&  m_bReferenced )
				pPage->SetDirty();
		}
	}
	return true;
}




/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumInteger::ResetData -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumInteger::ResetData
		(
		CDictPageActivePtr	pPage
		)
{
	UpdateData( pPage, m_sReset.Pointer() );
}



/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumFloat::SetRange -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumFloat::SetRange
		(
		GFLOAT	fLow,
		GFLOAT	fHigh
		)
{
	m_fLow = fLow;
	m_fHigh = fHigh;
	m_fDelta = m_fHigh - m_fLow;
	if ( GFLOAT_EPSILON < m_fDelta )
		m_nCheckType = 1;	// assume clip checking
	else
		m_nCheckType = 0;

	GFLOAT	f = m_tData;
	if ( f < m_fLow )
		m_tData = m_fLow;
	else if ( m_fHigh < f )
		m_tData = m_fHigh;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumFloat::SetCheckType -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumFloat::SetCheckType
		(
		int	nType
		)
{
	m_nCheckType = nType;
}


GFLOAT	CDictPageActiveDatumFloat::adjustInRange
		(
		GFLOAT	f
		)
{
	if ( 0 != m_nCheckType )
	{
		if ( 1 == m_nCheckType )	// clip
		{
			if ( f < m_fLow )
				f = m_fLow;
			else if ( m_fHigh < f )
				f = m_fHigh;
		}
		else	// circular
		{
			if ( f < m_fLow )
			{
				f = fmodf( f, m_fDelta );
				while ( f < m_fLow )
					f += m_fDelta;
			}
			else if ( m_fHigh < f )
			{
				f = fmodf( f, m_fDelta );
				while ( m_fHigh < f )
					f -= m_fDelta;
			}
		}
	}
	return f;
}



/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumFloat::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumFloat::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	GFLOAT	f;
	//if ( m_sUnavailable == sData )
	//{
	//	f = GFLOAT(atof( m_sReset ));
	//}
	if ( m_sUnavailable != sData )
	{
		f = GFLOAT(::atof( sData ));
		f = adjustInRange( f );
	if ( m_tData != f )
	{
		m_tData = f;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	}
	return true;
}

bool	CDictPageActiveDatumFloat::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	GFLOAT	n = GFLOAT_0;
	//if ( rData == m_sUnavailable )
	//{
	//	n = GFLOAT(atof(m_sReset));
	//}
	if ( rData != m_sUnavailable )
	{
		n = rData;
		n = adjustInRange( n );
	}
	if ( m_tData != n )
	{
		m_tData = n;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumFloat::ResetData -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumFloat::ResetData
		(
		CDictPageActivePtr	pPage
		)
{
	UpdateData( pPage, m_sReset.Pointer() );
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumDate::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumDate::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	CDateTime	t;
	if ( m_sUnavailable == sData )
	{
		if ( t.Parse( m_sReset ) )
		{
			if ( m_tData != t )
			{
				m_tData = t;
				//if ( pPage  &&  m_bReferenced )
				//	pPage->SetDirty();
				m_nDelta = t.ToTime_t() - (pPage->Dictionary()->GetMilliseconds() / 1000);
				m_bStale = true;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ( t.Parse( sData ) )
		{
			if ( m_tData != t )
			{
				m_tData = t;
				//if ( pPage  &&  m_bReferenced )
				//	pPage->SetDirty();
				m_nDelta = t.ToTime_t() - (pPage->Dictionary()->GetMilliseconds() / 1000);
				m_bStale = false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool	CDictPageActiveDatumDate::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	CDateTime	t = rData;
	if ( m_tData != t )
	{
		m_tData = t;
		m_nDelta = t.ToTime_t() - (pPage->Dictionary()->GetMilliseconds() / 1000);
		m_bStale = false;
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumDate::GetData -

\+---------------------------------------------------------------------*/
ConstConstCVariantDataPtr
		CDictPageActiveDatumDate::GetData
		(
		CDictPageActivePtr pPage
		)
{
	if ( m_nDelta  &&  m_bStale )
	{
		m_tData = CDateTime( m_nDelta + (pPage->Dictionary()->GetMilliseconds() / 1000) );
	}
	return &m_tData;
}


void	CDictPageActiveDatumDate::ResetData
		(
		CDictPageActivePtr //pPage
		)
{
	m_bStale = true;
}



/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumString::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumString::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	if ( m_tData != sData )
	{
		m_tData = sData;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}

/*---------------------------------------------------------------------+\

* VDictPageActiveDatum::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumString::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	CCharString	sData = rData.GetValueCCharString();
	return UpdateData(pPage, sData.Pointer());
}




/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumEnum::CDictPageActiveDatumEnum - constructor

\+---------------------------------------------------------------------*/
CDictPageActiveDatumEnum::CDictPageActiveDatumEnum
		(
		void
		)
		: VDictPageActiveDatum()
		, m_aList()
{
	CUnitsOfMeasure	u;
	u.SetUsingName( "enum" );

	m_tData = 0L;
	m_tData.SetUnits( u );
	m_nEnumUnits = u;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumEnum::AddItem -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumEnum::AddItem
		(
		const char*	s
		)
{
	CVariantData v;
	v = CCharDescriptor( s );
	v.SetUnits( m_nEnumUnits );
	m_aList.AppendData( &v );
	return true;
}

/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumEnum::GetData -

\+---------------------------------------------------------------------*/
ConstCVariantDataPtr
		CDictPageActiveDatumEnum::GetData
		(
		CDictPageActivePtr //pPage
		)
{
	long	n = m_tData;
	if ( n < 0 )
		n = 0;
	else if ( long(m_aList.Length()) <= n )
		n = long(m_aList.Length()) - 1;

	return m_aList.PointArray( n );
}

/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumEnum::UpdateData -

\+---------------------------------------------------------------------*/
bool	CDictPageActiveDatumEnum::UpdateData
		(
		CDictPageActivePtr	pPage,
		const char*			sData
		)
{
	long	n = ::atol( sData );
	if ( m_tData != n )
	{
		m_tData = n;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}


bool	CDictPageActiveDatumEnum::UpdateData
		(
		CDictPageActivePtr		pPage,
		ConstCVariantDataRef	rData
		)
{
	long	n = rData;
	if ( m_tData != n )
	{
		m_tData = n;
		if ( pPage  &&  m_bReferenced )
			pPage->SetDirty();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * CDictPageActiveDatumEnum::ResetData -

\+---------------------------------------------------------------------*/
void	CDictPageActiveDatumEnum::ResetData
		(
		CDictPageActivePtr pPage
		)
{
	UpdateData( pPage, "0" );
}



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageActive - constructor

\+---------------------------------------------------------------------*/
CDictPageActive::CDictPageActive
		(
		void
		)
		: VDictionaryPage()
		, m_aContent()
		, m_nLastUpdate( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageActive - destructor

\+---------------------------------------------------------------------*/
CDictPageActive::~CDictPageActive
		(
		void
		)
{
	VDictPageActiveDatumPtr*	p = m_aContent.PointArray();
	if ( p )
	{
		VDictPageActiveDatumPtr*	pEnd = p + m_aContent.Length();

		while ( p < pEnd )
		{
			if ( *p )
			{
				delete *p;
				*p = 0;
			}
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * AddEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::AddDatumEntry
		(
		const char*				sKey,
		VDictPageActiveDatumPtr pDatum
		)
{
	bool		bResult = false;
	CCharString	tName( sKey );
	long	n = long(m_aContent.IndexOf( tName ));
	if ( n < 0 )
	{
		bResult = m_aContent.Add( tName, pDatum );
	}

	return bResult;
}


bool	CDictPageActive::AddDatumEntry
		(
		ConstCCharDescriptorRef	rKey,
		VDictPageActiveDatumPtr pDatum
		)
{
	bool		bResult = false;
	CCharString	tName( rKey );
	long	n = long(m_aContent.IndexOf( tName ));
	if ( n < 0 )
	{
		bResult = m_aContent.Add( tName, pDatum );
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * BeginUpdate -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::BeginUpdate
		(
		void
		)
{
	return true;	// for right now do nothing (look in EndUpdate)
}


/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::Update
		(
		const char* sKey,
		const char* sData
		)
{
	bool	bResult = false;
	long	n = long(m_aContent.IndexOf( CCharString( sKey ) ));
	if ( -1 < n )
	{
		VDictPageActiveDatumPtr*	p = m_aContent.PointArray( n );
		if ( p )
		{
			if ( *p )
				bResult = (*p)->UpdateData( this, sData );
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::Update
		(
		ConstCCharDescriptorRef	rKey,
		const char*				sData
		)
{
	bool		bResult = false;
	CCharString	tKey( rKey );
	long	n = long(m_aContent.IndexOf( rKey ));
	if ( -1 < n )
	{
		VDictPageActiveDatumPtr*	p = m_aContent.PointArray( n );
		if ( p )
		{
			if ( *p )
				bResult = (*p)->UpdateData( this, sData );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::UpdateByName
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tKey( rKey );
	long		n = long(m_aContent.IndexOf( rKey ));
	if ( -1 < n )
	{
		bResult = UpdateEntry( (unsigned long)n, rData );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::UpdateEntry
		(
		unsigned long			nSel,
		ConstCVariantDataRef	rData
		)
{
	bool	bResult = false;
	VDictPageActiveDatumPtr* p = m_aContent.PointArray( nSel );
	if ( p )
	{
		if ( *p )
			bResult = (*p)->UpdateData( this, rData );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}



/*---------------------------------------------------------------------+\

 * EndUpdate -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::EndUpdate
		(
		void
		)
{
	m_nLastUpdate = m_pDictionary->GetMilliseconds();
	return true;
}






/*---------------------------------------------------------------------+\

 * ResetAllEntries -

\+---------------------------------------------------------------------*/
void	CDictPageActive::ResetAllEntries
		(
		void
		)
{
	VDictPageActiveDatumPtr*	p = m_aContent.PointArray();
	VDictPageActiveDatumPtr*	pEnd = p + m_aContent.Length();

	while ( p < pEnd )
	{
		if ( *p )
			(*p)->ResetData( this );
		++p;
	}
	m_nLastUpdate = m_pDictionary->GetMilliseconds();
}


/*---------------------------------------------------------------------+\

 * LastUpdate -

\+---------------------------------------------------------------------*/
long	CDictPageActive::LastUpdate
		(
		void
		)
{
	return m_nLastUpdate;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
long	CDictPageActive::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	long	n = long(m_aContent.IndexOf( rName ));
	if ( -1 < n )
	{
		VDictPageActiveDatumPtr*	p = m_aContent.PointArray( n );
		if ( p )
		{
			if ( *p )
				(*p)->SetReferenced();
		}
	}
	return n;
}








/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
ConstCVariantDataPtr
		CDictPageActive::GetData
		(
		unsigned long	nSel
		)
{
	VDictPageActiveDatumPtr*	p = m_aContent.PointArray( nSel );
	if ( p )
	{
		if ( *p )
			return (*p)->GetData( this );
		else
			return 0;
	}
	else
	{
		return 0;
	}
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageActive::PutData
		(
		unsigned long,			//nSel,
		ConstCVariantDataPtr	//pData
		)
{
	return false;
}


VDictionaryEnumerator*
		CDictPageActive::GetEnumerator
		(
		void
		)
{
	VDictionaryEnumerator* p = new CDictPageActiveEnumerator( this );
	return p;
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
