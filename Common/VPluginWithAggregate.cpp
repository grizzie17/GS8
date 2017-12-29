/*---------------------------------------------------------------------+\
|
|	VPluginWithAggregate.cpp  --  brief description of what VPluginWithAggregate.cpp is for
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	04-Jul-2010			J.Griswold		(Reviewed by: PJH) [1]
		Added use of TIP (template interface pointer)
	07-Jun-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VPluginWithAggregate.h"
#include "TComPointer.h"

#include "LogFile.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define VPLUGIN_AGGREGATE_DBG_PRINT

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMON_BEGIN
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

 * VPluginWithAggregate - constructor

\+---------------------------------------------------------------------*/
VPluginWithAggregate::VPluginWithAggregate
		(
		void
		)
		: VPlugin(),
		m_pAggregate( 0 )
{
}


VPluginWithAggregate::VPluginWithAggregate
		(
		ISupportsPtr pOwner
		)
		: VPlugin( pOwner ),
		m_pAggregate( 0 )
{
}

VPluginWithAggregate::VPluginWithAggregate
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPlugin( sName, pOwner ),
		m_pAggregate( 0 )
{
}





/*---------------------------------------------------------------------+\

 * ~VPluginWithAggregate - destructor

\+---------------------------------------------------------------------*/
VPluginWithAggregate::~VPluginWithAggregate
		(
		void
		)
{
	if ( m_pAggregate )
		m_pAggregate->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


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

/*---------------------------------------------------------------------+\

 * FindExternalInterface -

\+---------------------------------------------------------------------*/
void*	VPluginWithAggregate::FindExternalInterface
		(
		ConstIXIDRef	rIID,
		NResultPtr		pResult
		)
{
	NResult	nr = 0;
	void*	pI = VPlugin::FindExternalInterface( rIID, &nr );
	if ( ! pI )
	{
		if ( m_pAggregate )
			pI = m_pAggregate->QueryInterface( rIID, &nr );

	}
	if ( pResult )
		*pResult = nr;

	return pI;
}



/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	VPluginWithAggregate::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPlugin::Load( pConfig, pLib );
	if ( bResult )
	{
		VPluginConfiguration::FolderEnum	tFolder = pConfig->GetFolderEnum();
		if ( tFolder.MoveNext() )
		{
			VPluginConfigurationPtr	pSubFolder = tFolder.Value();
			if ( pSubFolder )
			{
				CCharString	sClass = pSubFolder->GetClass();
				CCharString	sGroup = pSubFolder->GetGroup();
				CCharString	sID = pSubFolder->GetID();

				pLib->SetRelativeFolder( sGroup.Pointer() );

#ifdef VPLUGIN_AGGREGATE_DBG_PRINT
				DbgPrint("VPluginWithAggregate.Load: Creating class '%s', ID '%s'\n",
					     sClass.Pointer(), sID.Pointer());
#endif
				m_pAggregate = pLib->Create( sClass, GetOwner() );
				if ( m_pAggregate )
				{
					TIP(IPluginLoadConfiguration)	pLoad( m_pAggregate );

					if ( pLoad )
					{
						pLoad->Load( pSubFolder, pLib );
					}
				}
			}
		}
	}

	return bResult;
}




NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

