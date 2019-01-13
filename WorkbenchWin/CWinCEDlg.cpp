/*---------------------------------------------------------------------+\
|
|	CWinCEDlg.cpp  --  brief description of what CWinCEDlg.cpp is for
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
	17-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UOSIncludes.h"
#include <WinUser.h>

#include "CWinCEDlg.h"
#include "IDrawWin32.h"
#include "IDrawDebug.h"
#include "LogFile.h"
#include "resource.h"
/*---------------------------------------------------------------------+\
|
|	Local defines / constants
|
\+---------------------------------------------------------------------*/
#define IDT_TIMER_CALCULATE		(WM_USER + 200)
#define	IDT_TIMER_VEHICLEDATA	(WM_USER + 201)
#define	IDT_TIMER_CHECKSTALE	(WM_USER + 202)

#define DISPLAY_HEIGHT_PIXELS    640
#define DISPLAY_WIDTH_PIXELS     (DISPLAY_HEIGHT_PIXELS*16/9)
#define DISPLAY_BITS_PER_PIXEL   8


#if defined WS_OVERLAPPEDWINDOW
#	define XSTYLE	(WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_SIZEBOX)
#else
#	define XSTYLE	(WS_VISIBLE)
#endif

#if ! defined( CS_OWNDC )
#	define CS_OWNDC		0
#endif

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Local Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/
const INT UWM_CALCULATENEEDED = RegisterWindowMessage( TEXT("CALCULATENEEDED"));

/*---------------------------------------------------------------------+\
|
|	Public Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	 Code
||
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CWinCEDlg - constructor

\+---------------------------------------------------------------------*/
CWinCEDlg::CWinCEDlg
		(
		void
		)
		: m_hwnd( 0 )
		, m_dc( 0 )
		, m_pApplicationGauge()
		, m_pKeyProcessor()
		, m_pMouseProcessor()
		//, m_bSampleLoader()
		, m_pCommandProcessor()
		, m_pFunctionProcessor()
		, m_pTaskManager()
		, m_pServiceManager()

		, m_bRemapBezelKeys( false )
		, m_bFullScreen( true )
		, m_nColorBackground( CColor::BackgroundColor() )
		, m_nColorText( CColor::ColorFromName( "blue" ) )

		, m_nTimerID( IDT_TIMER_CALCULATE )
		, m_nTimerValue( 100 )
		, m_nTimerSimulatedDataID( IDT_TIMER_VEHICLEDATA )
		, m_nTimerSimulatedDataValue( 20 )
		, m_nTimerCheckStaleID( IDT_TIMER_CHECKSTALE )
		, m_nTimerCheckStaleValue( 1000 )
{
}



/*---------------------------------------------------------------------+\

 * CWinCEDlg - copy constructor

\+---------------------------------------------------------------------*/
//CWinCEDlg::CWinCEDlg
//		(
//		ConstCWinCEDlgRef	r
//		)
//		: inherited( r )
//{
//	// TODO: add instructions to copy data from "r" to "this"
//}

