/*---------------------------------------------------------------------+\
|
|	CDictPageAlerts.cpp  --  Dictionary page handling Alerts
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
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for reseting all of the entries to a default value
	18-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictPageAlerts.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN

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
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageAlerts - constructor

\+---------------------------------------------------------------------*/
CDictPageAlerts::CDictPageAlerts
		(
		void
		)
		: VDictionaryPage(),
		m_aContent(),
		m_pEventsPage( 0 ),
		m_tAlertSelector()
{
	m_tAlertSelector.SetName( "E:Alert" );
}


/*---------------------------------------------------------------------+\

 * ~CDictPageAlerts - destructor

\+---------------------------------------------------------------------*/
CDictPageAlerts::~CDictPageAlerts
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * AddEntry -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

bool	CDictPageAlerts::AddEntry
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( rKey );
	long	n = long(m_aContent.IndexOf( tName ));

	if ( n < 0 )
	{
		char	sKeyTemp[128];
		strcpy_s( sKeyTemp, sizeof(sKeyTemp), "E:" );
		rKey.ConcatenateTo( sKeyTemp, sizeof(sKeyTemp) );

		AlertInfo	info;
		info.sel.SetName( sKeyTemp );
		info.v = false;
		if ( rData == "Y"  ||  rData == "T" )
			info.v = true;
		bResult = m_aContent.Add( tName, info );
	}

	return bResult;
}

//END_OVERRUN_WARNING

/*---------------------------------------------------------------------+\

* AddEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::AddEntry
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( rKey );
	long	n = long( m_aContent.IndexOf( tName ) );

	if ( n < 0 )
	{
		char	sKeyTemp[128];
		strcpy_s( sKeyTemp, sizeof( sKeyTemp ), "E:" );
		rKey.ConcatenateTo( sKeyTemp, sizeof( sKeyTemp ) );

		bool		b = rData.GetValueBool();
		AlertInfo	info;
		info.sel.SetName( sKeyTemp );
		info.v = b;
		bResult = m_aContent.Add( tName, info );
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::Update
		(
		const char*	sKey,
		const char*	sData
		)
{
	CCharDescriptor	tName( sKey );
	CCharDescriptor	tData( sData );

	return Update( tName, tData );
}


/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::Update
		(
		CCharDescriptorRef	rKey,
		CCharDescriptorRef	rData
		)
{
	bool	bResult = false;
	long	n = long(m_aContent.IndexOf( CCharString( rKey ) ));
	if ( -1 < n )
	{
		bResult = Update( (unsigned long)n, rData );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Update -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::Update
		(
		unsigned long		nSel,
		CCharDescriptorRef	rData
		)
{
	bool		bResult = false;
	AlertInfo*	p = m_aContent.PointArray( nSel );
	if ( p )
	{
		bool	b = false;
		bool	bActive = p->v;
		rData.ConvertUppercase();
		if ( rData == "Y"  ||  rData == "T" )
			b = true;
		if ( bActive != b )
		{
			p->v = b;

			if ( m_pDictionary )
			{
				VDictionary::Selector	nSel2;
				nSel2 = p->sel.GetSelector( m_pDictionary );
				m_pDictionary->PutData( nSel2, &p->v );
				m_pDictionary->SetDirty( true );

				if ( b )
				{
					CCharStringPtr sp = p->sel.Name();
					const char*	s = sp->Pointer(2);

					CVariantData	v = s;
					nSel2 = m_tAlertSelector.GetSelector( m_pDictionary );
					m_pDictionary->PutData( nSel2, &v );
				}
			}
		}
		bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::UpdateByName
		(
		CCharDescriptorRef	rKey,
		CVariantDataRef		rData
		)
{
	bool	bResult = false;
	long	n = long(m_aContent.IndexOf( CCharString( rKey ) ));
	if ( -1 < n )
	{
		bResult = UpdateEntry( (unsigned long)n, rData );
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * UpdateEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::UpdateEntry
		(
		unsigned long	nSel,
		CVariantDataRef	rData
		)
{
	bool		bResult = false;
	AlertInfo*	p = m_aContent.PointArray( nSel );
	if ( p )
	{
		bool	b = rData.GetValueBool();
		bool	bActive = p->v;
		if ( bActive != b )
		{
			p->v = b;

			if ( m_pDictionary )
			{
				VDictionary::Selector	nSel2;
				nSel2 = p->sel.GetSelector( m_pDictionary );
				m_pDictionary->PutData( nSel2, &p->v );
				m_pDictionary->SetDirty( true );

				if ( b )
				{
					CCharStringPtr sp = p->sel.Name();
					const char*	s = sp->Pointer(2);

					CVariantData	v = s;
					nSel2 = m_tAlertSelector.GetSelector( m_pDictionary );
					m_pDictionary->PutData( nSel2, &v );
				}
			}
		}
		bResult = true;
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::AddAlias
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

 * ResetAllEntries -

\+---------------------------------------------------------------------*/
void	CDictPageAlerts::ResetAllEntries
		(
		void
		)
{
	AlertInfo*	p = m_aContent.PointArray();
	AlertInfo*	pEnd = p + m_aContent.Length();

	while ( p < pEnd )
	{
		p->v = false;
		++p;
	}
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
long	CDictPageAlerts::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	return long(m_aContent.IndexOf( rName ));
}






/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CDictPageAlerts::GetData
		(
		unsigned long	nSel
		)
{
	AlertInfo*	p = m_aContent.PointArray( nSel );
	if ( p )
		return &(p->v);
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageAlerts::PutData
		(
		unsigned long	,//nSel,
		CVariantDataPtr //pData
		)
{
	return false;
}


VDictionaryEnumerator*
		CDictPageAlerts::GetEnumerator
		(
		void
		)
{
	CDictPageAlertsEnumerator* p = new CDictPageAlertsEnumerator( this );
	return p;
}





CDictPageAlertsEnumerator::CDictPageAlertsEnumerator
		(
		CDictPageAlerts*	p
		)
		: m_pPage( p ),
		m_nIndex( -1 )
{
}


CDictPageAlertsEnumerator::~CDictPageAlertsEnumerator
		(
		void
		)
{
}


bool	CDictPageAlertsEnumerator::MoveNext
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


void	CDictPageAlertsEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
}

CVariantData*
		CDictPageAlertsEnumerator::Current
		(
		void
		)
{
	CDictPageAlerts::AlertInfo* p = m_eList.Current();
	if ( p )
	{
		return &p->v;
	}
	else
	{
		return 0;
	}
}

long	CDictPageAlertsEnumerator::ID
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


CCharString
		CDictPageAlertsEnumerator::Key
		(
		void
		)
{
	return m_eList.Key();
}

CVariantData
		CDictPageAlertsEnumerator::Value
		(
		void
		)
{
	CVariantData*	p = Current();
	return *p;
}


char	CDictPageAlertsEnumerator::Page
		(
		void
		)
{
	return m_pPage->m_cPageID;
}




NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

