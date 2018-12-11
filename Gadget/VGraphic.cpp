/*---------------------------------------------------------------------+\
|
|	VGraphic.cpp  --  brief description of what VGraphic.cpp is for
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	30-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VGraphic.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * VGraphic - constructor

\+---------------------------------------------------------------------*/
VGraphic::VGraphic
		(
		void
		)
		: VOwnership()
		, m_pStyle( 0 )
{
}

/*---------------------------------------------------------------------+\

 * VGraphic - copy constructor

\+---------------------------------------------------------------------*/
VGraphic::VGraphic
		(
		ConstVGraphicRef	r
		)
		: VOwnership( r )
		, m_pStyle( 0 )
{
	m_pStyle = new CStyle( r.m_pStyle );
}

/*---------------------------------------------------------------------+\

 * ~VGraphic - destructor

\+---------------------------------------------------------------------*/
VGraphic::~VGraphic
		(
		void
		)
{
	if ( m_pStyle )
		delete m_pStyle;
	m_pStyle = 0;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
VGraphicRef
		VGraphic::operator=
		(
		ConstVGraphicRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetStyle -

\+---------------------------------------------------------------------*/
void	VGraphic::SetStyle
		(
		CStylePtr pStyle
		)
{
	if ( m_pStyle )
		delete m_pStyle;
	m_pStyle = pStyle;
}


/*---------------------------------------------------------------------+\

 * Style -

\+---------------------------------------------------------------------*/
CStylePtr
		VGraphic::Style
		(
		void
		)
{
	if ( ! m_pStyle )
		m_pStyle = new CStyle;
	return m_pStyle;
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
int		VGraphic::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int		nResult = VRDR_CALCULATE_NONE;
	if ( m_pStyle )
		nResult |= m_pStyle->Calculate( pDict );
	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	VGraphic::PreRender
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
bool	VGraphic::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = true;
	if ( m_pStyle )
		bResult = m_pStyle->Render( pDict, pDraw );
	return bResult;
}


/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	VGraphic::GetSize
		(
		VDictionaryPtr	,
		long&			,
		long&
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	VGraphic::IsDisplayed
		(
		VDictionaryPtr
		)
{
	return true;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