/*---------------------------------------------------------------------+\

 * ~CWinCEDlg - destructor

\+---------------------------------------------------------------------*/
CWinCEDlg::~CWinCEDlg
		(
		void
		)
{
	if ( m_nTimerID )
		::KillTimer( m_hwnd, m_nTimerID );
	if ( m_nTimerCheckStaleID )
		::KillTimer( m_hwnd, m_nTimerCheckStaleID );

	if ( m_pServiceManager )
		m_pServiceManager->StopServices();
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * Show -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::Show
		(
		void
		)
{
	::ShowWindow( m_hwnd, SW_SHOW );
	::UpdateWindow( m_hwnd );
}


/*---------------------------------------------------------------------+\

 * Invalidate -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::Invalidate
		(
		void
		)
{
	RECT	r;

	if ( ! m_pApplicationGauge->GetDirtyRectangle( &r.left, &r.top, &r.right, &r.bottom ) )
		::GetClientRect( m_hwnd, &r );
	::InvalidateRect( m_hwnd, &r, true );
}


/*---------------------------------------------------------------------+\

 * PostCalculateNeeded -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::PostCalculateNeeded()
{
	::PostMessage( m_hwnd, UWM_CALCULATENEEDED, 0, 0 );
}


/*---------------------------------------------------------------------+\

 * SetWindowTitle -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::SetWindowTitle
		(
		const char* sName
		)
{
#if defined( OS_MSWIN_WCE )
	TArrayPointer<WCHAR> wsName = ::WideStringFromString( sName );

	::SetWindowTextW( m_hwnd, wsName );
#else
	::SetWindowTextA( m_hwnd, sName );
#endif
}


/*---------------------------------------------------------------------+\

 * InitializeDialog -

\+---------------------------------------------------------------------*/
bool	CWinCEDlg::InitializeDialog
		(
		HINSTANCE	hInstance,
		LPCTSTR		szWindowClass
		)
{
	bool		bResult = true;
	WNDCLASS	wc = {0};

	wc.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= &CWinCEDlg::WndProcGlue;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WORKBENCHWIN));
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH) ::GetStockObject(NULL_BRUSH);
	wc.lpszMenuName		= 0;
	wc.lpszClassName	= szWindowClass;

	if ( ! RegisterClass(&wc) )
		bResult = false;

	m_hwnd = ::CreateWindow(szWindowClass, szWindowClass,
							XSTYLE,
							0, 0, DISPLAY_WIDTH_PIXELS, DISPLAY_HEIGHT_PIXELS,
							NULL, NULL, hInstance, this);

	if ( m_hwnd )
		m_dc = ::GetDC( m_hwnd );
	else
		bResult = false;

	return bResult;
}



/*---------------------------------------------------------------------+\

 * WndProcGlue -

\+---------------------------------------------------------------------*/
//static
LRESULT CALLBACK
		CWinCEDlg::WndProcGlue
		(
		HWND	hWnd,
		UINT	message,
		WPARAM	wParam,
		LPARAM	lParam
		)
{
	CWinCEDlgPtr	pThis = 0;

	switch ( message )
	{
	case WM_CREATE:
#if defined( WM_NCCREATE )
	case WM_NCCREATE:
#endif
		// this message is sent when a new window has just been created
		// we associate its handle with its CWinCEDlg instance
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(LPCREATESTRUCT(lParam))->lpCreateParams);
		//::SetWindowLong( hWnd, GWLP_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));
		break;
	default:
		break;
	}

	pThis = (CWinCEDlgPtr) ::GetWindowLongPtr( hWnd, GWLP_USERDATA );
	if ( pThis )
		return pThis->WndProc( hWnd, message, wParam, lParam );
	else
		return ::DefWindowProc( hWnd, message, wParam, lParam );
}



