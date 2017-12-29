/*---------------------------------------------------------------------+\
|
|	VEqOpQuaternary.cpp  --  brief description of what VEqOpQuaternary.cpp is for
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
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VEqOpQuaternary.h"
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

 * VEquationOperatorQuaternary - constructor

\+---------------------------------------------------------------------*/
VEquationOperatorQuaternary::VEquationOperatorQuaternary
		(
		void
		)
		: VEquation(),
		m_pOperand1( 0 ),
		m_pOperand2( 0 ),
		m_pOperand3( 0 ),
		m_pOperand4( 0 )
{
}

/*---------------------------------------------------------------------+\

 * VEquationOperatorQuaternary - copy constructor

\+---------------------------------------------------------------------*/
VEquationOperatorQuaternary::VEquationOperatorQuaternary
		(
		ConstVEquationOperatorQuaternaryRef	r
		)
		: VEquation( r ),
		m_pOperand1( 0 ),
		m_pOperand2( 0 ),
		m_pOperand3( 0 ),
		m_pOperand4( 0 )
{
	if ( r.m_pOperand1 )
		m_pOperand1 = r.m_pOperand1->Clone();
	if ( r.m_pOperand2 )
		m_pOperand2 = r.m_pOperand2->Clone();
	if ( r.m_pOperand3 )
		m_pOperand3 = r.m_pOperand3->Clone();
	if ( r.m_pOperand4 )
		m_pOperand4 = r.m_pOperand4->Clone();
}

/*---------------------------------------------------------------------+\

 * ~VEquationOperatorQuaternary - destructor

\+---------------------------------------------------------------------*/
VEquationOperatorQuaternary::~VEquationOperatorQuaternary
		(
		void
		)
{
	if ( m_pOperand1 )
		delete m_pOperand1;
	if ( m_pOperand2 )
		delete m_pOperand2;
	if ( m_pOperand3 )
		delete m_pOperand3;
	if ( m_pOperand4 )
		delete m_pOperand4;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
VEquationOperatorQuaternaryRef
		VEquationOperatorQuaternary::operator=
		(
		ConstVEquationOperatorQuaternaryRef	r
		)
{
	VEquation::operator=( r );

	if ( m_pOperand1 )
		delete m_pOperand1;
	if ( r.m_pOperand1 )
		m_pOperand1 = r.m_pOperand1->Clone();
	else
		m_pOperand1 = 0;

	if ( m_pOperand2 )
		delete m_pOperand2;
	if ( r.m_pOperand2 )
		m_pOperand2 = r.m_pOperand2->Clone();
	else
		m_pOperand2 = 0;

	if ( m_pOperand3 )
		delete m_pOperand3;
	if ( r.m_pOperand3 )
		m_pOperand3 = r.m_pOperand3->Clone();
	else
		m_pOperand3 = 0;

	if ( m_pOperand4 )
		delete m_pOperand4;
	if ( r.m_pOperand4 )
		m_pOperand4 = r.m_pOperand4->Clone();
	else
		m_pOperand4 = 0;

	return *this;
}


/*---------------------------------------------------------------------+\

 * SetOperand# -

\+---------------------------------------------------------------------*/
void	VEquationOperatorQuaternary::SetOperand1
		(
		VEquationPtr	pOp
		)
{
	if ( m_pOperand1 )
		delete m_pOperand1;
	m_pOperand1 = pOp;
}

void	VEquationOperatorQuaternary::SetOperand2
		(
		VEquationPtr	pOp
		)
{
	if ( m_pOperand2 )
		delete m_pOperand2;
	m_pOperand2 = pOp;
}

void	VEquationOperatorQuaternary::SetOperand3
		(
		VEquationPtr	pOp
		)
{
	if ( m_pOperand3 )
		delete m_pOperand3;
	m_pOperand3 = pOp;
}

void	VEquationOperatorQuaternary::SetOperand4
		(
		VEquationPtr	pOp
		)
{
	if ( m_pOperand4 )
		delete m_pOperand4;
	m_pOperand4 = pOp;
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

NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

