/*---------------------------------------------------------------------+\
|
|	CEqVariableIndirect.cpp  --  brief description of what VariableIndirect.cpp is for
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
	02-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
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
#include "CEqVariableIndirect.h"
#include "CUnitsOfMeasure.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CEquationVariableIndirect - constructor

\+---------------------------------------------------------------------*/
CEquationVariableIndirect::CEquationVariableIndirect
		(
		void
		)
		: VEquationOperatorUnary(),
		m_tSelector()
{
}

/*---------------------------------------------------------------------+\

 * CEquationVariableIndirect - copy constructor

\+---------------------------------------------------------------------*/
CEquationVariableIndirect::CEquationVariableIndirect
		(
		ConstCEquationVariableIndirectRef	r
		)
		: VEquationOperatorUnary( r ),
		m_tSelector( r.m_tSelector )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationVariableIndirect - destructor

\+---------------------------------------------------------------------*/
CEquationVariableIndirect::~CEquationVariableIndirect
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
CEquationVariableIndirectRef
		CEquationVariableIndirect::operator=
		(
		ConstCEquationVariableIndirectRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}



/*---------------------------------------------------------------------+\

 * GetSelector -

\+---------------------------------------------------------------------*/
bool	CEquationVariableIndirect::GetSelector
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
		CEquationVariableIndirect::GetValue
		(
		VDictionaryPtr pDict
		)
{
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );
	CCharString		tName;

	tName = *m_tSelector.Name();
	if ( vOperand != tName )
	{
		tName = vOperand.GetValueCCharString();
		m_tSelector.SetName( tName );
	}
	VDictionary::Selector tSel = m_tSelector.GetSelector( pDict );

	ConstCVariantDataPtr	pv = pDict->GetData( tSel );
	if ( pv )
		return *pv;
	else
		return CVariantData();
}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationVariableIndirect::Clone
		(
		void
		)
{
	return new CEquationVariableIndirect( *this );
}





}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
