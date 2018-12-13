/*---------------------------------------------------------------------+\
|
|	CEqOpUnitConvert.cpp  --  brief description of what CEqOpUnitConvert.cpp is for
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
	30-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>
#include <float.h>

#include "CEqOpUnitConvert.h"
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

 * CEquationOperatorUnitConvert - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitConvert::CEquationOperatorUnitConvert
		(
		void
		)
		: VEquationOperatorBinary(),
		m_sUnitName(),
		m_tUnits()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorUnitConvert - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitConvert::CEquationOperatorUnitConvert
		(
		CEquationOperatorUnitConvertRef	r
		)
		: VEquationOperatorBinary( r ),
		m_sUnitName( r.m_sUnitName ),
		m_tUnits( r.m_tUnits )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorUnitConvert - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitConvert::~CEquationOperatorUnitConvert
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
CEquationOperatorUnitConvertRef
		CEquationOperatorUnitConvert::operator=
		(
		CEquationOperatorUnitConvertRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorUnitConvert::GetValue
		(
		VDictionaryPtr	pDict
		)
{

	CVariantData	vResult;

	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	CVariantData::V_METATYPE	t = vLeft.GetMetaType();

	if ( CVariantData::MT_NUMERIC == t )
	{
		if ( vRight != m_sUnitName )
		{
			m_sUnitName = vRight.GetValueCCharString();
			m_tUnits.SetUsingString( m_sUnitName );
		}

		GFLOAT	fLeft = vLeft;
		int		nLeftUnits = vLeft.GetUnits();

		if ( m_tUnits == nLeftUnits )
		{
			vResult = vLeft;
		}
		else
		{
			fLeft = CUnitsOfMeasure::Convert( m_tUnits, nLeftUnits, fLeft );
			vResult = fLeft;
			vResult.SetUnits( m_tUnits );
		}
	}
	else
	{
		vResult = vLeft;
	}

	return vResult;
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

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorUnitConvert::Clone
		(
		void
		)
{
	return new CEquationOperatorUnitConvert( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
