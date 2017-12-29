/*---------------------------------------------------------------------+\
|
|	CDictPageVariant.cpp  --  Implementation of CVariantData Dictionary Page
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
	08-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for new template Dictionary Page.
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	19-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add CCharDescriptor variations of Add and Update entries
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
#include "CDictPageVariant.h"
#include "LogFile.h"
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

 * CDictPageVariant - constructor

\+---------------------------------------------------------------------*/
CDictPageVariant::CDictPageVariant
		(
		void
		)
		: VDictionaryPage()
		//m_aContent()
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageVariant - destructor

\+---------------------------------------------------------------------*/
CDictPageVariant::~CDictPageVariant
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
bool	CDictPageVariant::AddEntry
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( rKey );
	index_t		n = m_aContent.IndexOf( tName );

	if ( n < 0 )
	{
		bResult = m_aContent.Add( tName, rData );
	}

	return bResult;
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
long	CDictPageVariant::LocateEntry
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
		CDictPageVariant::GetData
		(
		unsigned long	nSel
		)
{
	return m_aContent.ItemAtIndex( nSel );
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageVariant::PutData
		(
		unsigned long	nSel,
		CVariantDataPtr pData
		)
{
	CVariantDataPtr	p = m_aContent.ItemAtIndex( nSel );
	if ( p )
	{
		if ( *p != *pData )
		{
			*p = *pData;
			if ( m_pDictionary )
				m_pDictionary->SetDirty( true );
		}
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageVariant::UpdateByName
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
bool	CDictPageVariant::UpdateEntry
		(
		unsigned long	nSel,
		CVariantDataRef	rData
		)
{
	bool	bResult = false;
	CVariantDataPtr	p = m_aContent.PointArray( (index_t)nSel );
	if ( p )
	{
		if ( *p != rData )
		{
			*p = rData;
			if ( m_pDictionary )
				m_pDictionary->SetDirty( true );
		}
		bResult = true;
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageVariant::AddAlias
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

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictPageVariant::GetEnumerator
		(
		void
		)
{
	CDictPageVariantEnumerator* p = new CDictPageVariantEnumerator( this );
	return p;
}


/*=====================================================================+\
||	 Enumerator
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * CDictPageVariantEnumerator - constructor

\+---------------------------------------------------------------------*/
CDictPageVariantEnumerator::CDictPageVariantEnumerator
		(
		CDictPageVariant*	p
		)
		: m_pPage( p ),
		m_nIndex( -1 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageVariantEnumerator - destructor

\+---------------------------------------------------------------------*/
CDictPageVariantEnumerator::~CDictPageVariantEnumerator
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * MoveNext -

\+---------------------------------------------------------------------*/
bool	CDictPageVariantEnumerator::MoveNext
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

 * Reset -

\+---------------------------------------------------------------------*/
void	CDictPageVariantEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
}

/*---------------------------------------------------------------------+\

 * Current -

\+---------------------------------------------------------------------*/
CVariantData*
		CDictPageVariantEnumerator::Current
		(
		void
		)
{
	CVariantData* p = m_eList.Current();
	if ( p )
	{
		return p;
	}
	else
	{
		return 0;
	}
}

/*---------------------------------------------------------------------+\

 * ID -

\+---------------------------------------------------------------------*/
long	CDictPageVariantEnumerator::ID
		(
		void
		)
{
	long	n = long(m_eList.ID());
	long	c = Page();
	long	i = c - 'A';

	long	id = ((i + 1) << 24)  |  n;

	return id;
}


/*---------------------------------------------------------------------+\

 * Key -

\+---------------------------------------------------------------------*/
CCharString
		CDictPageVariantEnumerator::Key
		(
		void
		)
{
	return m_eList.Key();
}

/*---------------------------------------------------------------------+\

 * Value -

\+---------------------------------------------------------------------*/
CVariantData
		CDictPageVariantEnumerator::Value
		(
		void
		)
{
	CVariantData*	p = Current();
	if ( p )
		return *p;
	else
		return CVariantData( 0L );
}


/*---------------------------------------------------------------------+\

 * Page -

\+---------------------------------------------------------------------*/
char	CDictPageVariantEnumerator::Page
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

