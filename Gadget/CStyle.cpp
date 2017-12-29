/*---------------------------------------------------------------------+\
|
|	CStyle.cpp  --  brief description of what CStyle.cpp is for
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
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	17-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CStyle.h"
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

 * CStyle - constructor

\+---------------------------------------------------------------------*/
CStyle::CStyle
		(
		void
		)
		: VRenderable(),
		m_tLineColor(),
		m_tLineWidth(),
		m_tFillColor(),
		m_tHaloColor(),
		m_eNightColor( VDraw::C_NORMAL )
{
	CColor	c;
	CVariantData	v;
	c.SetNonColor( true );
	v = c;
	m_tLineColor.SetValue( v );
	m_tFillColor.SetValue( v );
	m_tHaloColor.SetValue( v );
}

/*---------------------------------------------------------------------+\

 * CStyle - copy constructor

\+---------------------------------------------------------------------*/
CStyle::CStyle
		(
		ConstCStyleRef	r
		)
		: VRenderable( r ),
		m_tLineColor(),
		m_tLineWidth(),
		m_tFillColor(),
		m_tHaloColor(),
		m_eNightColor( r.m_eNightColor )
{
	m_tLineColor = r.m_tLineColor;
	m_tLineWidth = r.m_tLineWidth;
	m_tFillColor = r.m_tFillColor;
	m_tHaloColor = r.m_tHaloColor;
}

/*---------------------------------------------------------------------+\

 * CStyle - copy constructor

\+---------------------------------------------------------------------*/
CStyle::CStyle
		(
		CStylePtr p
		)
		: VRenderable(),
		m_tLineColor(),
		m_tLineWidth(),
		m_tFillColor(),
		m_tHaloColor(),
		m_eNightColor( p->m_eNightColor )
{
	m_tLineColor = p->m_tLineColor;
	m_tLineWidth = p->m_tLineWidth;
	m_tFillColor = p->m_tFillColor;
	m_tHaloColor = p->m_tHaloColor;
}

/*---------------------------------------------------------------------+\

 * ~CStyle - destructor

\+---------------------------------------------------------------------*/
CStyle::~CStyle
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
CStyleRef
		CStyle::operator=
		(
		ConstCStyleRef	r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	VRenderable::operator=( r );
	m_tLineColor = r.m_tLineColor;
	m_tLineWidth = r.m_tLineWidth;
	m_tFillColor = r.m_tFillColor;
	m_tHaloColor = r.m_tHaloColor;
	m_eNightColor = r.m_eNightColor;
	return *this;
}

/*---------------------------------------------------------------------+\

 * SetLineColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetLineColor
		(
		ConstCColorRef r
		)
{
	CVariantData	c;
	c = r;
	m_tLineColor.SetValue( c );
}

/*---------------------------------------------------------------------+\

 * SetLineColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetLineColor
		(
		VEquationPtr p
		)
{
	m_tLineColor.SetEquation( p );
}


/*---------------------------------------------------------------------+\

 * SetLineWidth -

\+---------------------------------------------------------------------*/
void	CStyle::SetLineWidth
		(
		float f
		)
{
	CVariantData	v = f;
	m_tLineWidth.SetValue( v );
}

/*---------------------------------------------------------------------+\

 * SetLineWidth -

\+---------------------------------------------------------------------*/
void	CStyle::SetLineWidth
		(
		VEquationPtr p
		)
{
	m_tLineWidth.SetEquation( p );
}

/*---------------------------------------------------------------------+\

 * SetFillColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetFillColor
		(
		ConstCColorRef r
		)
{
	CVariantData	c;
	c = r;
	m_tFillColor.SetValue( c );
}

/*---------------------------------------------------------------------+\

 * SetFillColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetFillColor
		(
		VEquationPtr p
		)
{
	m_tFillColor.SetEquation( p );
}


/*---------------------------------------------------------------------+\

 * SetHaloColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetHaloColor
		(
		ConstCColorRef r
		)
{
	CVariantData	c;
	c = r;
	m_tHaloColor.SetValue( c );
}

/*---------------------------------------------------------------------+\

 * SetHaloColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetHaloColor
		(
		VEquationPtr p
		)
{
	m_tHaloColor.SetEquation( p );
}


/*---------------------------------------------------------------------+\

 * SetNightColor -

\+---------------------------------------------------------------------*/
void	CStyle::SetNightColor
		(
		VDraw::ENightColorModes	eMode
		)
{
	m_eNightColor = eMode;
}


/*---------------------------------------------------------------------+\

 * GetLineColor -

\+---------------------------------------------------------------------*/
CColor	CStyle::GetLineColor
		(
		void
		)
{
	return m_tLineColor.GetCachedValue();
}

/*---------------------------------------------------------------------+\

 * GetLineWidth -

\+---------------------------------------------------------------------*/
GFLOAT	CStyle::GetLineWidth
		(
		void
		)
{
	return m_tLineWidth.GetCachedValue();
}

/*---------------------------------------------------------------------+\

 * GetFillColor -

\+---------------------------------------------------------------------*/
CColor	CStyle::GetFillColor
		(
		void
		)
{
	return m_tFillColor.GetCachedValue();
}


/*---------------------------------------------------------------------+\

 * GetHaloColor -

\+---------------------------------------------------------------------*/
CColor	CStyle::GetHaloColor
		(
		void
		)
{
	return m_tHaloColor.GetCachedValue();
}


/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CStyle::LineColor
		(
		void
		)
{
	return &m_tLineColor;
}


/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CStyle::LineWidth
		(
		void
		)
{
	return &m_tLineWidth;
}


/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CStyle::FillColor
		(
		void
		)
{
	return &m_tFillColor;
}

/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CStyle::HaloColor
		(
		void
		)
{
	return &m_tHaloColor;
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
int		CStyle::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VRDR_CALCULATE_NONE;
	if ( m_tLineColor.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tLineWidth.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tFillColor.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tHaloColor.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}


bool	CStyle::Layout
		(
		VDictionaryPtr //pDict
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CStyle::PreRender
		(
		VDictionaryPtr ,
		VDrawQueuePtr
		)
{
	// do nothing
	return true;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CStyle::Render
		(
		VDictionaryPtr ,	// unused argument
		VDrawPtr pDraw
		)
{
	float	fWidth = GetLineWidth();
	CColor	tColor = GetLineColor();

	pDraw->LineWidth( short(fWidth) );
	pDraw->LineColor( tColor );
	tColor = GetFillColor();
	pDraw->FillColor( tColor );
	tColor = GetHaloColor();
	pDraw->HaloColor( tColor );
	pDraw->NightColor( m_eNightColor );
	return true;
}


/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	CStyle::GetSize
		(
		VDictionaryPtr,
		long& ,	//rnWidth,
		long&	//rnHeight
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	CStyle::IsDisplayed
		(
		VDictionaryPtr
		)
{
	return true;
}


/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	CStyle::ProcessEvent
		(
		VDictionaryPtr			,
		VDictionary::Selector
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CStyle::ProcessMouse
		(
		VDictionaryPtr		,
		CMouseLocatePtr
		)
{
	return false;
}



NAMESPACE_GADGET_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

