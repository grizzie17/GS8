/*---------------------------------------------------------------------+\
|
|	CDictPageConfigWrapper.cpp  --  Implementation of CVariantData Dictionary Page
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
#include "CDictPageConfigWrapper.h"
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
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageConfigWrapper - constructor

\+---------------------------------------------------------------------*/
CDictPageConfigWrapper::CDictPageConfigWrapper
		(
		void
		)
		: VDictionaryPage()
		, m_pConfig( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageConfigWrapper - destructor

\+---------------------------------------------------------------------*/
CDictPageConfigWrapper::~CDictPageConfigWrapper
		(
		void
		)
{
	// do not delete configuration object ... it is owned elswhere
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetConfiguration -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::SetConfiguration
		(
		CConfigurationPtr	pConfig
		)
{
	m_pConfig = pConfig;
	return true;
}

/*---------------------------------------------------------------------+\

 * AddEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::AddEntry
		(
		const char*				sName,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( sName );

	CVariantDataPtr	pv = m_pConfig->GetEntry( tName );
	if ( ! pv )
	{
		bResult = m_pConfig->AddEntry( tName.Pointer(), rData );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * AddEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::AddEntry
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool		bResult = false;
	CCharString	tName( rKey );

	CVariantDataPtr	pv = m_pConfig->GetEntry( tName );
	if ( ! pv )
	{
		bResult = m_pConfig->AddEntry( tName.Pointer(), rData );
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
long	CDictPageConfigWrapper::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	return m_pConfig->LocateEntry( rName );
}






/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
ConstCVariantDataPtr
		CDictPageConfigWrapper::GetData
		(
		unsigned long	nSel
		)
{
	return m_pConfig->GetData( nSel );
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::PutData
		(
		unsigned long			nSel,
		ConstCVariantDataPtr	pData
		)
{
	bool	bResult = m_pConfig->PutData( nSel, pData );
	if ( bResult )
	{
		if ( m_pDictionary )
			m_pDictionary->SetDirty( true );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::UpdateByName
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool	bResult = false;
	long	n = m_pConfig->LocateEntry( CCharString( rKey ) );
	if ( -1 < n )
	{
		bResult = m_pConfig->PutData( (unsigned long)n, &rData );
		if ( bResult )
		{
			if ( m_pDictionary )
				m_pDictionary->SetDirty( true );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * UpdateEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::UpdateEntry
		(
		unsigned long			nSel,
		ConstCVariantDataRef	rData
		)
{
	bool	bResult = false;
	bResult = m_pConfig->PutData( nSel, &rData );
	if ( bResult )
	{
		if ( m_pDictionary )
			m_pDictionary->SetDirty( true );
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapper::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	return m_pConfig->AddAlias( rKey, rAlias );
}




/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictPageConfigWrapper::GetEnumerator
		(
		void
		)
{
	CDictPageConfigWrapperEnumerator* p = new CDictPageConfigWrapperEnumerator( this );
	return p;
}


/*=====================================================================+\
||	 Enumerator
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * CDictPageConfigWrapperEnumerator - constructor

\+---------------------------------------------------------------------*/
CDictPageConfigWrapperEnumerator::CDictPageConfigWrapperEnumerator
		(
		CDictPageConfigWrapper*	p
		)
		: m_pPage( p )
		, m_nIndex( -1 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageConfigWrapperEnumerator - destructor

\+---------------------------------------------------------------------*/
CDictPageConfigWrapperEnumerator::~CDictPageConfigWrapperEnumerator
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * MoveNext -

\+---------------------------------------------------------------------*/
bool	CDictPageConfigWrapperEnumerator::MoveNext
		(
		void
		)
{
	bool	bResult = false;

	if ( m_nIndex < 0 )
	{
		m_nIndex = 0;
		m_eList = m_pPage->m_pConfig->GetEnumerator();
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
void	CDictPageConfigWrapperEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
}

/*---------------------------------------------------------------------+\

 * Current -

\+---------------------------------------------------------------------*/
const CVariantData*
		CDictPageConfigWrapperEnumerator::Current
		(
		void
		)
{
	const CVariantData* p = m_eList.Current();
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
long	CDictPageConfigWrapperEnumerator::ID
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

 * Key -

\+---------------------------------------------------------------------*/
CCharString
		CDictPageConfigWrapperEnumerator::Key
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
		CDictPageConfigWrapperEnumerator::Value
		(
		void
		)
{
	const CVariantData*	p = Current();
	if ( p )
		return *p;
	else
		return CVariantData( 0L );
}


/*---------------------------------------------------------------------+\

 * Page -

\+---------------------------------------------------------------------*/
char	CDictPageConfigWrapperEnumerator::Page
		(
		void
		)
{
	return m_pPage->m_cPageID;
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
