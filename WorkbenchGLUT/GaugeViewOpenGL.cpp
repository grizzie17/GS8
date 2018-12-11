/*---------------------------------------------------------------------+\
|
|	GaugeViewOpenGL.cpp  --  view class for the GaugeViewOpenGL
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
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "GaugeViewOpenGL.h"

#include "VFunctionProcessor.h"

#include "GaugeApp.h"
#include "CVehicleDataReader.h"
#include "UKeys.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
//#define	LOCAL_PRINT( fmt, ... )

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

/*---------------------------------------------------------------------+\

 * GaugeViewOpenGL - constructor

\+---------------------------------------------------------------------*/
GaugeViewOpenGL::GaugeViewOpenGL(int width, int height) :
	m_pApplicationGauge(NULL),
	m_pKeyProcessor(NULL),
	m_pMouseProcessor(NULL),
	m_pCommandProcessor(NULL),
	m_pFunctionProcessor(NULL),
//	m_pSampleLoaderXML(NULL),
//	m_pVehicleDataXML(NULL),
	m_pServiceManager(),
	m_bFirstRender(true),
	m_bSampleLoader(false),
	m_bRemapBezelKeys(false)
{
	Yogi::Gadget::CApplicationGaugeWorkbenchPtr	pApp;
	pApp = new Yogi::Gadget::CApplicationGaugeWorkbench;
	if ( pApp )
	{
		ISupportsPtr	pIPluginLibrary = NEW_OBJECT( CPluginLibrary );

		pApp->RegisterCOMObject( "PluginLibrary", pIPluginLibrary );



		pApp->Initialize1();
		m_pApplicationGauge = pApp;


		//These timing values are obtained consistently with the WIN32
		//implementation of the Gauge package, but they are not used otherwise.
		long nFrequency;
		CVariantDataPtr pv;
//		Yogi::Common::CConfigurationPtr pConfig;
//		pConfig = (CConfigurationPtr) pApp->Configuration();
		VConfigurationPtr pConfig;
		pConfig = pApp->Configuration();
		if (pConfig)
		{
			pv = pConfig->GetEntry("Calculate Frequency");
			if (pv)
			{
				nFrequency = *pv;
				if (0 < nFrequency)
				{
					m_nTimerValue = 1000 / nFrequency;
					pApp->SetMaximumTimeElapsedToCalculate( m_nTimerValue );
				}
			}
			m_bRemapBezelKeys = pConfig->GetEntryAsBool( "Simulate Bezel Keys", false );

			pv = pConfig->GetEntry("Simulate Data Frequency");
			if (pv)
			{
				nFrequency = *pv;
				if (0 < nFrequency)
					m_nTimerSimulatedDataValue = 1000 / nFrequency;
			}

			pv = pConfig->GetEntry("Active Dictionary Check Stale");
			if (pv)
			{
				GFLOAT	f = GFLOAT_CAST(*pv);
				if (0.0f < f)
				{
					CUnitsOfMeasure u;
					u.SetUsingName((char*)"millisecond");
					f = pv->GetValueFloatAsUnits(u);
					m_nTimerCheckStaleValue = static_cast<long> (f);
				}
			}

			m_pServiceManager = new Yogi::Gadget::CServiceManager;
			if ( m_pServiceManager )
			{
				CCharString	sService = pConfig->GetEntryAsString("Service List","default");
				m_pServiceManager->SetApplication( pApp );
				m_pServiceManager->SetLibrary( pIPluginLibrary );
				m_pServiceManager->LoadServices(sService.Pointer());
				pApp->RegisterObject( "ServiceManager", m_pServiceManager );
			}

		}

		m_pCommandProcessor = new CCommandProcessorWorkbench;
		m_pCommandProcessor->SetApplication(pApp);
		pApp->SetCommandProcessor(m_pCommandProcessor);
		pApp->RegisterObject( "CommandProcessor", m_pCommandProcessor );
		m_pCommandProcessor->InitializeFunctions();

		m_pFunctionProcessor = new CFunctionProcessorForPlugins;
		m_pFunctionProcessor->SetApplication(pApp);
		pApp->SetFunctionProcessor(m_pFunctionProcessor);
		pApp->RegisterObject( "FunctionProcessor", m_pFunctionProcessor );
		m_pFunctionProcessor->InitializeFunctions();


		pApp->Initialize2();

		VDrawPtr pDrawWin = pApp->Draw();
		if ( pDrawWin )
		{
			pv = pConfig->GetEntry( "Background Color" );
			if ( pv )
			{
				CColor	clrBackground = *pv;
				pDrawWin->BackgroundColor( clrBackground );
			}
		}


		m_pKeyProcessor = new Yogi::Gadget::CKeyProcessorOpenGL;
		m_pKeyProcessor->SetApplication(pApp);

		m_pMouseProcessor = new Yogi::Gadget::CMouseProcessorWin;
		m_pMouseProcessor->SetApplication(pApp);

		m_pApplicationGauge->Size(width, height);
		m_pApplicationGauge->Calculate();

	}


}

