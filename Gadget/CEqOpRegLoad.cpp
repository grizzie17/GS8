/*---------------------------------------------------------------------+\
|
|	CEqOpRegLoad.cpp  --  brief description of what CEqOpRegLoad.cpp is for
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
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Allow the memory dictionary to manage the number of registers
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
#include "CEqOpRegLoad.h"
#include "CDictionaryMemory.h"
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

 * CEquationRegisterLoad - constructor

\+---------------------------------------------------------------------*/
CEquationRegisterLoad::CEquationRegisterLoad
		(
		void
		)
		: VEquation(),
		m_nRegister( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CEquationRegisterLoad - copy constructor

\+---------------------------------------------------------------------*/
CEquationRegisterLoad::CEquationRegisterLoad
		(
		ConstCEquationRegisterLoadRef	r
		)
		: VEquation( r ),
		m_nRegister( r.m_nRegister )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CEquationRegisterLoad - destructor

\+---------------------------------------------------------------------*/
CEquationRegisterLoad::~CEquationRegisterLoad
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
CEquationRegisterLoadRef
		CEquationRegisterLoad::operator=
		(
		ConstCEquationRegisterLoadRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetRegister -

\+---------------------------------------------------------------------*/
void	CEquationRegisterLoad::SetRegister
		(
		int n
		)
{
	m_nRegister = n;
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
		CEquationRegisterLoad::GetValue
		(
		VDictionaryPtr pDict
		)
{
	//	The memory dictionary handles out-of-range issues
	CDictionaryMemoryPtr	pMem = CDictionaryMemoryPtr( pDict );
	return pMem->Recall( m_nRegister );
}


/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationRegisterLoad::Clone
		(
		void
		)
{
	return new CEquationRegisterLoad( *this );
}





}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
