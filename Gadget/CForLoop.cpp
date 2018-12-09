/*---------------------------------------------------------------------+\
|
|	CForLoop.cpp  --  brief description of what CForLoop.cpp is for
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
		foreground/background data
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the initialization of the loop
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	12-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CForLoop.h"
#include "CDrawQueue.h"
#include "UMachine.h"
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

 * CForLoop - constructor

\+---------------------------------------------------------------------*/
CForLoop::CForLoop
		(
		void
		)
		: VElement(),
		m_tInit(),
		m_pTest( 0 ),
		m_pIncr( 0 ),
		m_aList()
{
}

/*---------------------------------------------------------------------+\

 * CForLoop - copy constructor

\+---------------------------------------------------------------------*/
CForLoop::CForLoop
		(
		ConstCForLoopRef	r
		)
		: VElement( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CForLoop - destructor

\+---------------------------------------------------------------------*/
CForLoop::~CForLoop
		(
		void
		)
{
	VRenderablePtr*	p = m_aList.PointArray();
	VRenderablePtr*	pEnd = p + m_aList.Length();

	while ( p < pEnd )
	{
		if ( *p )
			delete *p;
		++p;
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CForLoopRef
		CForLoop::operator=
		(
		ConstCForLoopRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetInitEquation -

\+---------------------------------------------------------------------*/
void	CForLoop::SetInitEquation
		(
		VEquationPtr pEq
		)
{
	m_tInit.SetEquation( pEq );
	//if ( m_pInit )
	//	delete m_pInit;
	//m_pInit = pEq;
}

/*---------------------------------------------------------------------+\

 * SetTestEquation -

\+---------------------------------------------------------------------*/
void	CForLoop::SetTestEquation
		(
		VEquationPtr pEq
		)
{
	if ( m_pTest )
		delete m_pTest;
	m_pTest = pEq;
}

/*---------------------------------------------------------------------+\

 * SetIncrEquation -

\+---------------------------------------------------------------------*/
void	CForLoop::SetIncrEquation
		(
		VEquationPtr pEq
		)
{
	if ( m_pIncr )
		delete m_pIncr;
	m_pIncr = pEq;
}

/*---------------------------------------------------------------------+\

 * AddRenderable -

\+---------------------------------------------------------------------*/
bool	CForLoop::AddRenderable
		(
		VRenderablePtr pComp
		)
{
	index_t	n = m_aList.AppendData( &pComp );
	return -1 < n ? true : false;
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
int		CForLoop::Calculate
		(
		VDictionaryPtr pDict
		)
{
	if ( m_tInit.Calculate( pDict ) )
		return VRDR_CALCULATE_UNDETERMINED;
	else
		return VRDR_CALCULATE_NONE;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CForLoop::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	return pQueue->AddGraphic( this );
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CForLoop::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool			bResult = true;
	size_t			n = m_aList.Length();
	if ( 0 < n )
	{
		if ( m_pTest  &&  m_pIncr )
		{
			VRenderablePtr*	pBase = m_aList.PointArray();
			VRenderablePtr*	pEnd = pBase + n;
			VRenderablePtr*	p = pBase;
			CVariantData	v;
			bool			bLoop = false;

			m_tInit.Calculate( pDict );
			v = m_tInit.GetValue( pDict );
			forever_loop		// loop forever
			{
				v = m_pTest->GetValue( pDict );
				bLoop = v;
				if ( ! bLoop )
					break;

				p = pBase;
				while ( p < pEnd )
				{
					if ( *p )
						(*p)->Calculate( pDict );
					++p;
				}

				CDrawQueue		tQueue;
				p = pBase;
				while ( p < pEnd )
				{
					if ( *p )
						bResult = (*p)->PreRender( pDict, &tQueue );
					++p;
				}
				if ( bResult )
					bResult = tQueue.RenderGraphics( pDict, pDraw );


				v = m_pIncr->GetValue( pDict );
			}
		}
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CForLoop::GetChildContext
		(
		void
		)
{
	int		m = 0;
	VRenderablePtr*	h = m_aList.PointArray();
	if ( h )
	{
		VRenderablePtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	return VElement::GetChildContext();
}




}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
