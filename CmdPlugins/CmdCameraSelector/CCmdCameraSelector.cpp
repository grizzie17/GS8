/*---------------------------------------------------------------------+\
|
|	CCmdCCmdCameraSelector.cpp  --  Plugin used to determine camera selections based on
|							VCB input
|
|	Purpose:
|	File Custodian:		S.Snider
|
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
	20-Sep-2010			J.Griswold		(Reviewed by: S.Graham) [2]
		Reworked to make compatible with Workbench
		Also remove hardcoded up, down, left, right values.
	12-Jul-2010			S.Snider		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CCmdCameraSelector.h"

#include "LogFile.h"
#include "VPluginFactory.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


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
PLUGIN_CREATE_FACTORY( CCmdCameraSelector );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CCmdCameraSelector - constructor

\+---------------------------------------------------------------------*/
CCmdCameraSelector::CCmdCameraSelector
		(
		void
		)
		: VPluginCommand()
		, m_sName()
		, m_selCEditCamera()
		, m_pagDEditCamera()
		, m_pagDCameraSelector()
		, m_selUCurrentVideoFeed()
		, m_aList()
		, m_aTransitions()

{
}

CCmdCameraSelector::CCmdCameraSelector
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner )
		, m_sName()
		, m_selCEditCamera()
		, m_pagDEditCamera()
		, m_pagDCameraSelector()
		, m_selUCurrentVideoFeed()
		, m_aList()
		, m_aTransitions()
{
}

CCmdCameraSelector::CCmdCameraSelector
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner )
		, m_sName()
		, m_selCEditCamera()
		, m_pagDEditCamera()
		, m_pagDCameraSelector()
		, m_selUCurrentVideoFeed()
		, m_aList()
		, m_aTransitions()
{
}


/*---------------------------------------------------------------------+\

 * ~CCmdCameraSelector - destructor

\+---------------------------------------------------------------------*/
CCmdCameraSelector::~CCmdCameraSelector
		(
		void
		)
{
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
/*----------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CCmdCameraSelector::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{

//	long			id;
	ConstCVariantDataPtr	pv;

	LOCAL_PRINT("CCmdCameraSelector::Initialize\n");

	if ( ! VPluginCommand::Initialize( pApplication, pCommandSetup ) )
	{
		return false;
	}

	// Create the command. There will be an instance of this class
	// for each camera, so create the command name by using the camera name.
	CCharString commandName;
	commandName.Format("Selector %s", m_sName.Pointer());
	pCommandSetup->RegisterCommand(commandName);


	m_pDictionary = pApplication->Dictionary();

	CVariantData	v;
	CVariantData	vt;	// temporary
	CCharString		s;
	long			nValue;
	THashTableEnumerator<CCharString, CVariantData>	eLst = m_aList.GetEnumerator();
	long			nID;

	while ( eLst.MoveNext() )
	{
		s = eLst.Key();
		v = eLst.Value();

		nValue = 0;

		// find the "K" entry or create if it doesn't exist
		nID = m_pConstantsPage->LocateEntry( s );
		if ( nID < 0 )
		{
			vt = 0L;
			m_pConstantsPage->AddEntry( s, vt );
			nID = m_pConstantsPage->LocateEntry( s );
			nValue =  nID | 0x010000L;	// just to be unique
			vt = nValue;
			m_pConstantsPage->UpdateEntry( (unsigned long)nID, vt );
		}
		else
		{
			pv = m_pConstantsPage->GetData( (unsigned long)nID );
			if ( pv )
				nValue = pv->GetValueInteger();
		}

		CDictPageSelector	spCam;
		spCam.SetName( v.GetValueString() );

		m_aTransitions.Add( nValue, spCam );
	}


	m_selCEditCamera.SetName( "C:Edit Camera" );
	m_pagDEditCamera.SetName( "Edit Camera" );
	m_pagDCameraSelector.SetName( "Camera Selector" );
	m_selUCurrentVideoFeed.SetName( "U:Current Video Feed" );


	return true;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest - Process VCB Camera selection inputs

\+---------------------------------------------------------------------*/
bool	CCmdCameraSelector::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	vDataRef
		)
{

	LOCAL_PRINT("CCmdCameraSelector::ProcessRequest\n");

	CVariantData	vData = vDataRef;
	long			button = vData;
	CCharString		sVideoFeed;

	CVariantDataPtr	pv;
	CVariantData	v;
	VDictionary::Selector	sel = 0;
	long			nPage;

	long			nNewCam = 0;
	ConstCVariantDataPtr	pvNewCam = 0;

	const CDictPageSelector*	pPSel;
	pPSel = m_aTransitions.Find( button );
	if ( pPSel )
	{
		LOCAL_PRINT("CCmdCameraSelector::Button found\n");
		nNewCam = (long)pPSel->GetSelector( m_pConstantsPage );
		LOCAL_PRINT("CCmdCameraSelector::nNewCam %d\n", nNewCam);
		if ( -1 < nNewCam )
			pvNewCam = m_pConstantsPage->GetData( (unsigned long)nNewCam );

		if ( pvNewCam )
		{
			LOCAL_PRINT("CCmdCameraSelector::New camera found\n");
			// D:Camera Selector
			nPage = (long)m_pagDCameraSelector.GetSelector( m_pDataPage );
			if ( -1 < nPage )
			{
				v = *pPSel->Name();
				m_pDataPage->UpdateEntry( (unsigned long)nPage, v );
			}

			// issue the command for "C:Edit Camera"
			sel = m_selCEditCamera.GetSelector( m_pDictionary );
			if ( sel )
				m_pDictionary->PutData( sel, pvNewCam );

			// U:Current Video Feed
			sel = m_selUCurrentVideoFeed.GetSelector( m_pDictionary );
			if ( sel )
			{
				CCharString	sFeedName;
				pv = m_pDictionary->GetData( sel );
				if ( pv )
				{
					CCharString	sUFeed;
					sFeedName = pv->GetValueCCharString();

					// U:Video Feed #
					sUFeed.Format( "U:%s", sFeedName.Pointer() );
					sel = m_pDictionary->LocateEntry( sUFeed );
					if ( sel )
					{
						m_pDictionary->PutData( sel, pvNewCam );
					}

					sVideoFeed.Format("U:Feed %c Position", sFeedName.AtIndex((index_t)sFeedName.Length() -1));
					sel = m_pDictionary->LocateEntry(sVideoFeed);
					m_pDictionary->PutData( sel, pvNewCam );
				}
			}
		} else
		{
			LOCAL_PRINT("CCmdCameraSelector::New camera not found\n");
		}

	} else
	{
		LOCAL_PRINT("CCmdCameraSelector::Did not find button: %d\n", button);
	}

	return true;
}

/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load - Load camera selector

\+---------------------------------------------------------------------*/
bool	CCmdCameraSelector::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );
	if ( bResult )
	{

		LOCAL_PRINT("CCmdCameraSelector::Load\n");

		// get the name of "this" camera
		IPlugin* pi = QI_(this, IPlugin);
		if ( pi )
		{
			m_sName = pi->ID();;
			pi->Release();
		}
		else
		{
			m_sName = "Default Camera";
		}

		// save off our list so we can use it in the initialize function
		CVariantData	v;
		CCharString		s;
		VPluginConfiguration::ParamEnum	eCfg = pConfig->GetParamEnum();

		while ( eCfg.MoveNext() )
		{
			v = eCfg.Value();
			s = eCfg.Key();

			m_aList.Add( s, v );

			LOCAL_PRINT("Key: %s", s.Pointer());
		}

	}

	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
