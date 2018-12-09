/*---------------------------------------------------------------------+\
|
|	gauges.h  --  header file for view class for the GaugeViewOpenGL
|
|	Purpose:
|	File Custodian:		R.Hosea
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
	25-Sep-2009			R.Hosea		(Reviewed by: M.Rose)
		Added mouse/key processor functions

\+---------------------------------------------------------------------*/
#ifndef _GAUGE_VIEW_OPENGL_MAIN_
#define _GAUGE_VIEW_OPENGL_MAIN_

#ifndef UINT
#define UINT unsigned int
#endif


#include "TPointer.h"
#include "CApplicationGaugeWorkbench.h"
#include "CKeyProcessorOpenGL.h"
#include "CMouseProcessorWin.h"
#include "CCommandProcessorWorkbench.h"
#include "CFunctionProcessorForPlugins.h"
#include "CXMLSampleLoader.h"
#include "CVehicleDataLoader.h"
#include "CVehicleDataReader.h"
#include "CServiceManager.h"

using namespace Yogi::Gadget;

class GaugeViewOpenGL
{
  public:
    GaugeViewOpenGL(int width, int height);
    virtual ~GaugeViewOpenGL();
	bool Calculate();
	bool CalculateNow();
	bool StaleData();
    void Render();
    void OnLButtonUp(UINT nFlags, int x, int y);
    void OnLButtonDown(UINT nFlags, int x, int y);
    void OnMouseMove(UINT nFlags, int x, int y);
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    bool Size(int x, int y);

	//int SendImageFile(char *filename, int socketFd);
    //static int SendMulticastCommand(int command);
	//static void SocketHandler(int *socketFd );

  private:

	TPointer<CApplicationGaugeWorkbench>	m_pApplicationGauge;
	TPointer<CKeyProcessorOpenGL>			m_pKeyProcessor;
	TPointer<CMouseProcessorWin>			m_pMouseProcessor;
	TPointer<CCommandProcessorWorkbench>	m_pCommandProcessor;
	TPointer<CFunctionProcessorForPlugins>	m_pFunctionProcessor;
	//TPointer<CXMLSampleLoader>		m_pSampleLoaderXML;
	//TPointer<CVehicleDataLoader>		m_pVehicleData;
	//TPointer<CVehicleDataReader>		m_pVehicleDataXML;

	TPointer<CServiceManager>			m_pServiceManager;

	int m_nSocketFd;

	bool m_bFirstRender;
	bool m_bSampleLoader;
	bool	m_bRemapBezelKeys;

	//TODO: implement use of these values (copied from WIN32 implementation)
	int m_nTimerValue;
	int m_nTimerSimulatedDataValue;
	int m_nTimerCheckStaleValue;
};


#endif // _GAUGE_VIEW_OPENGL_MAIN_
