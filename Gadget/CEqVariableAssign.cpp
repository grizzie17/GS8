/*---------------------------------------------------------------------+\
|
|	CEqVariableAssign.cpp  --  brief description of what CEqVariableAssign.cpp is for
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
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetVariableName that uses descriptor to send the name instead
		of null terminated string.
	28-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <string.h>
#include "CEqVariableAssign.h"
#include "CUnitsOfMeasure.h"
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

 * CEquationVariableAssign - constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssign::CEquationVariableAssign
		(
		void
		)
		: VEquationOperatorUnary(),
		m_tSelector()
{
}

/*---------------------------------------------------------------------+\

 * CEquationVariableAssign - copy constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssign::CEquationVariableAssign
		(
		ConstCEquationVariableAssignRef	r
		)
		: VEquationOperatorUnary( r ),
		m_tSelector( r.m_tSelector )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationVariableAssign - destructor

\+---------------------------------------------------------------------*/
CEquationVariableAssign::~CEquationVariableAssign
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
CEquationVariableAssignRef
		CEquationVariableAssign::operator=
		(
		ConstCEquationVariableAssignRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetVariableName -

\+---------------------------------------------------------------------*/
bool	CEquationVariableAssign::SetVariableName
		(
		const char*	sVariableName
		)
{
	m_tSelector.SetName( sVariableName );
	return true;
}


/*---------------------------------------------------------------------+\

 * SetVariableName -

\+---------------------------------------------------------------------*/
bool	CEquationVariableAssign::SetVariableName
		(
		CCharDescriptorRef rVariableName
		)
{
	m_tSelector.SetName( rVariableName );
	return true;
}

/*---------------------------------------------------------------------+\

 * GetSelector -

\+---------------------------------------------------------------------*/
bool	CEquationVariableAssign::GetSelector
		(
		VDictionaryPtr pDict
		)
{
	VDictionary::Selector	tSel;
	tSel = m_tSelector.GetSelector( pDict );

	return tSel ? true : false;
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
		CEquationVariableAssign::GetValue
		(
		VDictionaryPtr pDict
		)
{
	VDictionary::Selector tSel = m_tSelector.GetSelector( pDict );
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	bool	bResult = pDict->PutData( tSel, &vOperand );
	if ( bResult )
		return vOperand;
	else
		return CVariantData( 0L );
}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationVariableAssign::Clone
		(
		void
		)
{
	return new CEquationVariableAssign( *this );
}





NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

