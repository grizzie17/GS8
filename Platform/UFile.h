/*------------------------------------------------------------------*//**
*
*	@file UFile.h
*
*	@brief utilities for file processing
*
*//*-------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	19-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UFile
#define _H_UFile
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#include "NamespaceRoot.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#if ! defined( MAXPATH )
#	if defined( PATH_MAX )
#		define MAXPATH	PATH_MAX
#	elif defined( MAXPATHLEN )
#		define MAXPATH	MAXPATHLEN
#	else
#		define MAXPATH	1024
#	endif
#endif
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
NAMESPACE_ROOT_BEGIN

/**
 *	FileExists -- deterimine if file exists
 */
bool	FileExists				///@return true if file exists, false otherwise
		(
		const char*	sFilePath	///< [in] file to check
		);

/**
 *	FolderExists -- determine if a folder exists
 */
bool	FolderExists			///@return true if folder exists, false otherwise
		(
		const char*	sFilePath	///< [in] folder to check
		);

bool	PathBuild
		(
		char*		sBuffer,
		size_t		nSizeBuffer,
		const char*	sBasePath,
		const char*	sAddPath
		);



/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

NAMESPACE_ROOT_END


#endif /* _H_UFile */

