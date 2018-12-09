/*---------------------------------------------------------------------+\
|
|	CDictPageSystem.cpp  --  brief description of what CDictPageSystem.cpp is for
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

#include "CDictPageSystem.h"

#include "UPlatform.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

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


CDictPageSystemEnumerator::CDictPageSystemEnumerator
		(
		CDictPageSystem*	p
		)
		: m_pPage( p ),
		m_nIndex( -1 )
{
}


CDictPageSystemEnumerator::~CDictPageSystemEnumerator
		(
		void
		)
{
}


bool	CDictPageSystemEnumerator::MoveNext
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


void	CDictPageSystemEnumerator::Reset
		(
		void
		)
{
	m_nIndex = -1;
}

CVariantData*
		CDictPageSystemEnumerator::Current
		(
		void
		)
{
	VDictPageHandlerPtr* h = m_eList.Current();
	if ( h )
	{
		VDictPageHandlerPtr	p = *h;
		return p->GetData( m_pPage );
	}
	else
	{
		return 0;
	}
}


long	CDictPageSystemEnumerator::ID
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



CCharString
		CDictPageSystemEnumerator::Key
		(
		void
		)
{
	return m_eList.Key();
}

CVariantData
		CDictPageSystemEnumerator::Value
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


char	CDictPageSystemEnumerator::Page
		(
		void
		)
{
	return m_pPage->m_cPageID;
}


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageSystem - constructor

\+---------------------------------------------------------------------*/
CDictPageSystem::CDictPageSystem
		(
		void
		)
		: VDictionaryPage(),
		m_aContent()
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageSystem - destructor

\+---------------------------------------------------------------------*/
CDictPageSystem::~CDictPageSystem
		(
		void
		)
{
	VDictPageHandlerPtr*	p = m_aContent.PointArray();
	if ( p )
	{
		VDictPageHandlerPtr*	pEnd = p + m_aContent.Length();

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

 * AddEntryPageHandler -

\+---------------------------------------------------------------------*/
bool	CDictPageSystem::AddEntryPageHandler
		(
		const char*			sName,
		VDictPageHandlerPtr pHandler
		)
{
	bool		bResult = false;
	CCharString	tName( sName );
	long	n = long(m_aContent.IndexOf( tName ));
	if ( n < 0 )
	{
		bResult = m_aContent.Add( tName, pHandler );
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

 * BeginCalculate -

\+---------------------------------------------------------------------*/
void	CDictPageSystem::BeginCalculate
		(
		void
		)
{
	VDictPageHandlerPtr*	p = m_aContent.PointArray();
	if ( p )
	{
		VDictPageHandlerPtr*	pEnd = p + m_aContent.Length();

		while ( p < pEnd )
		{
			if ( *p )
				(*p)->BeginCalculate( this );
			++p;
		}
	}
}


/*---------------------------------------------------------------------+\

 * EndCalculate -

\+---------------------------------------------------------------------*/
void	CDictPageSystem::EndCalculate
		(
		void
		)
{
	VDictPageHandlerPtr*	p = m_aContent.PointArray();
	if ( p )
	{
		VDictPageHandlerPtr*	pEnd = p + m_aContent.Length();

		while ( p < pEnd )
		{
			if ( *p )
				(*p)->EndCalculate( this );
			++p;
		}
	}
}



/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
long	CDictPageSystem::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	long	n = long(m_aContent.IndexOf( rName ));
	return n;
}





/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CDictPageSystem::GetData
		(
		unsigned long	nSel
		)
{
	VDictPageHandlerPtr*	p = m_aContent.PointArray( nSel );
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
bool	CDictPageSystem::PutData
		(
		unsigned long	nSel,
		CVariantDataPtr	pData
		)
{
	VDictPageHandlerPtr*	p = m_aContent.PointArray( nSel );
	if ( p )
	{
		if ( *p )
			return (*p)->PutData( this, pData );
		else
			return false;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageSystem::UpdateByName
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

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictPageSystem::GetEnumerator
		(
		void
		)
{
	CDictPageSystemEnumerator*	p = new CDictPageSystemEnumerator( this );
	return p;
}


/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageSystem::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
