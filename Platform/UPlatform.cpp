/*---------------------------------------------------------------------+\
|
|	UPlatform.cpp  --  brief description of what UPlatform.cpp is for
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
	17-Jan-2013			J.Griswold
		Change conditionals away from OS to feature defined in UMachine.h
	27-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add GetUserConfigFolder function
	28-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Add FileExists and FolderExists functions
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add new GetApplicationFolder that will return the folder
		from which the application is running
	24-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove the namespace from UPlatform since these functions
		are global in nature and replace or emmulate global functions
	26-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Make sprintf_s for Linux a real function instead of a #define
	25-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision (moved functions from header file)
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UOSIncludes.h"
//#include <stdarg.h>
//#include <stdio.h>

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"

#include "UFile.h"
#include "TPointer.h"

#if defined( THREADS_WINDOWS )
#	include <winerror.h>
#	include <winbase.h>
#	if ! defined( OS_WIN32_WCE )
#		include <process.h>
#	endif
//#elif defined( THREADS_POSIX )  ||  defined( DLL_UNISTD )
//#	include <unistd.h>
//#	include <dlfcn.h>
#endif
#if defined( EXE_MACINTOSH )
#	include <mach-o/dyld.h>
#endif


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
using namespace Yogi::Core;
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/


#if defined( OS_MSWIN_WCE )

static int			g_nCountEnvVars;
static char**		g_asEnviron;
static wchar_t**	g_awsEnviron;


static char* messages[]
= {
	/*0           */    "No error",
	/*EPERM       */    "Operation not permitted",
	/*ENOENT      */    "No such file or directory",
	/*ESRCH       */    "No such process",
	/*EINTR       */    "Interrupted system call",
	/*EIO         */    "I/O error",
	/*ENXIO       */    "No such device or address",
	/*E2BIG       */    "Arg list too long",
	/*ENOEXEC     */    "Exec format error",
	/*EBADF       */    "Bad file descriptor",
	/*ECHILD      */    "No child processes",
	/*EAGAIN      */    "Resource temporarily unavailable",
	/*ENOMEM      */    "Not enough memory",
	/*EACCES      */    "Permission denied",
	/*EFAULT      */    "Bad address",
	/*15          */    "Unknown error",						// ENOTBLK "Block device required"
	/*EBUSY       */    "Device or resource busy",
	/*EEXIST      */    "File exists",
	/*EXDEV       */    "Improper link",						//         "Cross-device link"
	/*ENODEV      */    "No such device",
	/*ENOTDIR     */    "Not a directory",
	/*EISDIR      */    "Is a directory",
	/*EINVAL      */    "Invalid argument",
	/*ENFILE      */    "Too many open files in system",
	/*EMFILE      */    "Too many open files",
	/*ENOTTY      */    "Inappropriate I/O control operation",	//         "Not a character device"
	/*26          */    "Unknown error",						// ETXTBSY "Text file busy"
	/*EFBIG       */    "File too large",
	/*ENOSPC      */    "No space left on device",
	/*ESPIPE      */    "Invalid seek",							//         "Illegal seek"
	/*EROFS       */    "Read-only file system",
	/*EMLINK      */    "Too many links",
	/*EPIPE       */    "Broken pipe",
	/*EDOM        */    "Domain error",							//         "Math arg out of domain of func"
	/*ERANGE      */    "Result too large",						//         "Math result out of range"
	/*35          */    "Unknown error",						// ENOMSG  "No message of desired type"
	/*EDEADLK     */    "Resource deadlock avoided",			// EIDRM   "Identifier removed"
	/*37          */    "Unknown error",						// ECHRNG  "Channel number out of range"
	/*ENAMETOOLONG*/    "Filename too long",
	/*ENOLCK      */    "No locks available",
	/*ENOSYS      */    "Function not implemented",
	/*ENOTEMPTY   */    "Directory not empty",
	/*EILSEQ      */    "Illegal byte sequence"
};
const int NUM_MESSAGES = sizeof(messages)/sizeof(messages[0]);

#endif



static char	g_sApplicationFolder[MAXPATH] = {0};
static char	g_sApplicationRootFolder[MAXPATH] = {0};
static char	g_sUserConfigFolder[MAXPATH] = {0};
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

 * GetApplicationFolder - identify the application folder

\+---------------------------------------------------------------------*/
const char*
		GetApplicationFolder
		(
		void
		)
{
	if ( g_sApplicationFolder[0] )
	{
		return g_sApplicationFolder;
	}
	else
	{
		g_sApplicationFolder[0] = 0;

#if defined( EXE_WINDOWS )

		DWORD	nLen;
#	if defined( OS_MSWIN_WCE )
		WCHAR	wsAppFolder[sizeof(g_sApplicationFolder)];
		nLen = ::GetModuleFileName( NULL, wsAppFolder, sizeof(wsAppFolder) );
		::WideCharToMultiByte(CP_ACP, 0, wsAppFolder, nLen, g_sApplicationFolder, sizeof(g_sApplicationFolder),NULL,NULL);
		g_sApplicationFolder[nLen] = 0;
#	else
		nLen = ::GetModuleFileNameA( NULL, g_sApplicationFolder, sizeof(g_sApplicationFolder) );
		g_sApplicationFolder[nLen] = 0;
#	endif

		// get rid of application (exe) name
		char*	s = ::strrchr( g_sApplicationFolder, '\\' );
		if ( s )
			*s = 0;

#elif defined( EXE_MACINTOSH )

		uint32_t	nSize = sizeof(g_sApplicationFolder);
		if ( 0 == _NSGetExecutablePath( g_sApplicationFolder, &nSize ) )
		{
			// get rid of application (exe) name
			char*	s = ::strrchr( g_sApplicationFolder, '/' );
			if ( s )
				*s = 0;
		}


#elif defined( EXE_LINUX )  ||  defined( EXE_UNIX )

		char	szTmp[80];

		sprintf(szTmp, "/proc/%d/exe", getpid());

		int nBytes = umin((size_t)readlink(szTmp, g_sApplicationFolder, sizeof(g_sApplicationFolder)), sizeof(g_sApplicationFolder) - 1);

		if ( 0 <= nBytes )
		{
			g_sApplicationFolder[nBytes] = '\0';

			// get rid of application (exe) name
			char*	s = ::strrchr( g_sApplicationFolder, '/' );
			if ( s )
				*s = 0;
		}

#else

		char*	s = ::getcwd( NULL, 0 );
		if ( s )
		{
			::strcpy( g_sApplicationFolder, s );
		}


#endif
		return g_sApplicationFolder;
	}
}

