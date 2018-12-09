/*---------------------------------------------------------------------+\
|
|	CRotation.h  --  brief description of what CRotation.h is for
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
	28-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changed input values to represent degrees to correctly
		support XML schema
	09-Dec-2009			C.Cason			(Reviewed by: R.Hosea)
		Changed GFLOAT cast to explicit return in GetValue
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
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
#include "CRotation.h"
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

 * CRotation - constructor

\+---------------------------------------------------------------------*/
CRotation::CRotation
		(
		void
		)
		: VElement(),
		m_tValue()
{
}

/*---------------------------------------------------------------------+\

 * CRotation - copy constructor

\+---------------------------------------------------------------------*/
CRotation::CRotation
		(
		CRotationRef	r
		)
		: VElement( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CRotation - destructor

\+---------------------------------------------------------------------*/
CRotation::~CRotation
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
CRotationRef
		CRotation::operator=
		(
		CRotationRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetPointValue -

\+---------------------------------------------------------------------*/
void	CRotation::SetValue
		(
		float	f
		)
{
	CVariantData	vX;

	vX = f;
	m_tValue.SetValue( vX );
}


/*---------------------------------------------------------------------+\

 * SetEquation -

\+---------------------------------------------------------------------*/
void	CRotation::SetEquation
		(
		VEquationPtr p
		)
{
	m_tValue.SetEquation( p );
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
GFLOAT	CRotation::GetValue
		(
		void
		)
{
	return (m_tValue.GetCachedValue());
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

 * Calculate -

\+---------------------------------------------------------------------*/
int		CRotation::Calculate
		(
		VDictionaryPtr pDict
		)
{
	if ( m_tValue.Calculate( pDict ) )
		return VRDR_CALCULATE_UNDETERMINED;
	else
		return VRDR_CALCULATE_NONE;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CRotation::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	GFLOAT	f = m_tValue.GetCachedValue();

	// convert to radians
	f *= GFLOAT_PI / GFLOAT_180;

	return pQueue->SetRotation( f );
}




}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