/*---------------------------------------------------------------------+\

 * ~GaugeViewOpenGL - destructor

\+---------------------------------------------------------------------*/
GaugeViewOpenGL::~GaugeViewOpenGL()
{

  if(m_pApplicationGauge)
  {
    delete m_pApplicationGauge;
  }

}



/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
bool	GaugeViewOpenGL::Size
		(
		int x,
		int y
		)
{
	return m_pApplicationGauge->Size( x, y );
}

/*---------------------------------------------------------------------+\

 * OnLButtonUp -

\+---------------------------------------------------------------------*/
void	GaugeViewOpenGL::OnLButtonUp
		(
		UINT nFlags,
		int x,
		int y
		)
{
	m_pMouseProcessor->OnLButtonUp( nFlags, x, y );

}

/*---------------------------------------------------------------------+\

 * OnLButtonDown -

\+---------------------------------------------------------------------*/
void	GaugeViewOpenGL::OnLButtonDown
		(
		UINT nFlags,
		int x,
		int y
		)
{
	m_pMouseProcessor->OnLButtonDown( nFlags, x, y );
//		if ( m_pApplicationGauge->Calculate() )
//	{
//		m_pApplicationGauge->OnDraw();
//	}
}

/*---------------------------------------------------------------------+\

 * OnMouseMove -

\+---------------------------------------------------------------------*/
void	GaugeViewOpenGL::OnMouseMove
		(
		UINT nFlags,
		int x,
		int y
		)
{
	m_pMouseProcessor->OnMouseMove( nFlags, x, y );
}

/*---------------------------------------------------------------------+\

 * OnKeyDown -

\+---------------------------------------------------------------------*/
void	GaugeViewOpenGL::OnKeyDown
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	if ( m_bRemapBezelKeys )
	{
		if ( '1' <= nChar  &&  nChar <= '9' )
			nChar = nChar - '1' + UKEY_BEZEL1;
		else if ( '0' == nChar )
			nChar = nChar - '0' + UKEY_BEZEL10;
		else if ( VK_NUMPAD0 <= nChar  &&  nChar <= VK_NUMPAD9 )
			nChar = nChar - VK_NUMPAD0 + UKEY_BEZEL10;
	}
	m_pKeyProcessor->OnKeyDown( nChar, nRepCnt, nFlags );
}

/*---------------------------------------------------------------------+\

 * OnKeyUp -

\+---------------------------------------------------------------------*/
void	GaugeViewOpenGL::OnKeyUp
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	if ( m_bRemapBezelKeys )
	{
		if ( '1' <= nChar  &&  nChar <= '9' )
			nChar = nChar - '1' + UKEY_BEZEL1;
		else if ( '0' == nChar )
			nChar = nChar - '0' + UKEY_BEZEL10;
		else if ( VK_NUMPAD0 <= nChar  &&  nChar <= VK_NUMPAD9 )
			nChar = nChar - VK_NUMPAD0 + UKEY_BEZEL10;
	}
	m_pKeyProcessor->OnKeyUp( nChar, nRepCnt, nFlags );
}
/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
void GaugeViewOpenGL::Render()
{
	m_pApplicationGauge->OnDraw();
}

/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
bool	GaugeViewOpenGL::Calculate()
{
	if ( m_pApplicationGauge )
		return m_pApplicationGauge->Calculate();
	else
		return false;
}

/*---------------------------------------------------------------------+\

 * CalculateNow -

\+---------------------------------------------------------------------*/
bool	GaugeViewOpenGL::CalculateNow()
{
	if ( m_pApplicationGauge )
		return m_pApplicationGauge->CalculateNow();
	else
		return false;
}

/*---------------------------------------------------------------------+\

 * StaleData -

\+---------------------------------------------------------------------*/
bool	GaugeViewOpenGL::StaleData()
{
	if ( m_pApplicationGauge )
		return m_pApplicationGauge->StaleData();
	else
		return false;
}