/*---------------------------------------------------------------------+\

 * GetApplicationRootFolder - get application root (no debug or release)

\+---------------------------------------------------------------------*/
const char*
		GetApplicationRootFolder
		(
		void
		)
{
	if ( ! g_sApplicationRootFolder[0] )
	{
		const char*	sApp = ::GetApplicationFolder();
		strcpy_s( g_sApplicationRootFolder, sizeof(g_sApplicationRootFolder),
					sApp );

		const char sDebug[] = FOLDER_SEPARATOR_S "debug";
		const char sRelease[] = FOLDER_SEPARATOR_S "release";

		char*	s = strrchr( g_sApplicationRootFolder, FOLDER_SEPARATOR_C );
		if ( s )
		{
			if ( 0 == _strnicmp( s, sDebug, strlen(sDebug) ) )
				*s = 0;
			else if ( 0 == _strnicmp( s, sRelease, strlen(sRelease) ) )
				*s = 0;
		}
	}
	return g_sApplicationRootFolder;
}


/*---------------------------------------------------------------------+\

 * GetUserConfigFolder - get user config folder (app-root/config)

\+---------------------------------------------------------------------*/
const char*
		GetUserConfigFolder
		(
		void
		)
{
	if ( ! g_sUserConfigFolder[0] )
	{
		const char*	sApp = ::GetApplicationRootFolder();
		strcpy_s( g_sUserConfigFolder, sizeof(g_sUserConfigFolder),
					sApp );

		char*	t = g_sUserConfigFolder + ::strlen(g_sUserConfigFolder) - 1;
		if ( FOLDER_SEPARATOR_C == *t )
			strcat_s( g_sUserConfigFolder, sizeof(g_sUserConfigFolder),
						"Config" FOLDER_SEPARATOR_S );
		else
			strcat_s( g_sUserConfigFolder, sizeof(g_sUserConfigFolder),
						FOLDER_SEPARATOR_S "Config" FOLDER_SEPARATOR_S );

	}
	return g_sUserConfigFolder;
}












/*---------------------------------------------------------------------+\

 * DLLOpen

\+---------------------------------------------------------------------*/
ULibraryHdl
		DLLOpen
		(
		const char*	sLibraryName
		)
{
	ULibraryHdl	hLibrary = 0;

	if ( FileExists(sLibraryName) )
	{

#if defined( DLL_UNISTD )

		hLibrary = ::dlopen( sLibraryName, RTLD_NOW|RTLD_GLOBAL );

		if ( ! hLibrary )
		{
			LogPrint( "DLLOpen: Unable to load %s\n", sLibraryName );
			const char*	s = dlerror();
			LogPrint( " %s\n", s);
			int	n = errno;
			if ( 0 != n )
				perror( 0 );
		}

#elif defined( DLL_WINDOWS )
#	if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR>	pwLibName = WideStringFromString( sLibraryName );
		hLibrary = ::LoadLibrary( pwLibName );
#	else
		//hLibrary = ::LoadLibraryExA( sLibraryName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH );

		hLibrary = ::LoadLibraryA( sLibraryName );
#	endif
		if ( ! hLibrary )
		{
			LogPrint( "DLLOpen: Unable to load %s\n", sLibraryName );
			const char*	s = DLLErrorString();
			LogPrint( " %s\n", s );
		}

#endif

	}
	else
	{
		LogPrint( "DLLOpen: File not found %s\n", sLibraryName );
	}

	return hLibrary;
}


/*---------------------------------------------------------------------+\

 * DLLGetProcedure

\+---------------------------------------------------------------------*/
ULibraryFuncPtr
		DLLGetProcedure
		(
		ULibraryHdl	hLibrary,
		const char*	sFunctionName
		)
{
#if defined( DLL_UNISTD )

	return reinterpret_cast<ULibraryFuncPtr>(::dlsym( hLibrary, sFunctionName ));

#elif defined( DLL_WINDOWS )
#	if defined( OS_MSWIN_WCE )

	return ::GetProcAddressA( hLibrary, sFunctionName );

#	else

	return ::GetProcAddress( hLibrary, sFunctionName );

#	endif
#endif
}



/*---------------------------------------------------------------------+\

 * DLLClose

\+---------------------------------------------------------------------*/
void	DLLClose
		(
		ULibraryHdl	hLibrary
		)
{
#if defined( DLL_UNISTD )

	::dlclose( hLibrary );

#elif defined( DLL_WINDOWS )

	::FreeLibrary( hLibrary );

#endif
}


/*---------------------------------------------------------------------+\

 * DLLErrorString

\+---------------------------------------------------------------------*/
const
char*	DLLErrorString
		(
		void
		)
{

#if defined( DLL_UNISTD )

	return ::dlerror();

#elif defined( DLL_WINDOWS )

	BEGIN_IGNORE_WARNING( 4996 )
	return ::strerror( (int)::GetLastError() );
	END_IGNORE_WARNING

#endif
}












/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

