/*---------------------------------------------------------------------+\
|
|	CWinCEDlg.h  --  brief description of what CWinCEDlg.h is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	17-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CWinCEDlg
#define _H_CWinCEDlg
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/

#include "VPostCalculate.h"

#include "TPointer.h"
#include "TComPointer.h"
#include "CApplicationGaugeWorkbenchWin.h"
#include "CKeyProcessorWin.h"
#include "CMouseProcessorWin.h"
#include "CMouseProcessorWB.h"
#include "CCommandProcessorWorkbench.h"
#include "CFunctionProcessorForPlugins.h"
#include "CPluginLibrary.h"
#include "CTaskManager.h"
#include "CServiceManager.h"



namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/
typedef class CWinCEDlg*		CWinCEDlgPtr;
typedef class CWinCEDlg&		CWinCEDlgRef;
typedef const class CWinCEDlg&	ConstCWinCEDlgRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CWinCEDlg : public VPostCalculate
{
//	class lifecycle  ----------------------------------------------------
public:
			CWinCEDlg();
	virtual	~CWinCEDlg();

private:
			CWinCEDlg( ConstCWinCEDlgRef r );	// copy constructor
	ConstCWinCEDlgRef
			operator=( ConstCWinCEDlgRef r );	// assignment

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void	Show( void );
	void	Invalidate( void );

	bool	InitializeDialog
			(
			HINSTANCE	hInstance,
			LPCTSTR		szWindowClass
			);


protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

	static LRESULT CALLBACK WndProcGlue(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void LazySetup( HWND hWnd, WPARAM wParam, LPARAM lParam );

	void OnInitDialog( HWND hWnd, WPARAM wParam, LPARAM lParam );
	void OnCreate( HWND hWnd, WPARAM wParam, LPARAM lParam );
	UINT StartTimer (UINT TimerDuration);  // Start the Timer
	BOOL StopTimer (UINT TimerVal);           // Stop the Timer
	void OnTimer( UINT nIDEvent );

	void OnPaint();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnLButtonDown(UINT nFlags, int x, int y);
	void OnLButtonUp(UINT nFlags, int x, int y);
	void OnRButtonDown(UINT nFlags, int x, int y);
	void OnMouseMove(UINT nFlags, int x, int y);
	void OnMouseLeave();
	void OnSize(UINT nType, int cx, int cy);
	void OnFullscreenmode();
	void OnClose();
	void OnDestroy();
	LRESULT OnCalculateNeeded( WPARAM notused1, LPARAM notused2 );

	UINT RemapBezelKey( UINT nChar );

//	protected data  -----------------------------------------------------

	HWND	m_hwnd;
	HDC		m_dc;




	Yogi::Core::TPointer<CApplicationGaugeWorkbenchWin>
									m_pApplicationGauge;
	Yogi::Core::TPointer<CKeyProcessorWin>		m_pKeyProcessor;
	Yogi::Core::TPointer<VMouseProcessorWin>	m_pMouseProcessor;
	//bool							m_bSampleLoader;
	Yogi::Core::TPointer<CCommandProcessorWorkbench>
									m_pCommandProcessor;
	Yogi::Core::TPointer<CFunctionProcessorForPlugins>
									m_pFunctionProcessor;
	Yogi::Core::TPointer<CTaskManager>			m_pTaskManager;
	Yogi::Core::TPointer<CServiceManager>		m_pServiceManager;

	bool					m_bRemapBezelKeys;
	bool					m_bFullScreen;
	COLORREF				m_nColorBackground;
	COLORREF				m_nColorText;

	UINT					m_nTimerID;
	UINT					m_nTimerValue;	// milliseconds
	UINT					m_nTimerSimulatedDataID;	// simulate data
	UINT					m_nTimerSimulatedDataValue;
	UINT					m_nTimerCheckStaleID;
	UINT					m_nTimerCheckStaleValue;

private:
//	private types  ------------------------------------------------------

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VPostCalculate
public:
	virtual void	PostCalculateNeeded( void );

	virtual void	SetWindowTitle( const char* sName );


};

/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/

}}


#endif /* _H_CWinCEDlg */
