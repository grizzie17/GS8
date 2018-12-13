/*---------------------------------------------------------------------+\
|
|	CMouseAreaList.cpp  --  brief description of what CMouseAreaList.cpp is for
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CMouseAreaList.h"
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

 * CMouseAreaList - constructor

\+---------------------------------------------------------------------*/
CMouseAreaList::CMouseAreaList
		(
		void
		)
		: m_aList()
{
}

/*---------------------------------------------------------------------+\

 * CMouseAreaList - copy constructor

\+---------------------------------------------------------------------*/
CMouseAreaList::CMouseAreaList
		(
		ConstCMouseAreaListRef
		)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CMouseAreaList - destructor

\+---------------------------------------------------------------------*/
CMouseAreaList::~CMouseAreaList
		(
		void
		)
{
	CMouseAreaPtr*	p = m_aList.PointArray();
	if ( p )
	{
		CMouseAreaPtr*	pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
				delete (*p);
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CMouseAreaListRef
		CMouseAreaList::operator=
		(
		ConstCMouseAreaListRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
void	CMouseAreaList::AddArea
		(
		CMouseAreaPtr pArea
		)
{
	CMouseAreaPtr	*p = m_aList.AppendArray();
	if ( p )
	{
		*p = pArea;
	}
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CMouseAreaList::Calculate
		(
		VDictionaryPtr pDict
		)
{
	bool	bResult = false;
	CMouseAreaPtr*	p = m_aList.PointArray();
	if ( p )
	{
		CMouseAreaPtr*	pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
				bResult = (*p)->Calculate( pDict )  ||  bResult;
			++p;
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CMouseAreaList::ProcessMouse
		(
		VDictionaryPtr	pDict,
		CMouseLocatePtr	pMouseLocate
		)
{
	bool	bResult = true;
	CMouseAreaPtr*	p = m_aList.PointArray();
	if ( p )
	{
		CMouseAreaPtr*	pEnd = p + m_aList.Length();
		while ( p < pEnd  &&  bResult )
		{
			if ( *p )
				bResult = (*p)->ProcessMouse( pDict, pMouseLocate );
			++p;
		}
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


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
