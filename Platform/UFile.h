//=======================================================================
//
//!	@file UFile.h
//!
//!	@brief utilities for file processing
//
//=======================================================================
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
#include "UDeclPlatform.h"
#include "UOSIncludes.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#if ! defined( MAXPATH )
#    if defined( PATH_MAX )
#        define MAXPATH PATH_MAX
#    elif defined( MAXPATHLEN )
#        define MAXPATH MAXPATHLEN
#    else
#        define MAXPATH 1024
#    endif
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
namespace Yogi { namespace Core {

//!	deterimine if file exists
//!
CORE_API( bool )
FileExists                       //!@return true if file exists, false otherwise
        ( const char* sFilePath  //!< [in] file to check
        );

//!	determine if a folder exists
//!
CORE_API( bool )
FolderExists  //!@return true if folder exists, false otherwise
        ( const char* sFilePath  //!< [in] folder to check
        );

//! add onto an existing path
//!
CORE_API( bool )
PathBuild                                 //!@return false if error
        ( char*             sBuffer,      //!< [out] buffer to receive new path
                size_t      nSizeBuffer,  //!< [in] size of output buffer
                const char* sBasePath,    //!< [in] first part of path
                const char* sAddPath      //!< [in] path to append to base-path
        );


/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}  // namespace Yogi::Core


#endif /* _H_UFile */
