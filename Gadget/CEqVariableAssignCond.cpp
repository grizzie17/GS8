/*---------------------------------------------------------------------+\
|
|	CEqVariableAssignCond.cpp  --  brief description of what CEqVariableAssignCond.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
#include "CEqVariableAssignCond.h"
#include "CUnitsOfMeasure.h"
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

 * CEquationVariableAssignConditional - constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignConditional::CEquationVariableAssignConditional
		(
		void
		)
		: CEquationVariableAssign()
{
}

/*---------------------------------------------------------------------+\

 * CEquationVariableAssignConditional - copy constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignConditional::CEquationVariableAssignConditional
		(
		ConstCEquationVariableAssignConditionalRef	r
		)
		: CEquationVariableAssign( r )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationVariableAssignConditional - destructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignConditional::~CEquationVariableAssignConditional
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
CEquationVariableAssignConditionalRef
		CEquationVariableAssignConditional::operator=
		(
		ConstCEquationVariableAssignConditionalRef
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

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationVariableAssignConditional::GetValue
		(
		VDictionaryPtr pDict
		)
{
	VDictionary::Selector tSel = m_tSelector.GetSelector( pDict );
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );
	CVariantDataPtr	pPrevious = pDict->GetData( tSel );

	if ( pPrevious )
	{
		//bool	bResult;
		if ( vOperand != *pPrevious )
			pDict->PutData( tSel, &vOperand );
	}
	return vOperand;
}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationVariableAssignConditional::Clone
		(
		void
		)
{
	return new CEquationVariableAssignConditional( *this );
}





}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
