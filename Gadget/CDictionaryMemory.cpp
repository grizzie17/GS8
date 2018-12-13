/*---------------------------------------------------------------------+\
|
|	CDictionaryMemory.cpp  --  Wrapper clas to implement storage registers for expressions
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
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Increase number of registers from 10 to 16
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add GetMilliseconds
	20-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictionaryMemory.h"
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

 * CDictionaryMemory - constructor

\+---------------------------------------------------------------------*/
CDictionaryMemory::CDictionaryMemory
		(
		void
		)
		: m_pDict( 0 )
		, m_pControl( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CDictionaryMemory - constructor

\+---------------------------------------------------------------------*/
CDictionaryMemory::CDictionaryMemory
		(
		VDictionaryPtr	p
		)
		: m_pDict( p )
		, m_pControl( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CDictionaryMemory - constructor

\+---------------------------------------------------------------------*/
CDictionaryMemory::CDictionaryMemory
		(
		VDictionaryPtr	pDict,
		VControlPtr		pControl
		)
		: m_pDict( pDict )
		, m_pControl( pControl )
{
}

/*---------------------------------------------------------------------+\

 * ~CDictionaryMemory - destructor

\+---------------------------------------------------------------------*/
CDictionaryMemory::~CDictionaryMemory
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CDictionaryMemoryRef
		CDictionaryMemory::operator=
		(
		VDictionaryPtr	p
		)
{
	m_pDict = p;
	return *this;
}


/*---------------------------------------------------------------------+\

 * Store -

\+---------------------------------------------------------------------*/
void	CDictionaryMemory::Store
		(
		int						nRegister,
		ConstCVariantDataRef	rData
		)
{
	if ( 0 <= nRegister  &&  nRegister < 16 )
	{
		m_aRegisters[nRegister] = rData;
	}
}


/*---------------------------------------------------------------------+\

 * Recall -

\+---------------------------------------------------------------------*/
CVariantData
		CDictionaryMemory::Recall
		(
		int		nRegister
		)
{
	if ( 0 <= nRegister  &&  nRegister < 16 )
	{
		return m_aRegisters[nRegister];
	}
	else
	{
		return CVariantData( 0L );
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

 * BeginCalculate -

\+---------------------------------------------------------------------*/
void	CDictionaryMemory::BeginCalculate
		(
		void
		)
{
	m_pDict->BeginCalculate();
}

/*---------------------------------------------------------------------+\

 * EndCalculate -

\+---------------------------------------------------------------------*/
void	CDictionaryMemory::EndCalculate
		(
		void
		)
{
	m_pDict->EndCalculate();
}



/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CDictionaryMemory::LocateEntry
		(
		ConstCCharStringRef	rName
		)
{
	return m_pDict->LocateEntry( rName );
}


/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
VDictionary::Selector
		CDictionaryMemory::LocateEntry
		(
		const char* sName
		)
{
	return m_pDict->LocateEntry( sName );
}


/*---------------------------------------------------------------------+\

 * GetData -

\+---------------------------------------------------------------------*/
CVariantDataPtr
		CDictionaryMemory::GetData
		(
		VDictionary::Selector nSel
		)
{
	return m_pDict->GetData( nSel );
}


/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictionaryMemory::PutData
		(
		VDictionary::Selector nSel,
		CVariantDataPtr pData
		)
{
	return m_pDict->PutData( nSel, pData );
}


/*---------------------------------------------------------------------+\

 * IsDataLocked -

\+---------------------------------------------------------------------*/
bool	CDictionaryMemory::IsDataLocked
		(
		VDictionary::Selector nSel
		)
{
	return m_pDict->IsDataLocked( nSel );
}



/*---------------------------------------------------------------------+\

 * PushDictionaryPage -

\+---------------------------------------------------------------------*/
bool	CDictionaryMemory::PushDictionaryPage
		(
		VDictionaryPage* //pDict
		)
{
	// don't pass through to the main dictionary
	return false;
}


/*---------------------------------------------------------------------+\

 * PopDictionaryPage -

\+---------------------------------------------------------------------*/
bool	CDictionaryMemory::PopDictionaryPage
		(
		void
		)
{
	// don't pass through to the main dictionary
	return false;
}


/*---------------------------------------------------------------------+\

 * IsDirty -

\+---------------------------------------------------------------------*/
bool	CDictionaryMemory::IsDirty
		(
		void
		)
{
	return m_pDict->IsDirty();
}


/*---------------------------------------------------------------------+\

 * GetMilliseconds -

\+---------------------------------------------------------------------*/
long	CDictionaryMemory::GetMilliseconds
		(
		void
		)
{
	return m_pDict->GetMilliseconds();
}



/*---------------------------------------------------------------------+\

 * GetType -

\+---------------------------------------------------------------------*/
int		CDictionaryMemory::GetType
		(
		void
		)
{
	return 'M';
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictionaryMemory::GetEnumerator
		(
		void
		)
{
	return m_pDict->GetEnumerator();
}


/*---------------------------------------------------------------------+\

 * GetPageEnumerator -

\+---------------------------------------------------------------------*/
VDictionaryEnumerator*
		CDictionaryMemory::GetPageEnumerator
		(
		char	cPageID
		)
{
	return m_pDict->GetPageEnumerator( cPageID );
}


/*---------------------------------------------------------------------+\

 * GetVariableIF -

\+---------------------------------------------------------------------*/
VVariablePtr
		CDictionaryMemory::GetVariableIF
		(
		void
		)
{
	return m_pDict->GetVariableIF();
}






}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
