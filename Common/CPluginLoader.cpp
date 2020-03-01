/*---------------------------------------------------------------------+\
|
|	CPluginLoader.cpp  --  brief description of what CPluginLoader.cpp is for
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
	11-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CPluginLoader.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"
#if defined( DLL_UNISTD )
#	include <dlfcn.h>
#endif

namespace Yogi { namespace Common {
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
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CPluginLoader - constructor

\+---------------------------------------------------------------------*/
CPluginLoader::CPluginLoader
		(
		void
		)
		: m_sPath()
		, m_oMutex()
{
}


/*---------------------------------------------------------------------+\

 * ~CPluginLoader - destructor

\+---------------------------------------------------------------------*/
CPluginLoader::~CPluginLoader
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetPath -

\+---------------------------------------------------------------------*/
void	CPluginLoader::SetPath
		(
		const char*	sPath
		)
{
	m_oMutex.Lock();
	m_sPath = sPath;
	m_oMutex.Unlock();
}


/*---------------------------------------------------------------------+\

 * LoadFactory -

\+---------------------------------------------------------------------*/
VPluginFactoryPtr
		CPluginLoader::LoadFactory
		(
		const char*		sClass,
		ULibraryHdl*	phLib
		)
{
	VPluginFactoryPtr		pPlugFact = 0;
	ULibraryHdl				hLibrary = 0;
	FactoryCreateFunction	pFunc = 0;
	Yogi::Core::CCharString	sLibraryName = BuildLibraryPath( sClass );

	if ( 0 < sLibraryName.Length() )
	{
		Yogi::Core::CMutexLocker	locker( &this->m_oMutex );
		hLibrary = DLLOpen( sLibraryName.Pointer() );
		if ( hLibrary )
		{
			ULibraryFuncPtr	pF = 0;
			pF = DLLGetProcedure( hLibrary, "CreatePluginFactory" );
			if ( pF )
			{
				BEGIN_IGNORE_WARNING(4191)	// typecast warning
				pFunc = (FactoryCreateFunction)(pF);
				END_IGNORE_WARNING
				pPlugFact = pFunc();
			}
			else
			{
				Yogi::Core::DbgPrint( "Unrecognized plugin - missing entry point: %s\n", sClass );
				DLLClose( hLibrary );
			}
		}
		else
		{
			Yogi::Core::DbgPrint( "Unable to load plugin factory: %s\n", sLibraryName.Pointer() );
		}
	}
	if ( phLib )
		*phLib = hLibrary;

	return pPlugFact;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * BuildLibraryPath -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING

Yogi::Core::CCharString
		CPluginLoader::BuildLibraryPath
		(
		const char*	sClass
		)
{
	const char	sFolderSeparator[] = { FOLDER_SEPARATOR, 0 };
	char		sBuffer[256];
	Yogi::Core::CCharString	sPath;

	m_oMutex.Lock();
	m_sPath.CopyTo( sBuffer, sizeof(sBuffer) );
	m_oMutex.Unlock();

	index_t	i = (index_t)m_sPath.Length() - 1;

	if ( FOLDER_SEPARATOR == sBuffer[i] )
		sBuffer[i] = 0;

	strcat_s( sBuffer, sizeof(sBuffer), sFolderSeparator );
	strcat_s( sBuffer, sizeof(sBuffer), sClass );
#if defined( DLL_UNISTD )
	strcat_s( sBuffer, sizeof(sBuffer), ".so" );
#elif defined( DLL_WINDOWS )
	#if defined( OS_MSWIN_MINGW )
		strcat_s( sBuffer, sizeof(sBuffer), "-0.dll" );
	#else
		strcat_s( sBuffer, sizeof(sBuffer), ".dll" );
	#endif
#endif
	return Yogi::Core::CCharString( sBuffer );
}

//END_OVERRUN_WARNING

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
