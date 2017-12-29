/*---------------------------------------------------------------------+\
|
|	CChoose.cpp  --  brief description of what CChoose.cpp is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data.
		There was also a bug in the Calculate function that caused
		it to always show as dirty.
	19-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that true is returned from Calculate if the chosen
		'When' changes.
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CChoose.h"
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

 * CChoose - constructor

\+---------------------------------------------------------------------*/
CChoose::CChoose
		(
		void
		)
		: VElement(),
		m_pWhen( 0 ),
		m_aList(),
		m_pOtherwise( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CChoose - copy constructor

\+---------------------------------------------------------------------*/
CChoose::CChoose
		(
		ConstCChooseRef	r
		)
		: VElement( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CChoose - destructor

\+---------------------------------------------------------------------*/
CChoose::~CChoose
		(
		void
		)
{
	CChooseWhenPtr*	p = m_aList.PointArray();
	if ( p )
	{
		CChooseWhenPtr*	pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
				delete *p;
			++p;
		}
	}
	if ( m_pOtherwise )
		delete m_pOtherwise;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CChooseRef
		CChoose::operator=
		(
		ConstCChooseRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * AddWhen -

\+---------------------------------------------------------------------*/
bool	CChoose::AddWhen
		(
		CChooseWhenPtr pWhen
		)
{
	index_t	n = m_aList.AppendData( &pWhen );
	return n < 0 ? false : true;
}

/*---------------------------------------------------------------------+\

 * SetOtherwise -

\+---------------------------------------------------------------------*/
bool	CChoose::SetOtherwise
		(
		CChooseWhenPtr pWhen
		)
{
	if ( m_pOtherwise )
		delete m_pOtherwise;
	m_pOtherwise = pWhen;
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
int		CChoose::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int				nResult = VRDR_CALCULATE_NONE;
	CVariantData	v;
	CVariantData	vc;
	bool			bTest = false;

	CChooseWhenPtr	pOrigWhen = m_pWhen;
	m_pWhen = 0;

	CChooseWhenPtr*	p;
	CChooseWhenPtr*	pEnd;
	p = m_aList.PointArray();
	if ( p )
	{
		pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
			{
				nResult |= (*p)->CalculateWhen( pDict );
			}
			++p;
		}
	}

	p = m_aList.PointArray();
	if ( p )
	{
		pEnd = p + m_aList.Length();
		while ( p < pEnd )
		{
			if ( *p )
			{
				vc = (*p)->GetValue( 0 );
				bTest = vc;
				if ( bTest )
				{
					nResult |= (*p)->Calculate( pDict );
					if ( pOrigWhen != *p )
						nResult |= m_mChildrenContext
								? m_mChildrenContext
								: VRDR_CALCULATE_UNDETERMINED;
					m_pWhen = *p;
					break;
				}

			}
			++p;
		}

		if ( ! m_pWhen )
		{
			if ( m_pOtherwise )
			{
				nResult |= m_pOtherwise->Calculate( pDict );
				if ( pOrigWhen != m_pOtherwise )
					nResult |= m_mChildrenContext
							? m_mChildrenContext
							: VRDR_CALCULATE_UNDETERMINED;
				m_pWhen = m_pOtherwise;
			}
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CChoose::PreRender
		(
		VDictionaryPtr pDict,
		VDrawQueuePtr pQueue
		)
{
	bool	bResult = true;
	if ( m_pWhen )
	{
		bResult = m_pWhen->PreRender( pDict, pQueue );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CChoose::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = true;
	if ( m_pWhen )
		bResult = m_pWhen->Render( pDict, pDraw );
	return bResult;
}



/*---------------------------------------------------------------------+\

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CChoose::GetChildContext
		(
		void
		)
{
	int		m = 0;
	CChooseWhenPtr*	h = m_aList.PointArray();
	if ( h )
	{
		CChooseWhenPtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	if ( m_pOtherwise )
	{
		m = m_pOtherwise->GetChildContext();
		IncludeContext( m );
	}
	return VElement::GetChildContext();
}




NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

