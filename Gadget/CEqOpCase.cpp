/*---------------------------------------------------------------------+\
|
|	CEqOpCase.cpp  --  Select from list of items
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
	24-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpCase.h"
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

 * CEquationOperatorCase - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorCase::CEquationOperatorCase
		(
		void
		)
		: VEquationOperatorUnary(),
		m_aItems()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorCase - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorCase::CEquationOperatorCase
		(
		ConstCEquationOperatorCaseRef	r
		)
		: VEquationOperatorUnary( r ),
		m_aItems()
{
	size_t			n = r.m_aItems.Length();
	size_t			i;
	//p = 0;
	for ( i = 0; i < n; ++i )
	{
		VEquationPtr*	h = r.m_aItems.PointArray( (index_t)i );
		if ( h )
		{
			VEquationPtr	p = *h;
			if ( p )
				AppendItem( p->Clone() );
		}
	}
	//VEquationPtr*	pr = r.m_aItems.PointArray();
	//if ( pr )
	//{
	//	VEquationPtr*	prEnd = pr + r.m_aItems.Length();
	//	while ( pr < prEnd )
	//	{
	//		if ( *pr )
	//			AppendItem( (*pr)->Clone() );
	//		++pr;
	//	}
	//}
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorCase - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorCase::~CEquationOperatorCase
		(
		void
		)
{
	VEquationPtr*	p = m_aItems.PointArray();
	if ( p )
	{
		VEquationPtr*	pEnd = p + m_aItems.Length();
		while ( p < pEnd )
		{
			if ( *p )
				delete *p;
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CEquationOperatorCaseRef
		CEquationOperatorCase::operator=
		(
		ConstCEquationOperatorCaseRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * AppendItem -

\+---------------------------------------------------------------------*/
void	CEquationOperatorCase::AppendItem
		(
		VEquationPtr	pItem
		)
{
	VEquationPtr*	p = m_aItems.AppendArray();
	if ( p )
	{
		*p = pItem;
	}
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
		CEquationOperatorCase::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	long	n = vOperand;
	if ( n < 0 )
		n = 0;
	long	t = long(m_aItems.Length());
	if ( t < n+1 )
		n = t - 1;

	VEquationPtr*	p = m_aItems.PointArray( n );
	if ( p )
		return (*p)->GetValue( pDict );
	else
		return CVariantData();
}

/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorCase::Clone
		(
		void
		)
{
	return new CEquationOperatorCase( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
