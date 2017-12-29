/*---------------------------------------------------------------------+\
|
|	UFile.cpp  --  brief description of what UFile.cpp is for
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
	19-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <stdio.h>
//#include <sys/types.h>

#include "UFile.h"
#include "TPointer.h"

#include "UPlatform.h"
#include "UPlatformString.h"
#if defined( FILEIO_WINDOWS )
#	include <winbase.h>
#elif defined( FILEIO_UNISTD )
#	include <unistd.h>
#	include <sys/stat.h>
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
NAMESPACE_ROOT_BEGIN

/*---------------------------------------------------------------------+\

 * FileExists -

\+---------------------------------------------------------------------*/
bool	FileExists
		(
		const char*	sFilePath
		)
{
	bool	bResult = false;

	if ( sFilePath  &&  0 != *sFilePath )
	{
#if defined( FILEIO_UNISTD )

		struct stat	ss;

		int	n = ::stat( sFilePath, &ss );
		if ( 0 == n )
		{
			if ( S_ISREG(ss.st_mode) )
				bResult = true;
			else if ( S_ISDIR(ss.st_mode) )
				bResult = false;		// just to remind me how to check for dir
		}


#elif defined( FILEIO_WINDOWS )

		::SetLastError( NOERROR );

#	if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR>	wsFilePath = WideStringFromString( sFilePath );
		const DWORD	nAttr = ::GetFileAttributes( wsFilePath );
#	else
		const DWORD nAttr = ::GetFileAttributesA( sFilePath );
#	endif
		if ( INVALID_FILE_ATTRIBUTES != nAttr )
		{
			const DWORD nErr = ::GetLastError();

			if ( ERROR_FILE_NOT_FOUND == nErr
				||	ERROR_PATH_NOT_FOUND == nErr )
			{
				bResult = false;
			}
			else
			{
				if ( 0 != (FILE_ATTRIBUTE_DIRECTORY & nAttr) )
					bResult = false;
				else
					bResult = true;
			}

		}

#endif
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * FolderExists -

\+---------------------------------------------------------------------*/
bool	FolderExists
		(
		const char*	sFilePath
		)
{
	bool	bResult = false;

	if ( sFilePath  &&  0 != *sFilePath )
	{
#if defined( FILEIO_UNISTD )

		struct stat	ss;

		int	n = ::stat( sFilePath, &ss );
		if ( 0 == n )
		{
			if ( S_ISDIR(ss.st_mode) )
				bResult = true;
		}


#elif defined( FILEIO_WINDOWS )

		::SetLastError( NOERROR );

#	if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR>	wsFilePath = WideStringFromString( sFilePath );
		const DWORD	nAttr = ::GetFileAttributes( wsFilePath );
#	else
		const DWORD nAttr = ::GetFileAttributesA( sFilePath );
#	endif
		if ( INVALID_FILE_ATTRIBUTES != nAttr )
		{
			const DWORD nErr = ::GetLastError();

			if ( ERROR_FILE_NOT_FOUND == nErr
				||	ERROR_PATH_NOT_FOUND == nErr )
			{
				bResult = false;
			}
			else
			{
				if ( 0 != (FILE_ATTRIBUTE_DIRECTORY & nAttr) )
					bResult = true;
			}

		}

#endif
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * PathBuild -

\+---------------------------------------------------------------------*/
bool	PathBuild
		(
		char*		sBuffer,
		size_t		nSizeBuffer,
		const char*	sBasePath,
		const char*	sAddPath
		)
{
	bool	bResult = false;
	size_t	nLenBase = strlen(sBasePath);
	size_t	nLenAdd = strlen(sAddPath);
	size_t	nSize = nLenBase + nLenAdd;

	if ( nSize < nSizeBuffer )
	{
		strcpy_s( sBuffer, nSizeBuffer, sBasePath );

		size_t	i = nLenBase - 1;
		if ( FOLDER_SEPARATOR == sBuffer[i] )
			sBuffer[i] = 0;

		if ( '.' == sAddPath[0] )
		{
			if ( '.' == sAddPath[1] )
			{
			}
			else
			{
			}
		}
		i = strlen(sBuffer);
		sBuffer[i] = FOLDER_SEPARATOR;
		sBuffer[i+1] = 0;

		strcat_s( sBuffer, nSizeBuffer, sAddPath );
	}

	return bResult;
}




NAMESPACE_ROOT_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

