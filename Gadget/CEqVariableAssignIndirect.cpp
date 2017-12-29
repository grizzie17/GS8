/*---------------------------------------------------------------------+\
|
|	CEqVariableAssignIndirect.cpp  --  brief description of what VariableIndirect.cpp is for
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
#include "CEqVariableAssignIndirect.h"
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

 * CEquationVariableAssignIndirect - constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignIndirect::CEquationVariableAssignIndirect
		(
		void
		)
		: VEquationOperatorBinary(),
		m_tSelector()
{
}

/*---------------------------------------------------------------------+\

 * CEquationVariableAssignIndirect - copy constructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignIndirect::CEquationVariableAssignIndirect
		(
		ConstCEquationVariableAssignIndirectRef	r
		)
		: VEquationOperatorBinary( r ),
		m_tSelector( r.m_tSelector )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationVariableAssignIndirect - destructor

\+---------------------------------------------------------------------*/
CEquationVariableAssignIndirect::~CEquationVariableAssignIndirect
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
CEquationVariableAssignIndirectRef
		CEquationVariableAssignIndirect::operator=
		(
		ConstCEquationVariableAssignIndirectRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}



/*---------------------------------------------------------------------+\

 * GetSelector -

\+---------------------------------------------------------------------*/
bool	CEquationVariableAssignIndirect::GetSelector
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
		CEquationVariableAssignIndirect::GetValue
		(
		VDictionaryPtr pDict
		)
{
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );
	CCharString		tName;

	tName = *m_tSelector.Name();
	if ( vRight != tName )
	{
		tName = vRight.GetValueCCharString();
		m_tSelector.SetName( tName );
	}
	VDictionary::Selector tSel = m_tSelector.GetSelector( pDict );

	bool	bResult = pDict->PutData( tSel, &vLeft );
	if ( bResult )
		return vLeft;
	else
		return CVariantData( 0L );

}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationVariableAssignIndirect::Clone
		(
		void
		)
{
	return new CEquationVariableAssignIndirect( *this );
}





NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

