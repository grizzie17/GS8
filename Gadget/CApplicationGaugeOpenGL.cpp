/*---------------------------------------------------------------------+\
|
|	CApplicationGaugeOpenGL.cpp  --  brief description of what CApplicationGaugeOpenGL.cpp is for
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
    14-Dec-2009         R.Hosea        (Reviewed by: J.Griswold)
        Fixed gcc compile problem for omniscape
	20-Nov-2009			C. Cason		(Reviewed by: R.Hosea)
		Initial Revision - baselined from CApplicationGaugeVDDS.h
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CApplicationGaugeOpenGL.h"
#if defined( OS_MSWIN )

long	dummyApplicationGaugeOpenGL;	// dummy symbol to surpress 'no public symbols' message

#elif defined( OS_LINUX_BLUERING )	// brackets whole file
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
/*---------------------------------------------------------------------+\

 * CApplicationGaugeOpenGL - constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeOpenGL::CApplicationGaugeOpenGL
		(
		void
		)
		: CApplicationGauge()
{
}

/*---------------------------------------------------------------------+\

 * CApplicationGaugeOpenGL - copy constructor

\+---------------------------------------------------------------------*/
CApplicationGaugeOpenGL::CApplicationGaugeOpenGL
		(
		ConstCApplicationGaugeOpenGLRef	r
		)
		: CApplicationGauge( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CApplicationGaugeOpenGL - destructor

\+---------------------------------------------------------------------*/
CApplicationGaugeOpenGL::~CApplicationGaugeOpenGL
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
CApplicationGaugeOpenGLRef
		CApplicationGaugeOpenGL::operator=
		(
		ConstCApplicationGaugeOpenGLRef	r
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * DrawOpenGL -

\+---------------------------------------------------------------------*/

CDrawOpenGLPtr
CApplicationGaugeOpenGL::DrawOpenGL
		(
		void
		)
{
	return CDrawOpenGLPtr( Draw() );
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

 * MakeDraw -  Creates a vdds draw object

\+---------------------------------------------------------------------*/
VDrawPtr
		CApplicationGaugeOpenGL::MakeDraw
		(
		void
		)
{
	VDrawPtr pDraw = new CDrawOpenGL;
	if ( pDraw )
	{
		pDraw->BackgroundColor( CColor::ColorFromName( "black" ) );
	}
	return pDraw;
}

/*---------------------------------------------------------------------+\

 * MakeDictionary - Creates a dictionary object

\+---------------------------------------------------------------------*/
VDictionaryPageServerPtr
		CApplicationGaugeOpenGL::MakeDictionary
		(
		void
		)
{
	return CApplicationGauge::MakeDictionary();
}

/*---------------------------------------------------------------------+\

 * MakeScreen - Creates a screen object

\+---------------------------------------------------------------------*/
CScreenPtr
		CApplicationGaugeOpenGL::MakeScreen
		(
		void
		)
{
	return CApplicationGauge::MakeScreen();
}

/*---------------------------------------------------------------------+\

 * MakeConfiguration - Creates a configuration

\+---------------------------------------------------------------------*/
CConfigurationPtr
		CApplicationGaugeOpenGL::MakeConfiguration
		(
		void
		)
{
	CCharString	sName( "configuration" );
	CFactoryConfiguration	factory;
	factory.SetRelativePath("dictionary");
	CConfigurationPtr	pConfig = factory.Make( sName );

	return pConfig;
}
/*---------------------------------------------------------------------+\

 * SetPort - Sets port number for config

\+---------------------------------------------------------------------*/
void
	CApplicationGaugeOpenGL::SetPort
	(
	unsigned int port
	)
{
	m_port = port;
}

}}


#endif	// OS_LINUX_VDDS
