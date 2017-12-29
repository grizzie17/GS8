/*---------------------------------------------------------------------+\
|
|	VPluginWithAggregateList.cpp  --  brief description of what VPluginWithAggregateList.cpp is for
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
	22-Jul-2010			J.Griswold		(Reviewed by: J.Griswold)
		Removed copying string data for debug prints
	29-Jun-2010			J.Griswold		(Reviewed by: PJH)
		was not incrementing pointer in the destructor or FindExternalInterface
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
#include "VPluginWithAggregateList.h"

#include "LogFile.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define VPLUGIN_AGGREGATE_LIST_DBG_PRINT

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

 * VPluginWithAggregateList - constructor

\+---------------------------------------------------------------------*/
VPluginWithAggregateList::VPluginWithAggregateList
		(
		void
		)
		: inherited(),
		m_aAggregateList()
{
}


VPluginWithAggregateList::VPluginWithAggregateList
		(
		ISupportsPtr pOwner
		)
		: inherited( pOwner ),
		m_aAggregateList()
{
}

VPluginWithAggregateList::VPluginWithAggregateList
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_aAggregateList()
{
}





/*---------------------------------------------------------------------+\

 * ~VPluginWithAggregateList - destructor

\+---------------------------------------------------------------------*/
VPluginWithAggregateList::~VPluginWithAggregateList
		(
		void
		)
{
	ISupportsPtr*	h = m_aAggregateList.PointArray();
	if ( h )
	{
		ISupportsPtr*	hEnd = h + m_aAggregateList.Length();
		while ( h < hEnd )
		{
			if ( *h )
				(*h)->Release();
			++h;
		}
	}
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
void*	VPluginWithAggregateList::FindExternalInterface
		(
		ConstIXIDRef	rIID,
		NResultPtr		pResult
		)
{
	NResult	nr = 0;
	void*	pI = inherited::FindExternalInterface( rIID, &nr );
	if ( ! pI )
	{

		ISupportsPtr*	h = m_aAggregateList.PointArray();
		if ( h )
		{
			ISupportsPtr*	hEnd = h + m_aAggregateList.Length();
			while ( h < hEnd )
			{
				if ( *h )
				{
					pI = (*h)->QueryInterface( rIID, &nr );
					if ( pI )
						break;
				}
				++h;
			}
		}
	}

	if ( pResult )
		*pResult = nr;

	return pI;
}



/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	VPluginWithAggregateList::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		VPluginConfiguration::FolderEnum tFolder = pConfig->GetFolderEnum();
		while ( tFolder.MoveNext() )
		{
			VPluginConfigurationPtr	pSubConfig;

			pSubConfig = tFolder.Value();
			if ( pSubConfig )
			{
				CCharString	sClass = pSubConfig->GetClass();
				CCharString	sGroup = pSubConfig->GetGroup();
				CCharString	sID = pSubConfig->GetID();

				pLib->SetRelativeFolder( sGroup.Pointer() );

#ifdef VPLUGIN_AGGREGATE_LIST_DBG_PRINT
				DbgPrint("VPluginWithAggregateList.Load: Creating class '%s', ID '%s'\n",
					     sClass.Pointer(), sID.Pointer());
#endif

				ISupportsPtr pSup = pLib->Create( sClass, GetOwner() );
				if ( pSup )
				{
					IPluginLoadConfigurationPtr	pLoad;

					pLoad = (IPluginLoadConfigurationPtr)
							pSup->QueryInterface( IXID_IPluginLoadConfiguration, 0 );
					if ( pLoad )
					{
						if ( pLoad->Load( pSubConfig, pLib ) )
						{
							m_aAggregateList.AppendData( &pSup );
						}
						else
						{
							bResult = false;
						}
						pLoad->Release();
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

