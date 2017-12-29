/*---------------------------------------------------------------------+\
|
|	CEqConstGaugeHeight.cpp  --  brief description of what CEqConstGaugeHeight.cpp is for
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
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqConstGaugeHeight.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

NAMESPACE_GADGET_BEGIN
//USING_NAMESPACE_COMMON
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

 * CEquationGaugeHeight - constructor

\+---------------------------------------------------------------------*/
CEquationGaugeHeight::CEquationGaugeHeight
		(
		void
		)
		: VEquationGauge()
{
}

/*---------------------------------------------------------------------+\

 * CEquationGaugeHeight - copy constructor

\+---------------------------------------------------------------------*/
CEquationGaugeHeight::CEquationGaugeHeight
		(
		CEquationGaugeHeightRef	r
		)
		: VEquationGauge( r )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationGaugeHeight - destructor

\+---------------------------------------------------------------------*/
CEquationGaugeHeight::~CEquationGaugeHeight
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
CEquationGaugeHeightRef
		CEquationGaugeHeight::operator=
		(
		CEquationGaugeHeightRef	r
		)
{
	VEquationGauge::operator = ( r );
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

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationGaugeHeight::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	long	x;
	long	y;
	m_pGauge->GetSize( pDict, x, y );

	return CVariantData( y );
}




/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationGaugeHeight::Clone
		(
		void
		)
{
	return new CEquationGaugeHeight( *this );
}







NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

