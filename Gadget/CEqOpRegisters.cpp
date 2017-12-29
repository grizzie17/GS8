/*---------------------------------------------------------------------+\
|
|	CEqOpRegisters.cpp  --  brief description of what CEqOpRegisters.cpp is for
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
	20-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpRegisters.h"
#include "CDictionaryMemory.h"
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

 * CEquationOperatorRegisters - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisters::CEquationOperatorRegisters
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRegisters - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisters::CEquationOperatorRegisters
		(
		ConstCEquationOperatorRegistersRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRegisters - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisters::~CEquationOperatorRegisters
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
CEquationOperatorRegistersRef
		CEquationOperatorRegisters::operator=
		(
		ConstCEquationOperatorRegistersRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRegisters::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CDictionaryMemory	tMemoryDictionary( pDict );
	return m_pOperand->GetValue( &tMemoryDictionary );
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
		CEquationOperatorRegisters::Clone
		(
		void
		)
{
	return new CEquationOperatorRegisters( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

