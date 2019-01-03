/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWorkbench.cpp  --  brief description of what CApplicationGaugeWorkbench.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	26-Jan-2010			J.Griswold		(Reviewed by: xxxx)
		Add support for setting the window title
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change to call Size instead of SetSize on draw object
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Changes to support foreground/background (double-buffer) drawing.
	18-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Dispose of unnecessary functions
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CApplicationGaugeWorkbench.h"

#if defined( OS_MSWIN )
#include "CDictionary.h"
#include "CFactoryScreen.h"
#include "CFactoryConfiguration.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
/**--------------------------------------------------------------------+\

 * <summary>CApplicationGaugeWorkbench - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::CApplicationGaugeWorkbench
		(
		void
		)
		: CApplicationGauge()
{
}

/**--------------------------------------------------------------------+\

 * <summary>CApplicationGaugeWorkbench - copy constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::CApplicationGaugeWorkbench
		(
		ConstCApplicationGaugeWorkbenchRef	r
		)
		: CApplicationGauge( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/**--------------------------------------------------------------------+\

 * <summary>~CApplicationGaugeWorkbench - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::~CApplicationGaugeWorkbench
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/**---------------------------------------------------------------------+\

 * <summary>operator= - assignment operator</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbenchRef
		CApplicationGaugeWorkbench::operator=
		(
		ConstCApplicationGaugeWorkbenchRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/**--------------------------------------------------------------------+\

 * <summary>DrawWin - return pointer to windows specific draw object</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
CDrawWinPtr
		CApplicationGaugeWorkbench::DrawWin
		(
		void
		)
{
	return CDrawWinPtr( Draw() );
}


/**--------------------------------------------------------------------+\

 * <summary>SetCView - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  26-Jun-2010

\+---------------------------------------------------------------------*/
void	CApplicationGaugeWorkbench::SetCView
		(
		CView *p
		)
{
	m_pCView = p;
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


/**--------------------------------------------------------------------+\

 * <summary>OnDraw - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  04-Dec-2009

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::OnDraw
		(
		void
		)
{
	long	w = 0;
	long	h = 0;

	if ( m_pScreen )
		m_pScreen->GetSize( 0, w, h );
	if ( m_pDraw )
	{
		CDrawWinPtr	pDraw = DrawWin();

		pDraw->Size( w, h );
	}

	return CApplicationGauge::OnDraw();
}


/**--------------------------------------------------------------------+\

 * <summary>WindowTitle - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  26-Jun-2010

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::WindowTitle
		(
		ConstCCharDescriptorRef rChar
		)
{
	char	s[128];
	rChar.CopyTo( s, sizeof(s) );

	::SetWindowTextA( m_pCView->GetParentFrame()->GetSafeHwnd(), s );

	//m_pCView->SetWindowText( s );
	return true;
}


/**--------------------------------------------------------------------+\

 * <summary>MakeDraw - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
VDrawPtr
		CApplicationGaugeWorkbench::MakeDraw
		(
		void
		)
{
	CDrawWinWorkbenchPtr pDraw = new CDrawWinWorkbench;
	if ( pDraw )
	{
		pDraw->BackgroundColor( CColor::ColorFromName( "background" ) );
		pDraw->SetApplication( this );
	}
	return pDraw;
}


/**--------------------------------------------------------------------+\

 * <summary>MakeConfiguration - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  27-Aug-2010

\+---------------------------------------------------------------------*/
VConfigurationPtr
		CApplicationGaugeWorkbench::MakeConfiguration
		(
		void
		)
{
	CCharString	sName( "configurationWB" );
	CFactoryConfiguration	factory;
	factory.SetRelativePath( "dictionary" );
	VConfigurationPtr	pConfig = factory.Make( sName );

	return pConfig;
}





}}



#endif	//	OS_MSWIN


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  05-Aug-2009

\+---------------------------------------------------------------------*/
