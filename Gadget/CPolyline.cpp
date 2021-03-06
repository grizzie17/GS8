/*---------------------------------------------------------------------+\
|
|	CPolyline.cpp  --  brief description of what CPolyline.cpp is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPolyline.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CPolyline - constructor

\+---------------------------------------------------------------------*/
CPolyline::CPolyline
		(
		void
		)
		: VPolylist()
{
}

/*---------------------------------------------------------------------+\

 * CPolyline - copy constructor

\+---------------------------------------------------------------------*/
CPolyline::CPolyline
		(
		ConstCPolylineRef	r
		)
		: VPolylist( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CPolyline - destructor

\+---------------------------------------------------------------------*/
CPolyline::~CPolyline
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
CPolylineRef
		CPolyline::operator=
		(
		ConstCPolylineRef
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

/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CPolyline::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr 		pDraw
		)
{
	bool	bResult = VPolylist::Render( pDict, pDraw );

	bResult = pDraw->BeginPolyline();
	if ( bResult )
	{
		bResult = VPolylist::Render( pDict, pDraw );
		if ( bResult )
			bResult = pDraw->EndPolyline();
	}

	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
