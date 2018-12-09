/*---------------------------------------------------------------------+\
|																		|
|	Copyright 2010 DRS Test & Energy Management LLC						|
|	All Rights Reserved													|
|																		|
|	Including software, file formats, and audio-visual displays;		|
|	may only be used pursuant to applicable software license			|
|	agreement; contains confidential and proprietary information of		|
|	DRS-TEM and/or third parties which is protected by copyright		|
|	and trade secret law and may not be provided or otherwise made		|
|	available without proper authorization.								|
|																		|
|	Unpublished -- rights reserved under the Copyright Laws of the		|
|	United States.														|
|																		|
|	DRS Test & Energy Management LLC									|
|	110 Wynn Drive, P.O. Box 1929, Huntsville, AL 35805					|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	CCmdVcb.cpp  --  brief description of what CCmdVcb.cpp is for
|
|	Purpose:
|	File Custodian:		R.Hosea
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
	08-Jul-2010			R.Hosea		(Reviewed by: S.Snider)
		Initial Revision, unable to unit test because of lack of menu control
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CCmdVcb.h"
#include "CApplicationGaugeVDDS.h"
#include "vdds_graphics.h"
#include "UPlatform.h"

#include "VPluginFactory.h"
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

namespace Yogi { namespace Gadget {

/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
PLUGIN_CREATE_FACTORY( CCmdVcb );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CCmdVcb - constructor</summary>

 * <remarks/>

 * (author)R.Hosea  --  17-May-2010

\+---------------------------------------------------------------------*/
CCmdVcb::CCmdVcb
		(
		void
		)
		: VPluginCommand(),
		m_pDataStream( 0 ),
		m_cBackLight( 0 )
{
}

CCmdVcb::CCmdVcb
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner ),
		m_pDataStream( 0 ),
		m_cBackLight( 0 )
{
}

CCmdVcb::CCmdVcb
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner ),
		m_pDataStream( 0 ),
		m_cBackLight( 0 )
{
}


/**--------------------------------------------------------------------+\

 * <summary>~CCmdVcb - destructor</summary>

 * <remarks/>

 * (author)R.Hosea  --  17-May-2010

\+---------------------------------------------------------------------*/
CCmdVcb::~CCmdVcb
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


/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - brief statement</summary>

 * <remarks/>

 * (author)R.Hosea  --  30-Jun-2010

\+---------------------------------------------------------------------*/
void*	CCmdVcb::FindInternalInterface
		(
		ConstIXIDRef rIID
		)
{
	void*	p = VPluginCommand::FindInternalInterface( rIID );
	if ( p )
	{
		return p;

	}
	else if ( rIID == IXID_IPluginLoadConfiguration )
	{
		p = (IPluginLoadConfigurationPtr)(this);
	}
	else if ( rIID == IXID_ICommandPlugin )
	{
		return INTERFACE_THIS( ICommandPluginPtr );
	}
	else if ( rIID == IXID_IDataStream )
	{
		return reinterpret_cast<ISupportsPtr>( static_cast<IDataStreamPtr>( m_pDataStream ) );
	}

 	return 0;
}

/*----------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/**--------------------------------------------------------------------+\

 * <summary>Initialize - brief statement</summary>

 * <remarks/>

 * (author)R.Hosea  --  30-Jun-2010

\+---------------------------------------------------------------------*/
bool	CCmdVcb::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	DbgPrint( "CCmdVcb - Initialize\n" );
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	CApplicationGaugeVDDSPtr	pApplicationVDDS = static_cast<CApplicationGaugeVDDSPtr>(pApplication);
    CDictPageFunctionsPtr	pFunc = pApplicationVDDS->DictPageFunctions();
	VDictionaryPtr	pDict;

	pDict = pApplicationVDDS->Dictionary();
	if ( pFunc )
	{
		CVariantData	v;

		v = false;
		pFunc->AddEntry( "Back Light", v );
		m_cBackLight = pDict->LocateEntry( "C:Back Light" );

		//may need K page entries for on/off values


	}


	if ( m_sID.Length() < 1 )
		m_sID = "Send Back Light";

	pCommandSetup->RegisterCommand( m_sID );

	m_pDataStream = static_cast<IDataStreamPtr>(QueryInterface( IXID_IDataStream, 0 ));
	if(m_pDataStream)
		m_pDataStream->Release();


	if(m_pDataStream)
		m_pDataStream->Write((void*)'l', 1);

	return true;
}

/**--------------------------------------------------------------------+\

 * <summary>ProcessRequest - brief statement</summary>

 * <remarks/>

 * (author)R.Hosea  --  30-Jun-2010

\+---------------------------------------------------------------------*/
bool	CCmdVcb::ProcessRequest
		(
		VDictionary::Selector	selCommand,//selCommand,
		ConstCVariantDataRef vData
		)
{

	if (selCommand == m_cBackLight )
    {//may need to set D page values
		if(vData == 0L)
		{
			if(m_pDataStream->Write((void*)'l', 1) <= 0)
				m_pGraphicsEvent->SendUserInputDeviceStatusEvent
				( DEVICE_COMM_ERROR, 0 );
        }
		else
		{
			if(m_pDataStream->Write((void*)'L', 1) <= 0)
				m_pGraphicsEvent->SendUserInputDeviceStatusEvent
				( DEVICE_COMM_ERROR, 0 );

		}
	}

	return true;
}

/*----------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/**--------------------------------------------------------------------+\

 * <summary>Load - brief statement</summary>

 * <remarks/>

 * (author)R.Hosea  --  30-Jun-2010

\+---------------------------------------------------------------------*/
bool	CCmdVcb::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );
	if ( bResult )
	{
		DbgPrint( "CCmdVcb - Load\n" );
	}

	return bResult;
}



}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)R.Hosea  --  17-May-2010

\+---------------------------------------------------------------------*/
