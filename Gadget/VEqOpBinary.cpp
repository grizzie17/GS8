/*---------------------------------------------------------------------+\
|
|	VEqOpBinary.cpp  --  brief description of what VEqOpBinary.cpp is for
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
	26-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Change the copy constructor to receive a type of const
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
#include "VEqOpBinary.h"
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

 * VEquationOperatorBinary - constructor

\+---------------------------------------------------------------------*/
VEquationOperatorBinary::VEquationOperatorBinary
		(
		void
		)
		: VEquation(),
		m_pLeft( 0 ),
		m_pRight( 0 )
{
}

/*---------------------------------------------------------------------+\

 * VEquationOperatorBinary - copy constructor

\+---------------------------------------------------------------------*/
VEquationOperatorBinary::VEquationOperatorBinary
		(
		ConstVEquationOperatorBinaryRef	r
		)
		: VEquation( r ),
		m_pLeft( 0 ),
		m_pRight( 0 )
{
	if ( r.m_pLeft )
		m_pLeft = r.m_pLeft->Clone();
	if ( r.m_pRight )
		m_pRight = r.m_pRight->Clone();
}

/*---------------------------------------------------------------------+\

 * ~VEquationOperatorBinary - destructor

\+---------------------------------------------------------------------*/
VEquationOperatorBinary::~VEquationOperatorBinary
		(
		void
		)
{
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
VEquationOperatorBinaryRef
		VEquationOperatorBinary::operator=
		(
		VEquationOperatorBinaryRef	r
		)
{
	VEquation::operator=( r );
	if ( m_pLeft )
		delete m_pLeft;
	if ( r.m_pLeft )
		m_pLeft = r.m_pLeft->Clone();

	if ( m_pRight )
		delete m_pRight;
	if ( r.m_pRight )
		m_pRight = r.m_pRight->Clone();

	return *this;
}

/*---------------------------------------------------------------------+\

 * SetLeft -

\+---------------------------------------------------------------------*/
void	VEquationOperatorBinary::SetLeft
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
void	VEquationOperatorBinary::SetRight
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

NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

