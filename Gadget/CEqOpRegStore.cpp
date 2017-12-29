/*---------------------------------------------------------------------+\
|
|	CEqOpRegStore.cpp  --  brief description of what CEqOpRegStore.cpp is for
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
#include "CEqOpRegStore.h"
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

 * CEquationOperatorRegisterStore - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisterStore::CEquationOperatorRegisterStore
		(
		void
		)
		: VEquationOperatorUnary(),
		m_nRegister( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRegisterStore - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisterStore::CEquationOperatorRegisterStore
		(
		ConstCEquationOperatorRegisterStoreRef	r
		)
		: VEquationOperatorUnary( r ),
		m_nRegister( r.m_nRegister )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRegisterStore - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRegisterStore::~CEquationOperatorRegisterStore
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
CEquationOperatorRegisterStoreRef
		CEquationOperatorRegisterStore::operator=
		(
		ConstCEquationOperatorRegisterStoreRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetRegister -

\+---------------------------------------------------------------------*/
void	CEquationOperatorRegisterStore::SetRegister
		(
		int n
		)
{
	m_nRegister = n;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRegisterStore::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	CDictionaryMemoryPtr	pMem = CDictionaryMemoryPtr( pDict );

	pMem->Store( m_nRegister, vOperand );

	return vOperand;
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
		CEquationOperatorRegisterStore::Clone
		(
		void
		)
{
	return new CEquationOperatorRegisterStore( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

