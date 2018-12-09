/*---------------------------------------------------------------------+\
|
|	VDictionaryPage.cpp  --  brief description of what VDictionaryPage.cpp is for
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
	12-Nov-2015			J.Griswold		(Reviewed by: xxx)
		Change nSel to be unsigned long
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	21-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for new "standardized" update functionality
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for the concept of locked data (does not change)
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
#include "VDictionaryPage.h"
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * VDictionaryPage - constructor

\+---------------------------------------------------------------------*/
VDictionaryPage::VDictionaryPage
		(
		void
		)
		: m_cPageID( 0 ),
		m_nRefCount( 0 ),
		m_pDictionary( 0 )
{
}

/*---------------------------------------------------------------------+\

 * ~VDictionaryPage - destructor

\+---------------------------------------------------------------------*/
VDictionaryPage::~VDictionaryPage
		(
		void
		)
{
	m_cPageID = 0;
	m_pDictionary = 0;
}

/*---------------------------------------------------------------------+\

 * RefCount - get reference (usage) count

\+---------------------------------------------------------------------*/
long	VDictionaryPage::RefCount
		(
		void
		)
{
	return m_nRefCount;
}

/*---------------------------------------------------------------------+\

 * AddRef - notify object of reference usage

\+---------------------------------------------------------------------*/
long	VDictionaryPage::AddRef
		(
		void
		)
{
	return ++m_nRefCount;
}

/*---------------------------------------------------------------------+\

 * Release - notify object of released usage

\+---------------------------------------------------------------------*/
long	VDictionaryPage::Release
		(
		void
		)
{
	long	n = --m_nRefCount;
	if ( n < 1 )
		delete this;
	return n;
}


/*---------------------------------------------------------------------+\

* AddEntry -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::AddEntry
		(
		const char*				sName,
		ConstCVariantDataRef	rData
		)
{
	CCharDescriptor	tName( sName );
	return AddEntry( tName, rData );
}

bool	VDictionaryPage::AddEntry
		(
		ConstCCharDescriptorRef	,//rKey,
		ConstCVariantDataRef	//rData
		)
{
	return false;
}

bool	VDictionaryPage::AddEntry
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rData
		)
{
	CVariantData	tV( rData );
	return AddEntry( rKey, tV );
}

bool	VDictionaryPage::AddEntry
		(
		const char*	sKey,
		const char*	sData
		)
{
	CCharDescriptor	tKey( sKey );
	CCharDescriptor	tData( sData );
	return AddEntry( tKey, tData );
}


/*---------------------------------------------------------------------+\

 * LocateEntry -

\+---------------------------------------------------------------------*/
long	VDictionaryPage::LocateEntry
		(
		const char*	sName
		)
{
	CCharString	tName( sName );
	return LocateEntry( tName );
}


/*---------------------------------------------------------------------+\

 * IsDataLocked -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::IsDataLocked
		(
		unsigned long	//nSel
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * SetPageID -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::SetPageID
		(
		char	c
		)
{
	m_cPageID = c;
	return true;
}


/*---------------------------------------------------------------------+\

 * SetDictionary -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::SetDictionary
		(
		VDictionaryPageServerPtr pDict
		)
{
	m_pDictionary = pDict;
	return true;
}


/*---------------------------------------------------------------------+\

 * Dictionary -

\+---------------------------------------------------------------------*/
VDictionaryPageServerPtr
		VDictionaryPage::Dictionary
		(
		void
		)
{
	return m_pDictionary;
}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::UpdateByName
		(
		const char*		sKey,
		CVariantDataRef	rData
		)
{
	CCharDescriptor	tKey( sKey );

	return UpdateByName( tKey, rData );
}


/*---------------------------------------------------------------------+\

 * UpdateEntry -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::UpdateEntry
		(
		unsigned long	nSel,
		CVariantDataRef	rData
		)
{
	CVariantData	v = rData;
	return PutData( nSel, &v );
}


/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	VDictionaryPage::AddAlias
		(
		const char*	sKey,
		const char*	sAlias
		)
{
	CCharString	tKey( sKey );
	CCharString	tAlias( sAlias );

	return AddAlias( tKey, tAlias );
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


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
