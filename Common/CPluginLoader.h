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

#include "UDeclCommon.h"

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
typedef class CPluginLoader*		CPluginLoaderPtr;
typedef class CPluginLoader&		CPluginLoaderRef;
typedef const class CPluginLoader&	ConstCPluginLoaderRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS CPluginLoader
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

	Yogi::Core::CCharString		BuildLibraryPath( const char* sClass );

//	protected data  -----------------------------------------------------

	Yogi::Core::CCharString		m_sPath;
	Yogi::Core::CMutex			m_oMutex;

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

}}



#endif /* _H_CPluginLoader */
