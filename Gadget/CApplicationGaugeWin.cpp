/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWin.cpp  --  brief description of what CApplicationGaugeWin.cpp is for
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
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to call Size instead of SetSize on draw object
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change background color to be "background" which numerically
		is different from "black"
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changes to support foreground/background (double-buffer) drawing.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Dispose of unnecessary functions
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UMachine.h"

#include "CApplicationGaugeWin.h"

#if defined( OS_MSWIN )
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CApplicationGaugeWin - constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWin::CApplicationGaugeWin
		(
		void
		)
		: CApplicationGauge()
{
}

/*---------------------------------------------------------------------+\

 * CApplicationGaugeWin - copy constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWin::CApplicationGaugeWin
		(
		ConstCApplicationGaugeWinRef	r
		)
		: CApplicationGauge( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CApplicationGaugeWin - destructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWin::~CApplicationGaugeWin
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
CApplicationGaugeWinRef
		CApplicationGaugeWin::operator=
		(
		ConstCApplicationGaugeWinRef	//r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * DrawWin - return pointer to windows specific draw object

\+---------------------------------------------------------------------*/
//CDrawWinPtr
//		CApplicationGaugeWin::DrawWin
//		(
//		void
//		)
//{
//	return CDrawWinPtr( Draw() );
//}

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

 * OnDraw -

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWin::OnDraw
		(
		void
		)
{
	long	w = 0;
	long	h = 0;

	if ( m_pScreen )
		m_pScreen->GetSize( 0, w, h );
	if ( m_pDraw )
	{
		IDrawPtr	pDraw = Draw();

		pDraw->Size( w, h );
	}

	return CApplicationGauge::OnDraw();
}


/*---------------------------------------------------------------------+\

 * MakeDraw -

\+---------------------------------------------------------------------*/
VDrawPtr
		CApplicationGaugeWin::MakeDraw
		(
		void
		)
{
	// TODO: add code to insert configuration entry for OS

	return inherited::MakeDraw();
}





NAMESPACE_GADGET_END



#endif	//	OS_MSWIN


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
