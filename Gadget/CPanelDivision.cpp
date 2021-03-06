/*---------------------------------------------------------------------+\
|
|	CPanelDivision.cpp  --  brief description of what CPanelDivision.cpp is for
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
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPanelDivision.h"
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

 * CPanelDivision - constructor

\+---------------------------------------------------------------------*/
CPanelDivision::CPanelDivision
		(
		void
		)
		: VPanelChild()
		, m_aList()
		, m_pVisible( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CPanelDivision - copy constructor

\+---------------------------------------------------------------------*/
CPanelDivision::CPanelDivision
		(
		CPanelDivisionRef	r
		)
		: VPanelChild( r )
		, m_aList()
		, m_pVisible( 0 )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CPanelDivision - destructor

\+---------------------------------------------------------------------*/
CPanelDivision::~CPanelDivision
		(
		void
		)
{
	VPanelChildPtr*	p = m_aList.PointArray();
	VPanelChildPtr*	pEnd = p + m_aList.Length();

	while ( p < pEnd )
	{
		if ( *p )
			delete *p;
		++p;
	}

	if ( m_pVisible )
		delete m_pVisible;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CPanelDivisionRef
		CPanelDivision::operator=
		(
		CPanelDivisionRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
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
