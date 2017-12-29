/*---------------------------------------------------------------------+\
|
|	CPosition.cpp  --  Identify position for new World coordinate system
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	17-Jul-2009			J.Griswold
		Change class hierarchy to use new VCoordinate class
	29-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPosition.h"
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

 * CPosition - constructor

\+---------------------------------------------------------------------*/
CPosition::CPosition
		(
		void
		)
		: VCoordinate()
{
}

/*---------------------------------------------------------------------+\

 * CPosition - copy constructor

\+---------------------------------------------------------------------*/
CPosition::CPosition
		(
		ConstCPositionRef	r
		)
		: VCoordinate( r )
{
}

/*---------------------------------------------------------------------+\

 * ~CPosition - destructor

\+---------------------------------------------------------------------*/
CPosition::~CPosition
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



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

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CPosition::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	GFLOAT	x = m_tX.GetCachedValue();
	GFLOAT	y = m_tY.GetCachedValue();

	return pQueue->SetPosition( x, y );
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CPosition::Render
		(
		VDictionaryPtr,
		VDrawPtr
		)
{
	// CPosition does not actually render
	return true;
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

