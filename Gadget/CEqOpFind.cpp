/*---------------------------------------------------------------------+\
|
|	CEqOpFind.cpp  --  Select from list of items
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
	23-Oct-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpFind.h"
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

 * CEquationOperatorFind - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorFind::CEquationOperatorFind
		(
		void
		)
		: VEquationOperatorUnary(),
		m_aItems()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorFind - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorFind::CEquationOperatorFind
		(
		ConstCEquationOperatorFindRef	r
		)
		: VEquationOperatorUnary( r ),
		m_aItems()
{
	size_t			n = r.m_aItems.Length();
	size_t			i;
	//p;
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
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorFind - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorFind::~CEquationOperatorFind
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
CEquationOperatorFindRef
		CEquationOperatorFind::operator=
		(
		ConstCEquationOperatorFindRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * AppendItem -

\+---------------------------------------------------------------------*/
void	CEquationOperatorFind::AppendItem
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
		CEquationOperatorFind::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult = -1L;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );
	CVariantData	vTemp;

	VEquationPtr*	p = m_aItems.PointArray();
	if ( p )
	{
		long	n = 0;
		VEquationPtr*	pEnd = p + m_aItems.Length();
		while ( p < pEnd )
		{
			if ( *p )
			{
				vTemp = (*p)->GetValue( pDict );
				if ( vTemp == vOperand )
				{
					vResult = n;
					break;
				}
			}
			++p;
			++n;
		}
	}

	return vResult;
}

/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorFind::Clone
		(
		void
		)
{
	return new CEquationOperatorFind( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