/*---------------------------------------------------------------------+\

 * WndProc -

\+---------------------------------------------------------------------*/
LRESULT CWinCEDlg::WndProc
		(
		HWND	hWnd,
		UINT	message,
		WPARAM	wParam,
		LPARAM	lParam
		)
{
	LRESULT	result = TRUE;
	int		x;
	int		y;

	try
	{
		switch (message)
		{
		case WM_TIMER:
			OnTimer( (UINT)wParam );
			break;

		case WM_PAINT:
			//TRACE("WM_PAINT\n");
			OnPaint();
			break;

		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			//TRACE("WM_LBUTTONDOWN, x=%d, y=%d\n", point.x, point.y);
			OnLButtonDown(0/* not used*/, x, y);
			break;

		case WM_LBUTTONUP:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			//TRACE("WM_LBUTTONUP, x=%d, y=%d\n", point.x, point.y);
			OnLButtonUp(0/* not used*/, x, y);
			break;

		case WM_MOUSEMOVE:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			//TRACE("WM_MOUSEMOVE, flags=%d x=%d, y=%d\n", wParam, point.x, point.y);
			OnMouseMove((UINT)wParam, x, y);
			break;

		case WM_RBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			//TRACE("WM_RBUTTONDOWN, x=%d, y=%d\n", point.x, point.y);
			OnRButtonDown(0/* not used*/, x, y);
			break;

#ifdef WM_MOUSELEAVE
		case WM_MOUSELEAVE:
			OnMouseLeave();
			break;
#endif

		//case WM_RBUTTONUP:
		//	point.x = LOWORD(lParam);
		//	point.y = HIWORD(lParam);
		//	//TRACE("WM_RBUTTONUP, x=%d, y=%d\n", point.x, point.y);
		//	OnRButtonUp(0/* not used*/, point);
		//	break;

		//case WM_MBUTTONDOWN:
		//	point.x = LOWORD(lParam);
		//	point.y = HIWORD(lParam);
		//	//TRACE("WM_MBUTTONDOWN, x=%d, y=%d\n", point.x, point.y);
		//	OnMButtonDown(0/* not used*/, point);
		//	break;

		//case WM_MBUTTONUP:
		//	point.x = LOWORD(lParam);
		//	point.y = HIWORD(lParam);
		//	//TRACE("WM_MBUTTONUP, x=%d, y=%d\n", point.x, point.y);
		//	OnMButtonUp(0/* not used*/, point);
		//	break;

		//case WM_MOUSEWHEEL:
		//	point.x = LOWORD(lParam);
		//	point.y = HIWORD(lParam);
		//	//fwKeys = LOWORD(wParam); //not used
		//	zDelta = HIWORD(wParam);
		//	//TRACE("WM_MOUSEWHEEL, x=%d, y=%d\n, zDelta=%d", point.x, point.y, zDelta);
		//	OnMouseWheel(0/* not used*/, zDelta, point);
		//	break;

		case WM_KEYDOWN:
			//TRACE("WM_KEYDOWN\n");
			OnKeyDown((UINT)wParam,LOWORD(lParam),0);
			break;

		case WM_KEYUP:
			//TRACE("WM_KEYUP\n");
			OnKeyUp((UINT)wParam,LOWORD(lParam),0);
			break;

		case WM_INITDIALOG:
			OnInitDialog( hWnd, wParam, lParam );
			//TRACE("WM_INITDIALOG\n");
			//MoveWindow(hWnd,0,0,bmi.bmih.biWidth,-bmi.bmih.biHeight,TRUE);
			break;

		case WM_CREATE:
#if defined( WM_NCCREATE )
		case WM_NCCREATE:
#endif
			//TRACE("WM_CREATE\n");
			OnCreate( hWnd, wParam, lParam );
			break;

		case WM_DESTROY:
			//TRACE("WM_DESTROY\n");
			PostQuitMessage(0);
			break;


		case WM_SIZE:
			OnSize( (UINT)wParam, LOWORD(lParam), HIWORD(lParam) );
			break;

		case WM_CLOSE:
			//TRACE("WM_CLOSE\n");
			OnClose();
			break;

		//case MSG_USB_ATTACHED_DETACHED:
		//	OnUSBAttachedDetachedMsg( (UInt8_T)wParam, (UInt8_T)lParam );
		//	break;

		//case MSG_CURSOR_SHOW:
		//	//TRACE("MSG_CURSOR_SHOW:%d\n", wParam);
		//	ShowHideCursor((wParam != 0) ? true : false);
		//	break;

		//case MSG_VNC_LAUNCHER:
		//	OnVNCLaucherMsg(wParam, lParam);
		//	break;

		case WM_COMMAND:
			{
				//int wmId = LOWORD(wParam);

				//switch (wmId)
				//{
				//case ID_CLOSE_APP:
				//	PostMessage(hWnd, WM_CLOSE, (WPARAM)0, (LPARAM)0);
				//	break;

				//default:
				//	result = DefWindowProc(hWnd, message, wParam, lParam);
				//	break;
				//}
				//result = DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		default:
			if ( UWM_CALCULATENEEDED == INT(message) )
				OnCalculateNeeded( 0, 0 );
			break;

		}
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	catch (...)
	{
		//Request a reboot and wait until it happens
		//if(SysMgrIsRunning())
		//{
		//	SysMgrRequestReboot();
		//	while (SysMgrIsRunning())
		//	{
		//		TASKSLEEP(100);
		//	}
		//}
		//else
		//{
		//	SysPwr_Reboot();
		//}
	}

	return result;
}


/*---------------------------------------------------------------------+\

 * OnTimer -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnTimer
		(
		UINT nIDEvent
		)
{
	if ( IDT_TIMER_CALCULATE == nIDEvent )
	{
		if ( m_pApplicationGauge->CalculateNow() )
			Invalidate();
	}
	else if ( IDT_TIMER_CHECKSTALE == nIDEvent )
	{
		// see if the data is stale
		m_pApplicationGauge->StaleData();
	}
}


/*---------------------------------------------------------------------+\

 * OnClose -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnClose()
{

}


/*---------------------------------------------------------------------+\

 * LazySetup -

\+---------------------------------------------------------------------*/
void CWinCEDlg::LazySetup
		(
		HWND hWnd,
		WPARAM ,//wParam,
		LPARAM //lParam
		)
{
	if ( m_pApplicationGauge )
		return;

	m_hwnd = hWnd;
	m_dc = ::GetDC( m_hwnd );


	//--------------------------------------

	//bool	bDisplayDR = false;
	//bool	bDoubleBackingstore = true;

	CApplicationGaugeWorkbenchWinPtr	pApp;
	pApp = new CApplicationGaugeWorkbenchWin;
	if ( pApp )
	{
		pApp->SetVPostCalculate( this );

		ISupportsPtr	pIPluginLibrary = NEW_OBJECT( CPluginLibrary );

		pApp->RegisterCOMObject( "PluginLibrary", pIPluginLibrary );

		pApp->Initialize1();
		m_pApplicationGauge = pApp;

		long			nFrequency;
		CVariantDataPtr	pv;
		VConfigurationPtr	pConfig;
		pConfig = pApp->Configuration();
		if ( pConfig )
		{
			m_bRemapBezelKeys = pConfig->GetEntryAsBool( "Simulate Bezel Keys", false );

			pv = pConfig->GetEntry( "Calculate Frequency" );
			if ( pv )
			{
				nFrequency = *pv;
				if ( 0 < nFrequency )
					m_nTimerValue = 1000 / nFrequency;
				else
					m_nTimerValue = 0;
				pApp->SetMaximumTimeElapsedToCalculate( m_nTimerValue );
			}

			pv = pConfig->GetEntry( "Simulate Data Frequency" );
			if ( pv )
			{
				nFrequency = *pv;
				if ( 0 < nFrequency )
					m_nTimerSimulatedDataValue = 1000 / nFrequency;
				else
					m_nTimerSimulatedDataValue = 0;
			}

			m_nTimerCheckStaleValue
				= (long)pConfig->GetEntryAsFloatUnits
				(
				"Active Dictionary Check Stale",
				"millisecond", GFLOAT_0
				);

			/*bDisplayDR =*/ pConfig->GetEntryAsBool( "Display Dirty Rectangle", false );
			/*bDoubleBackingstore
				=*/ pConfig->GetEntryAsBool( "Double Backingstore", true );

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
		m_pCommandProcessor->SetApplication( pApp );
		pApp->SetCommandProcessor( m_pCommandProcessor );
		pApp->RegisterObject( "CommandProcessor", m_pCommandProcessor );
		m_pCommandProcessor->InitializeFunctions();

		m_pFunctionProcessor = new CFunctionProcessorForPlugins;
		m_pFunctionProcessor->SetApplication( pApp );
		pApp->SetFunctionProcessor( m_pFunctionProcessor );
		pApp->RegisterObject( "FunctionProcessor", m_pFunctionProcessor );
		m_pFunctionProcessor->InitializeFunctions();


		pApp->Initialize2();

		RECT	r;
		GetClientRect( m_hwnd, &r );

		IDrawPtr pDraw = pApp->Draw();
		if ( pDraw )
		{
			//TIP(IDrawDebug)	pIDbg = pDraw;
			//if ( pIDbg )
			//{
			//	pIDbg->SetDoubleBackingstore( bDoubleBackingstore );
			//	pIDbg->SetDisplayDirtyRectangle( bDisplayDR );
			//}

			TIP(IDrawWin32) pIDw = pDraw;
			if ( pIDw )
				pIDw->SetHDC( m_hwnd, m_dc, &r );

		}


		m_pKeyProcessor = new CKeyProcessorWin;
		m_pKeyProcessor->SetApplication( pApp );

		CMouseProcessorWinPtr	pMPW = new CMouseProcessorWin;
#if 0	// force skewed mouse coordinates to test screen alignment
		CMouseProcessorWBPtr	pMPWB = new CMouseProcessorWB;
		pMPWB->SetMouseProcessor( pMPW );
		m_pMouseProcessor = (VMouseProcessorWinPtr)(pMPWB);
#else
		m_pMouseProcessor = (VMouseProcessorWinPtr)(pMPW);
#endif
		m_pMouseProcessor->SetApplication( pApp );


		pIPluginLibrary->Release();



		m_pApplicationGauge->Size( r.right-r.left, r.bottom-r.top );
		m_pApplicationGauge->CalculateNow();
	}


	UINT	nTimerID = 0;

	// Starting the timer
	nTimerID = IDT_TIMER_CALCULATE;
	if ( 0 < m_nTimerValue )
		::SetTimer( m_hwnd, (UINT_PTR)nTimerID, m_nTimerValue, NULL );

	nTimerID = IDT_TIMER_CHECKSTALE;
	if ( 0 < m_nTimerCheckStaleValue )
		::SetTimer( m_hwnd, (UINT_PTR)nTimerID, m_nTimerCheckStaleValue, NULL );



}


/*---------------------------------------------------------------------+\

 * OnInitDialog -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnInitDialog
		(
		HWND hWnd,
		WPARAM wParam,
		LPARAM lParam
		)
{

	LazySetup( hWnd, wParam, lParam );

}


/*---------------------------------------------------------------------+\

 * OnCreate -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnCreate
		(
		HWND	hWnd,
		WPARAM	wParam,
		LPARAM	lParam
		)
{

	LazySetup( hWnd, wParam, lParam );

}



/*---------------------------------------------------------------------+\

 * OnPaint -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnPaint
		(
		void
		)
{
	PAINTSTRUCT	ps;
	//HDC			dc;

	/*dc =*/ ::BeginPaint( m_hwnd, &ps );


	RECT	rct = ps.rcPaint;

	if ( rct.left < rct.right  &&  rct.top < rct.bottom )
	{
		IDrawPtr		pDraw = m_pApplicationGauge->Draw();
		if ( pDraw )
		{
			TIP(IDrawWin32)	pDW = pDraw;
			if ( pDW )
			{
				//pDW->SetHDC( m_hwnd, dc, &rct );
				pDW->UpdateRect( &rct );
				m_pApplicationGauge->OnDraw();
			}
			else
			{
				LogPrint( "%s - IDrawWin32 interface not found\n", __PRETTY_FUNCTION__ );
			}
		}
		else
		{
			LogPrint( "%s - draw object missing\n", __PRETTY_FUNCTION__ );
		}
	}

	::EndPaint( m_hwnd, &ps );
}



/*---------------------------------------------------------------------+\

 * OnKeyDown -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnKeyDown
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	if ( m_bRemapBezelKeys )
		nChar = RemapBezelKey( nChar );

	m_pKeyProcessor->OnKeyDown( nChar, nRepCnt, nFlags );
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}


/*---------------------------------------------------------------------+\

 * OnKeyUp -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnKeyUp
		(
		UINT nChar,
		UINT nRepCnt,
		UINT nFlags
		)
{
	if ( m_bRemapBezelKeys )
		nChar = RemapBezelKey( nChar );

	m_pKeyProcessor->OnKeyUp( nChar, nRepCnt, nFlags );
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}


/*---------------------------------------------------------------------+\

 * RemapBezelKey -

\+---------------------------------------------------------------------*/
UINT	CWinCEDlg::RemapBezelKey
		(
		UINT nChar
		)
{
	if ( '1' <= nChar  &&  nChar <= '9' )
		nChar = nChar - '1' + 255 + 1;
	else if ( '0' == nChar )
		nChar = nChar - '0' + 255 + 10;
	else if ( VK_NUMPAD0 <= nChar  &&  nChar <= VK_NUMPAD9 )
		nChar = nChar - VK_NUMPAD0 + 255 + 10;

	return nChar;
}







/*---------------------------------------------------------------------+\

 * OnCalculateNeeded -

\+---------------------------------------------------------------------*/
LRESULT	CWinCEDlg::OnCalculateNeeded
		(
		WPARAM ,//notused,
		LPARAM // notused
		)
{
	if ( m_pApplicationGauge->CalculateNow() )
		Invalidate();
	return NOERROR;
}





/*---------------------------------------------------------------------+\

 * OnLButtonUp -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnLButtonUp
		(
		UINT	nFlags,
		int		x,
		int		y
		)
{

	m_pMouseProcessor->OnLButtonUp( nFlags, x, y );
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}



/*---------------------------------------------------------------------+\

 * OnLButtonDown -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnLButtonDown
		(
		UINT	nFlags,
		int		x,
		int		y
		)
{
#ifndef OS_WIN32_WCE
	TRACKMOUSEEVENT	tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hwnd;
	tme.dwHoverTime = 0;
	TrackMouseEvent( &tme );
#endif

	m_pMouseProcessor->OnLButtonDown( nFlags, x, y );
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}



/*---------------------------------------------------------------------+\

 * OnRButtonDown -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnRButtonDown
		(
		UINT	,//nFlags,
		int		,//x,
		int		//y
		)
{
	// TODO: Add your message handler code here and/or call default
	//ClientToScreen(&point);
	//if ( m_pContextMenu->GetSubMenu(0) )
	//{
	//	CMenu*	pSubMenu = m_pContextMenu->GetSubMenu(0);
	//	if ( m_bFullScreen )
	//	{
	//		/* check menu item if full screen mode */
	//		pSubMenu->CheckMenuItem(ID_FULLSCREENMODE,MF_CHECKED );
	//	}
	//	else
	//	{
	//		/* uncheck menu item */
	//		pSubMenu->CheckMenuItem(ID_FULLSCREENMODE,MF_UNCHECKED );
	//	}

	//	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
	//		point.x,point.y,this);
	//}
}



//void CWinCEDlg::OnMouseHover(UINT nFlags, POINT& point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	m_pMouseProcessor->OnMouseHover( nFlags, point );
//
//	CView::OnMouseHover(nFlags, point);
//}

/*---------------------------------------------------------------------+\

 * OnMouseLeave -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnMouseLeave()
{

	m_pMouseProcessor->OnMouseLeave();
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}

/*---------------------------------------------------------------------+\

 * OnMouseMove -

\+---------------------------------------------------------------------*/
void	CWinCEDlg::OnMouseMove
		(
		UINT	nFlags,
		int		x,
		int		y
		)
{
	m_pMouseProcessor->OnMouseMove( nFlags, x, y );
	if ( m_pApplicationGauge->Calculate() )
		Invalidate();

}

/*---------------------------------------------------------------------+\

 * OnSize -

\+---------------------------------------------------------------------*/
void CWinCEDlg::OnSize
		(
		UINT ,//nType,
		int cx,
		int cy
		)
{
	if ( 0 < cx  &&  0 < cy )
	{
		if ( m_pApplicationGauge )
		{
			if ( m_pApplicationGauge->Size( cx, cy ) )
				Invalidate();
		}
	}
}




/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||
||	 Overrides
||
\+=====================================================================*/



}}
