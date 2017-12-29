/*---------------------------------------------------------------------+\
|
|	winmain.cpp  --  main entry point for WinCE application
|
|	Purpose:
|
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
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#ifdef _DEBUG
// enable memory leak detection
#	if defined( _MSC_VER )
#		ifndef _WIN32_WCE
#			define _CRTDBG_MAP_ALLOC
#			include <stdlib.h>
#			include <crtdbg.h>
#			define CHECK_LEAKS _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#		endif
#	endif
#endif // _DEBUG
#ifndef CHECK_LEAKS
#	define CHECK_LEAKS
#endif

#include "LogFile.h"
#include "UPlatform.h"
#if defined( OS_MSWIN )

#include <tchar.h>

#include "CWinCEApp.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local Defines / Constants											|
|																		|
\+---------------------------------------------------------------------*/
#define APPLICATION_NAME	"Workbench"

#if defined OS_MSWIN_WCE
#	define	LPXSTR	LPWSTR
#else
#	define	LPXSTR	LPSTR
#endif

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
static CWinCEApp*	g_pApplication = NULL;		// The one & only application object
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
||	 private functions													|
\+=====================================================================*/

/*=====================================================================+\
||	 public functions													|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * WinMain - main entry point

\+---------------------------------------------------------------------*/
INT WINAPI
		WinMain
		(
		HINSTANCE	hInstance,
		HINSTANCE	,//hPrevInstance,
		LPXSTR		,//lpCmdLine,
		INT			//nCmdShow
		)
{
	CHECK_LEAKS

	HACCEL	hAccelTable = NULL;
	MSG		msg = {0};


	DbgPrint( "Starting Application ...\n" );

	try
	{
		//Setup FPU for chop mode
#if defined OS_MSWIN_WCE
		_controlfp(_RC_CHOP, _MCW_RC);
#endif

		g_pApplication = new CWinCEApp;
		if ( ! g_pApplication )
			return 1;

		// This determines if we're allowed to run and instantiates the VTWin32Dlg app.
		if (!g_pApplication->InitInstance(hInstance, TEXT(APPLICATION_NAME))) 
		{
			DbgPrint( "Application did not initialize\n" );
			return 1;
		}


		g_pApplication->Start();

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if ( hAccelTable )
		{
			DestroyAcceleratorTable(hAccelTable);
		}

		delete g_pApplication;

	}
	catch ( ... )
	{
	}

	return (int) msg.wParam;
}




#endif	// OS_MSWIN
