/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeWorkbench.cpp  --  brief description of what CApplicationGaugeWorkbench.cpp is for
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

#if defined( OS_LINUX )
#include "GL/glut.h"

#include "CDictionary.h"
#include "CFactoryScreen.h"
#include "CFactoryConfiguration.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/



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

extern bool g_bCalculateNeeded;

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

 * CApplicationGaugeWorkbench - constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::CApplicationGaugeWorkbench
		(
		void
		)
		: CApplicationGauge()
{
}

/*---------------------------------------------------------------------+\

 * CApplicationGaugeWorkbench - copy constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeWorkbench::CApplicationGaugeWorkbench
		(
		ConstCApplicationGaugeWorkbenchRef	r
		)
		: CApplicationGauge( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CApplicationGaugeWorkbench - destructor

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

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

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

 * OnDraw -

\+---------------------------------------------------------------------*/
#if 0
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
		VDrawPtr	pDraw = Draw();

		pDraw->Size( w, h );
	}

	return CApplicationGauge::OnDraw();
}
#endif


/*---------------------------------------------------------------------+\

 * WindowTitle -

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::WindowTitle
		(
		ConstCCharDescriptorRef rChar
		)
{
	char	s[128];
	rChar.CopyTo( s, sizeof(s) );

	glutSetWindowTitle( s );

	return true;
}


/*---------------------------------------------------------------------+\

 * PostCalculateNeeded -

\+---------------------------------------------------------------------*/
bool	CApplicationGaugeWorkbench::PostCalculateNeeded
		(
		void
		)
{
	g_bCalculateNeeded = true;		// handled in idle_func
	return true;
}


/*---------------------------------------------------------------------+\

 * MakeDraw -

\+---------------------------------------------------------------------*/
VDrawPtr
		CApplicationGaugeWorkbench::MakeDraw
		(
		void
		)
{
	return inherited::MakeDraw();
//	CDrawLinuxDTWorkbenchPtr pDraw = new CDrawLinuxDTWorkbench;
//	if ( pDraw )
//	{
//		pDraw->BackgroundColor( CColor::ColorFromName( "background" ) );
//		pDraw->SetApplication( this );
//	}
//	return pDraw;
}


/*---------------------------------------------------------------------+\

 * MakeConfiguration -

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
	VConfigurationPtr	pConfig = factory.Make( sName.Pointer() );

	CCharString		sOS = OS_NAME;
	CVariantData	v = sOS;
	pConfig->AddEntry( "OS", v );

	return pConfig;
}





NAMESPACE_GADGET_END



#endif	//	OS_LINUX


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

