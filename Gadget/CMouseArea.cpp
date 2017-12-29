/*---------------------------------------------------------------------+\
|
|	CMouseArea.cpp  --  brief description of what CMouseArea.cpp is for
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
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseDown, MouseUp, and MouseMove
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetEvent that uses descriptor to send the name instead
		of null terminated string.
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CMouseArea.h"
#include "CEqConstant.h"
#include "CEqVariableAssign.h"
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

 * CMouseArea - constructor

\+---------------------------------------------------------------------*/
CMouseArea::CMouseArea
		(
		void
		)
		: m_fLeft( 0 ),
		m_fTop( 0 ),
		m_fRight( 0 ),
		m_fBottom( 0 ),
		m_pVisibility( 0 ),
		m_pEquation( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CMouseArea - copy constructor

\+---------------------------------------------------------------------*/
CMouseArea::CMouseArea
		(
		ConstCMouseAreaRef	r
		)
		: m_fLeft( r.m_fLeft ),
		m_fTop( r.m_fTop ),
		m_fRight( r.m_fRight ),
		m_fBottom( r.m_fBottom ),
		m_pVisibility( r.m_pVisibility ),
		m_pEquation( r.m_pEquation )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CMouseArea - destructor

\+---------------------------------------------------------------------*/
CMouseArea::~CMouseArea
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
CMouseAreaRef
		CMouseArea::operator=
		(
		ConstCMouseAreaRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetArea -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetArea
		(
		float	fLeft,
		float	fTop,
		float	fRight,
		float	fBottom
		)
{
	m_fLeft = fLeft;
	m_fTop = fTop;
	m_fRight = fRight;
	m_fBottom = fBottom;
}


/*---------------------------------------------------------------------+\

 * SetVisibility -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetVisibility
		(
		VEquationPtr	pEq
		)
{
	CVisiblePtr	pVis = new CVisible;
	pVis->SetEquation( pEq );
	SetVisibility( pVis );
}

/*---------------------------------------------------------------------+\

 * SetVisibility -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetVisibility
		(
		CVisiblePtr pVis
		)
{
	if ( m_pVisibility )
		delete m_pVisibility;
	m_pVisibility = pVis;
}

/*---------------------------------------------------------------------+\

 * SetEquation -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetEquation
		(
		VEquationPtr pEq
		)
{
	if ( m_pEquation )
		delete m_pEquation;
	m_pEquation = pEq;
}

/*---------------------------------------------------------------------+\

 * SetEvent -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetEvent
		(
		CCharDescriptorRef	rEvent
		)
{
	CEquationConstantPtr		pConst = new CEquationConstant;
	CEquationVariableAssignPtr	pVar = new CEquationVariableAssign;

	pConst->SetValue( CVariantData( GFLOAT_1 ) );
	pVar->SetOperand( pConst );
	pVar->SetVariableName( rEvent );

	SetEquation( pVar );
}


/*---------------------------------------------------------------------+\

 * SetClickType -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetClickType
		(
		CMouseLocate::E_TYPE	t
		)
{
	m_eClickType = t;
}


/*---------------------------------------------------------------------+\

 * SetEvent -

\+---------------------------------------------------------------------*/
void	CMouseArea::SetEvent
		(
		const char*	sEvent
		)
{
	CCharDescriptor	tName( sEvent );
	SetEvent( tName );
}


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
bool	CMouseArea::Calculate
		(
		VDictionaryPtr pDict
		)
{
	bool	bResult = false;
	if ( m_pVisibility )
	{
		if ( m_pVisibility->Calculate( pDict ) )
			bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CMouseArea::ProcessMouse
		(
		VDictionaryPtr	pDict,
		CMouseLocatePtr	pMouseLocate
		)
{
	bool	bResult = true;
	bool	bProcess = true;

	if ( m_eClickType == pMouseLocate->GetAction() )
	{
		if ( m_pVisibility )
			bProcess = m_pVisibility->IsDisplayed( pDict );
		if ( bProcess )
		{
			if ( pMouseLocate->Locate( m_fLeft, m_fTop, m_fRight, m_fBottom ) )
			{
				if ( m_pEquation )
				{
					CVariantData	vData = m_pEquation->GetValue( pDict );

					bResult = vData;	// do we allow the mouse point to bubble up
				}
			}
		}
	}
	return bResult;
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


NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

