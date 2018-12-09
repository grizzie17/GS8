/*---------------------------------------------------------------------+\
|
|	CEqVariable.cpp  --  brief description of what CEqVariable.cpp is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		another optimization regarding unit conversion
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Very slight optimization involving unit conversion
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
#include "CEqVariable.h"
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

 * CEquationVariable - constructor

\+---------------------------------------------------------------------*/
CEquationVariable::CEquationVariable
		(
		void
		)
		: VEquation(),
		m_tSelector(),
		m_tUoM()
{
}

/*---------------------------------------------------------------------+\

 * CEquationVariable - copy constructor

\+---------------------------------------------------------------------*/
CEquationVariable::CEquationVariable
		(
		ConstCEquationVariableRef	r
		)
		: VEquation( r ),
		m_tSelector( r.m_tSelector ),
		m_tUoM( r.m_tUoM )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CEquationVariable - destructor

\+---------------------------------------------------------------------*/
CEquationVariable::~CEquationVariable
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
CEquationVariableRef
		CEquationVariable::operator=
		(
		ConstCEquationVariableRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetVariableName -

\+---------------------------------------------------------------------*/
bool	CEquationVariable::SetVariableName
		(
		const char*	sVariableName
		)
{
	m_tSelector.SetName( sVariableName );
	return true;
}

/*---------------------------------------------------------------------+\

 * SetDesiredUoM -

\+---------------------------------------------------------------------*/
void	CEquationVariable::SetDesiredUoM
		(
		ConstCUnitsOfMeasureRef cUoM
		)
{
	m_tUoM = cUoM;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * GetSelector -

\+---------------------------------------------------------------------*/
bool	CEquationVariable::GetSelector
		(
		VDictionaryPtr pDict
		)
{
	VDictionary::Selector	tSel;
	tSel = m_tSelector.GetSelector( pDict );

	return tSel ? true : false;
}


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
		CEquationVariable::GetValue
		(
		VDictionaryPtr pDict
		)
{
	CVariantData	v;
	VDictionary::Selector tSel = m_tSelector.GetSelector( pDict );
	if ( tSel )
	{
		CVariantDataPtr	p;
		p = pDict->GetData( tSel );
		if ( p )
		{
			v = *p;
			if ( CVariantData::MT_NUMERIC == v.GetMetaType() )
			{
				int		u = m_tUoM.GetUnits();
				if ( u )
				{
					int		uv = v.GetUnits();
					if ( uv != u )
					{
						GFLOAT	f = v;
						f = CUnitsOfMeasure::Convert( u, uv, f );
						v = f;
						v.SetUnits( m_tUoM );
					}
				}
			}
		}
	}
	return v;
}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationVariable::Clone
		(
		void
		)
{
	return new CEquationVariable( *this );
}





}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
