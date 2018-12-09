/*---------------------------------------------------------------------+\
|
|	VEqOpTrinary.cpp  --  brief description of what VEqOpTrinary.cpp is for
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
	18-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VEqOpTrinary.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
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

 * VEquationOperatorTrinary - constructor

\+---------------------------------------------------------------------*/
VEquationOperatorTrinary::VEquationOperatorTrinary
		(
		void
		)
		: VEquation(),
		m_pControl( 0 ),
		m_pLeft( 0 ),
		m_pRight( 0 )
{
}

/*---------------------------------------------------------------------+\

 * VEquationOperatorTrinary - copy constructor

\+---------------------------------------------------------------------*/
VEquationOperatorTrinary::VEquationOperatorTrinary
		(
		VEquationOperatorTrinaryRef	r
		)
		: VEquation( r ),
		m_pControl( 0 ),
		m_pLeft( 0 ),
		m_pRight( 0 )
{
	if ( r.m_pControl )
		m_pControl = r.m_pControl->Clone();
	if ( r.m_pLeft )
		m_pLeft = r.m_pLeft->Clone();
	if ( r.m_pRight )
		m_pRight = r.m_pRight->Clone();
}

/*---------------------------------------------------------------------+\

 * ~VEquationOperatorTrinary - destructor

\+---------------------------------------------------------------------*/
VEquationOperatorTrinary::~VEquationOperatorTrinary
		(
		void
		)
{
	if ( m_pControl )
		delete m_pControl;

	if ( m_pLeft )
		delete m_pLeft;

	if ( m_pRight )
		delete m_pRight;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
VEquationOperatorTrinaryRef
		VEquationOperatorTrinary::operator=
		(
		VEquationOperatorTrinaryRef	r
		)
{
	VEquation::operator=( r );
	if ( m_pControl )
		delete m_pControl;
	if ( r.m_pControl )
		m_pControl = r.m_pControl->Clone();
	else
		m_pControl = 0;

	if ( m_pLeft )
		delete m_pLeft;
	if ( r.m_pLeft )
		m_pLeft = r.m_pLeft->Clone();
	else
		m_pLeft = 0;

	if ( m_pRight )
		delete m_pRight;
	if ( r.m_pRight )
		m_pRight = r.m_pRight->Clone();
	else
		m_pRight = 0;

	return *this;
}


/*---------------------------------------------------------------------+\

 * SetControl -

\+---------------------------------------------------------------------*/
void	VEquationOperatorTrinary::SetControl
		(
		VEquationPtr	pControl
		)
{
	if ( m_pControl )
		delete m_pControl;
	m_pControl = pControl;
}

/*---------------------------------------------------------------------+\

 * SetLeft -

\+---------------------------------------------------------------------*/
void	VEquationOperatorTrinary::SetLeft
		(
		VEquationPtr pLeft
		)
{
	if ( m_pLeft )
		delete m_pLeft;
	m_pLeft = pLeft;
}

/*---------------------------------------------------------------------+\

 * SetRight -

\+---------------------------------------------------------------------*/
void	VEquationOperatorTrinary::SetRight
		(
		VEquationPtr pRight
		)
{
	if ( m_pRight )
		delete m_pRight;
	m_pRight = pRight;
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
