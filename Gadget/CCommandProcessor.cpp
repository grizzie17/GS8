/*---------------------------------------------------------------------+\
|
|	CCommandProcessor.cpp  --  brief description of what CCommandProcessor.cpp is for
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
    22-Mar-2010         P.Hogan         (Reviewed by: M.Rose)
        Fix Omniscape "no video" bug
	25-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Added video layouts to Initialize
	18-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Changed hierarchy to make this class a reasonable base class
		for Command Processors
	24-Dec-2009			R.Hosea			(Reviewed by: J.Griswold)
		Fixed Linux compile errors
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for the new "Constants" dictionary page
	11-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add entries for the side-rear cameras
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add command to toggle which VehicleData XML processor
		that we are going to use.
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add access to the Reload function on the application
	31-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Correct spelling of "Camera Right-Forward Color"
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CCommandProcessor.h"

#include "CColor.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
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

 * CCommandProcessor - constructor

\+---------------------------------------------------------------------*/
CCommandProcessor::CCommandProcessor
		(
		void
		)
		: m_pApplication( 0 )
		, m_pPageData( 0 )
		, m_pPageConstants( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CCommandProcessor - destructor

\+---------------------------------------------------------------------*/
CCommandProcessor::~CCommandProcessor
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CCommandProcessor::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;
	m_pPageData = p->DictPageData();
	m_pPageConstants = p->DictPageConstants();
}


/*---------------------------------------------------------------------+\

 * SetLoaderControl -

\+---------------------------------------------------------------------*/
//void	CCommandProcessor::SetLoaderControl
//		(
//		bool*	pLoaderControl
//		)
//{
//	m_pLoaderControl = pLoaderControl;
//}


/*---------------------------------------------------------------------+\

 * InitializeFunctions -

\+---------------------------------------------------------------------*/
void	CCommandProcessor::InitializeFunctions
		(
		void
		)
{
	VDictionaryPagePtr	pFunc = m_pApplication->DictPageCommands();
	if ( pFunc )
	{
		VDictionaryPtr	pDict = m_pApplication->Dictionary();
		CVariantData	v;



		v = "test";
		pFunc->AddEntry( "Reload Screens", v );
		m_cReloadScreens = pDict->LocateEntry( "C:Reload Screens" );


		v = 0L;
		pFunc->AddEntry( "Dump Dictionary", v );
		m_cDumpDictionary = pDict->LocateEntry( "C:Dump Dictionary" );

		v = false;
		pFunc->AddEntry( "Blackout", v );
		m_cBlackout = pDict->LocateEntry( "C:Blackout" );

		m_pPageData->AddEntry( "Blackout", v );
		m_nBlackout = m_pPageData->LocateEntry( "Blackout" );


		CColor c;
		c = CColor::ErrorColor();
		//c = CColor::ColorFromName( "background" );
		v = c;
		pFunc->AddEntry( "Background Color", v );
		m_cBackgroundColor = pDict->LocateEntry( "C:Background Color" );


		v = "*";
		pFunc->AddEntry( "Window Title", v );
		m_cWindowTitle = pDict->LocateEntry( "C:Window Title" );




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

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CCommandProcessor::ProcessRequest
		(
		VDictionary::Selector sel,
		ConstCVariantDataRef vDataRef
		)
{
	CVariantData vData = vDataRef;
	bool	bResult = true;

	if ( sel == m_cReloadScreens )
	{
		m_pApplication->ReloadScreen();
	}
	else if ( sel == m_cBlackout )
	{
		bool	b = vData;
		vData = b;	// force to be bool
		m_pApplication->Blackout( b );
		m_pPageData->UpdateEntry( (unsigned long)m_nBlackout, vData );
	}
	else if ( sel == m_cBackgroundColor )
	{
		CColor		c = vData;
		m_pApplication->BackgroundColor( c );
	}
	else if ( sel == m_cWindowTitle )
	{
		CCharString	s = vData;
		m_pApplication->WindowTitle( s );
	}
	else if ( sel == m_cDumpDictionary )
	{
		m_pApplication->DumpDictionary();
	}
	else
	{
		bResult = false;
	}
	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
