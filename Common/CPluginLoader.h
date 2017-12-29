/*---------------------------------------------------------------------+\
|
|	CPluginLoader.h  --  brief description of what CPluginLoader.h is for
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
	11-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CPluginLoader
#define _H_CPluginLoader
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPlugin.h"
#include "VPluginFactory.h"

#include "CCharString.h"
#include "CMutex.h"

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
typedef class CPluginLoader*		CPluginLoaderPtr;
typedef class CPluginLoader&		CPluginLoaderRef;
typedef const class CPluginLoader&	ConstCPluginLoaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CPluginLoader
{
//	class lifecycle  ----------------------------------------------------
public:
					CPluginLoader();
	virtual			~CPluginLoader();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	void				SetPath( const char* sPath );
	VPluginFactoryPtr	LoadFactory( const char* sClass, ULibraryHdl* phLib );

protected:
//	protected types  ----------------------------------------------------

	typedef	VPluginFactoryPtr
						(*FactoryCreateFunction)( void );

//	protected functions  ------------------------------------------------

	CCharString			BuildLibraryPath( const char* sClass );

//	protected data  -----------------------------------------------------

	CCharString		m_sPath;
	CMutex			m_oMutex;

private:
//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


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



#endif /* _H_CPluginLoader */

