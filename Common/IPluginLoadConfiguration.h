/*---------------------------------------------------------------------+\
|
|	IPluginLoadConfiguration.h  --  load plugin configuration data
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
	03-Jul-2010			J.Griswold		(Reviewed by: xxxx)
		Move definition of IXID to cpp file
	10-May-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IPluginLoadConfiguration
#define _H_IPluginLoadConfiguration
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "VPluginConfiguration.h"
#include "VPluginLibrary.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
extern const IXID	IXID_IPluginLoadConfiguration;

typedef interface_ IPluginLoadConfiguration*		IPluginLoadConfigurationPtr;
typedef interface_ IPluginLoadConfiguration&		IPluginLoadConfigurationRef;
typedef const interface_ IPluginLoadConfiguration&	ConstIPluginLoadConfigurationRef;
/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IPluginLoadConfiguration : public ISupports
{
	/**
	*	Load - load configuration information to correctly
	*			initialize the object
	*/
	virtual
	bool	Load								///@return true on success
			(
			VPluginConfigurationPtr	pConfig,	///< [in]
			VPluginLibraryPtr		pLib		///< [in]
			) = 0;

};

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
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

NAMESPACE_COMMON_END



#endif /* _H_IPluginLoadConfiguration */

