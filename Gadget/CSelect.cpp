/*---------------------------------------------------------------------+\
|
|	CSelect.cpp  --  brief description of what CSelect.cpp is for
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
	11-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix "Calculate" since it was not correctly identifying
		that something had changed.
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Also fix a bug in Calculate that caused it to always identify
		the object as dirty
	19-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that if we change which case that we are using
		based upon the calculate that we return true from the calculate.
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Don't fail in Render just because no selections were made
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	27-Aug-2009			J.Griswold
		React to change for Case tag that allows an Expression instead
		of just an ExpressionResult.
	14-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CSelect.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN

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

 * CSelect - constructor

\+---------------------------------------------------------------------*/
CSelect::CSelect
		(
		void
		)
		: VElement(),
		m_tSelect(),
		m_pCase( 0 ),
		m_aList(),
		m_pCaseElse( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CSelect - copy constructor

\+---------------------------------------------------------------------*/
CSelect::CSelect
		(
		ConstCSelectRef	r
		)
		: VElement( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CSelect - destructor

\+---------------------------------------------------------------------*/
CSelect::~CSelect
		(
		void
		)
{
	CSelectCasePtr*	p = m_aList.PointArray();
	if ( p )
	{
		CSelectCasePtr*	pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
				delete *p;
			++p;
		}
	}
	if ( m_pCaseElse )
		delete m_pCaseElse;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CSelectRef
		CSelect::operator=
		(
		ConstCSelectRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetEquation -

\+---------------------------------------------------------------------*/
void	CSelect::SetEquation
		(
		VEquationPtr pEq
		)
{
	m_tSelect.SetEquation( pEq );
}

/*---------------------------------------------------------------------+\

 * AddCase -

\+---------------------------------------------------------------------*/
bool	CSelect::AddCase
		(
		CSelectCasePtr pCase
		)
{
	index_t	n = m_aList.AppendData( &pCase );
	return n < 0 ? false : true;
}

/*---------------------------------------------------------------------+\

 * SetCaseElse -

\+---------------------------------------------------------------------*/
bool	CSelect::SetCaseElse
		(
		CSelectCasePtr pCase
		)
{
	if ( m_pCaseElse )
		delete m_pCaseElse;
	m_pCaseElse = pCase;
	return true;
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

 * Calculate -

\+---------------------------------------------------------------------*/
int		CSelect::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int		nResult = VRDR_CALCULATE_NONE;

	if ( m_tSelect.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;

	CVariantData	v;
	CVariantData	vc;
	v = m_tSelect.GetCachedValue();

	CSelectCasePtr	pOrigCase = m_pCase;
	m_pCase = 0;

	CSelectCasePtr*	p;
	CSelectCasePtr*	pEnd;
	p = m_aList.PointArray();
	if ( p )
	{
		pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
			{
				nResult |= (*p)->CalculateCase( pDict );
			}
			++p;
		}
	}

	p = m_aList.PointArray();
	if ( p )
	{
		CSelectCasePtr*	pEnd2 = p + m_aList.Length();
		while ( p < pEnd2 )
		{
			if ( *p )
			{
				vc = (*p)->GetValue( 0 );
				if ( v == vc )
				{
					nResult |= (*p)->Calculate( pDict );
					if ( pOrigCase != *p )
						nResult |= m_mChildrenContext
								? m_mChildrenContext
								: VRDR_CALCULATE_UNDETERMINED;
					m_pCase = *p;
					break;
				}

			}
			++p;
		}

		if ( ! m_pCase )
		{
			if ( m_pCaseElse )
			{
				nResult |= m_pCaseElse->Calculate( pDict );
				if ( pOrigCase != m_pCaseElse )
					nResult |= m_mChildrenContext
							? m_mChildrenContext
							: VRDR_CALCULATE_UNDETERMINED;
				m_pCase = m_pCaseElse;
			}
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CSelect::PreRender
		(
		VDictionaryPtr pDict,
		VDrawQueuePtr pQueue
		)
{
	bool	bResult = true;
	if ( m_pCase )
	{
		bResult = m_pCase->PreRender( pDict, pQueue );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CSelect::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = true;
	if ( m_pCase )
		bResult = m_pCase->Render( pDict, pDraw );
	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CSelect::GetChildContext
		(
		void
		)
{
	int		m = 0;
	CSelectCasePtr*	h = m_aList.PointArray();
	if ( h )
	{
		CSelectCasePtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	if ( m_pCaseElse )
	{
		m = m_pCaseElse->GetChildContext();
		IncludeContext( m );
	}
	return VElement::GetChildContext();
}





NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

