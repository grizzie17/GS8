/*---------------------------------------------------------------------+\
|
|	CServiceManager.cpp  --  brief description of what CCommandProcessor.cpp is for
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
	12-Jul-2010			J.Griswold		(Reviewed by: P.Hogan)
		Add optional InitialState pointer for the RegisterCommand func.
    02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Fix possible crash in InitializeFunctions and
		assure all needed parameters are present in RegisterCommand
	16-May-2010			J.Griswold		(Reviewed by: PJH)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CServiceManager.h"

#include "CFactoryPlugin.h"
#include "IApplicationUser.h"
#include "LogFile.h"

namespace Yogi { namespace Gadget {
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

 * CServiceManager - constructor

\+---------------------------------------------------------------------*/
CServiceManager::CServiceManager
		(
		void
		)
		: m_aList()
		, m_pLibrary( 0 )
		, m_pApplication( 0 )
		, m_oMutex()
{
}


/*---------------------------------------------------------------------+\

 * ~CServiceManager - destructor

\+---------------------------------------------------------------------*/
CServiceManager::~CServiceManager
		(
		void
		)
{
	THashTableEnumerator< Yogi::Core::CCharString, IServicePtr>
			enumSvcs = m_aList.GetEnumerator();

	while ( enumSvcs.MoveNext() )
	{
		IServicePtr*	h = enumSvcs.Current();
		if ( h )
		{
			if ( (*h)->IsRunning() )
				(*h)->Stop();
			(*h)->Release();
		}
	}

	if ( m_pLibrary )
		m_pLibrary->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
bool	CServiceManager::SetApplication
		(
		CApplicationGauge* pApplication
		)
{
	m_pApplication = pApplication;
	return true;
}



/*---------------------------------------------------------------------+\

 * LoadServices -

\+---------------------------------------------------------------------*/
bool	CServiceManager::LoadServices
		(
		const char*	sName
		)
{
	Yogi::Core::CCharString		sXML;

	if ( sName )
		sXML = sName;
	else
		sXML = "default";

	ISupportsArray*	aSup;
	Yogi::Core::CCharString		sPath = "plugins/services";

	sPath += sXML;

	CMutexLocker	lock( &m_oMutex );

	m_pLibrary->SetBaseFolder( GetApplicationFolder() );

	CFactoryPlugin	plug;
	plug.SetRelativePath( "plugins/services" );
	aSup = plug.Make( sXML.Pointer(), m_pLibrary );

	if ( aSup )
	{
		ISupportsPtr*	h = aSup->PointArray();
		if ( h )
		{
			ISupportsPtr*	hEnd = h + aSup->Length();
			while ( h < hEnd )
			{
				IServicePtr	pI = QI_( *h, IService );
				if ( pI )
				{
					Yogi::Core::CCharString	sID = pI->GetID();
					if ( ! m_aList.Find( sID ) )
					{
						IApplicationUserPtr	pIApp = QI_( pI, IApplicationUser );
						if ( pIApp )
						{
							pIApp->SetApplication( m_pApplication );
							pIApp->Release();
						}
						if ( NR_SUCCEEDED( pI->Start() ) )
						{
							m_aList.Add( sID, pI );
						}
						else
						{
							LogPrint( "Failed to Start Service %s\n", sID.Pointer());
							pI->Release();
						}
					}
					else
					{
						LogPrint( "Service '%s' Already installed\n", sID.Pointer() );
						pI->Release();
					}
				}
				(*h)->Release();
				++h;
			}
		}

		delete aSup;
	}
	return true;

}


/*---------------------------------------------------------------------+\

 * StopServices -

\+---------------------------------------------------------------------*/
bool	CServiceManager::StopServices
		(
		void
		)
{
	THashTableEnumerator< Yogi::Core::CCharString, IServicePtr>
		enumSvcs = m_aList.GetEnumerator();

	while ( enumSvcs.MoveNext() )
	{
		IServicePtr*	h = enumSvcs.Current();
		if ( h )
		{
			if ( (*h)->IsRunning() )
				(*h)->Stop();
		}
	}

	return true;
}


/*---------------------------------------------------------------------+\

 * FindServiceByName -

\+---------------------------------------------------------------------*/
IServicePtr
		CServiceManager::FindServiceByName
		(
		const char* sName
		)
{
	IServicePtr		pSup = 0;
	IServicePtr*	hSup = 0;
	Yogi::Core::CCharString		tKey( sName );

	hSup = m_aList.Find( tKey );
	if ( hSup )
	{
		pSup = *hSup;
		pSup->AddRef();
	}

	return pSup;
}


/*---------------------------------------------------------------------+\

 * FindServiceByIF -

\+---------------------------------------------------------------------*/
ISupportsPtr
		CServiceManager::FindServiceByIF
		(
		ConstIXIDRef rIID
		)
{
	ISupportsPtr	pIf = 0;
	THashTableEnumerator<Yogi::Core::CCharString, IServicePtr>	tEnum = m_aList.GetEnumerator();

	while ( tEnum.MoveNext() )
	{
		IServicePtr	pSup = tEnum.Value();
		if ( pSup )
		{
			pIf = (ISupportsPtr)pSup->QueryInterface( rIID );
			if ( pIf )
				break;
		}
	}

	return pIf;
}


/*---------------------------------------------------------------------+\

 * SetLibrary -

\+---------------------------------------------------------------------*/
bool	CServiceManager::SetLibrary
		(
		ISupportsPtr pI
		)
{
	ISupportsPtr	pT = m_pLibrary;

	m_pLibrary = QI_( pI, IPluginLibrary );
	if ( pT )
		pT->Release();

	return true;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

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
