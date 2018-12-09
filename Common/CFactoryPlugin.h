/*==================================================================*//**
*
*	@file	CFactoryPlugin.h
*	@brief	Make a plugin object
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	13-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add Filter support for the PluginConfiguration
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CFactoryPlugin
#define _H_CFactoryPlugin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VFactoryLite.h"

#include "CPluginConfiguration.h"
#include "VPluginLibrary.h"
#include "VPluginFilter.h"
#include "TPointer.h"
#include "TArray.h"
#include "ISupports.h"

namespace Yogi { namespace Common {

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

typedef	Yogi::Core::TArray<ISupportsPtr>	ISupportsArray;


typedef class CFactoryPlugin*		CFactoryPluginPtr;
typedef class CFactoryPlugin&		CFactoryPluginRef;
typedef const class CFactoryPlugin&	ConstCFactoryPluginRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CFactoryPlugin : public VFactoryLite
{
//	class lifecycle  ----------------------------------------------------
public:
					CFactoryPlugin();
	virtual			~CFactoryPlugin();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	ISupportsArray*	Make
					(
					const char*			sNameXML,
					VPluginLibraryPtr	pLib,
					VPluginFilterPtr	pFilter = 0
					);


protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------

	virtual
	CPluginConfigurationPtr
					MakeConfiguration
					(
					const char*	sName,
					CPluginConfigurationPtr	pConfig = 0
					);

	CPluginConfigurationPtr
					Plugins
					(
					CPluginConfigurationPtr pConfig,
					XMLIteratorPtr		pIt
					);
	bool			PluginInclude
					(
					CPluginConfigurationPtr	pConfig,
					XMLIteratorPtr		pIt
					);

	bool			Plugin
					(
					CPluginConfigurationPtr	pConfig,
					XMLIteratorPtr		pIt
					);
	bool			Parameters
					(
					CPluginConfigurationPtr	pConfig,
					XMLIteratorPtr		pIt
					);

	bool			Param
					(
					CPluginConfigurationPtr	pConfig,
					XMLIteratorPtr		pIt
					);

	bool			IncludeFile
					(
					CPluginConfigurationPtr	pConfig,
					XMLIteratorPtr		pIt
					);



//	protected data  -----------------------------------------------------



private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================


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
}}


#endif /* _H_CFactoryPlugin */


