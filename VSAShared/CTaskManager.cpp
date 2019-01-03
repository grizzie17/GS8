/*---------------------------------------------------------------------+\
|
|	CTaskManager.cpp  --  brief description of what CCommandProcessor.cpp is for
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
#include "Stdafx.h"
#include "CTaskManager.h"

#include "CFactoryPlugin.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
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

 * CTaskManager - constructor

\+---------------------------------------------------------------------*/
CTaskManager::CTaskManager
		(
		void
		)
		: m_aList(),
		m_pLibrary( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CTaskManager - destructor

\+---------------------------------------------------------------------*/
CTaskManager::~CTaskManager
		(
		void
		)
{
	TArrayEnumerator< ITaskPtr>
			enumTasks = m_aList.GetEnumerator();

	while ( enumTasks.MoveNext() )
	{
		const ITaskPtr*	h = enumTasks.Current();
		if ( h )
		{
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

 * InitializeFunctions -

\+---------------------------------------------------------------------*/
bool	CTaskManager::LoadTasks
		(
		char*	sName
		)
{
	Yogi::Core::CCharString		sXML;

	if ( sName )
		sXML = sName;
	else
		sXML = "default";

	ISupportsArray*	aSup;
	Yogi::Core::CCharString		sPath = "plugins/tasks";

	sPath += sXML;


	m_pLibrary->SetBaseFolder( GetApplicationFolder() );

	CFactoryPlugin	plug;
	plug.SetRelativePath( "plugins/tasks" );
	aSup = plug.Make( sXML.Pointer(), m_pLibrary );

	if ( aSup )
	{
		ISupportsPtr*	h = aSup->PointArray();
		if ( h )
		{
			ISupportsPtr*	hEnd = h + aSup->Length();
			while ( h < hEnd )
			{
				ITaskPtr	pI = QI_( *h, ITask );
				if ( pI )
				{
					if ( NR_SUCCEEDED( pI->Start() ) )
					{
						m_aList.AppendData( &pI );
					}
					else
					{
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


bool	CTaskManager::SetLibrary
		(
		ISupportsPtr pI
		)
{
	m_pLibrary = QI_( pI, IPluginLibrary );
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
