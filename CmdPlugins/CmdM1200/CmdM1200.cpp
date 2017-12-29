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
|	CmdM1200.cpp  --  brief description of what CmdM1200.cpp is for
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
	08-Jul-2010			P.Hogan			(Reviewed by: J.Griswold)
		Changed case of Stdafx.h include file for compatibility with case
		sensitive file systems (Unix/Linux). Added using graphics event namespace
		for compatibility with updated graphics events.
	17-May-2010			J.Griswold		(Reviewed by: P.Hogan)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CmdM1200.h"
#include "CApplicationGaugeVDDS.h"
#include "vdds_graphics.h"
#include "UPlatform.h"

#include "VPluginFactory.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
USING_NAMESPACE_GRAPHICS_EVENT
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
// it is important that the following extern not be nested within
//	a namespace
extern void Tx232AvalexELOCoordinates( int x, int y, VDDS_GRAPHICS_EVENT_TYPE t );

NAMESPACE_GADGET_BEGIN

/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
PLUGIN_CREATE_FACTORY( CmdM1200 );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/**--------------------------------------------------------------------+\

 * <summary>CmdM1200 - constructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  17-May-2010

\+---------------------------------------------------------------------*/
CmdM1200::CmdM1200
		(
		void
		)
		: VPluginCommand(),
		m_pVideoFeedCntl( 0 ),
		m_pDictionary( 0 ),
		m_nVideoFeedID( -1 ),
		m_nVideoSourceID( -1 ),
		m_sVideoSourceName(),
		m_selMouseX( 0 ),
		m_selMouseY( 0 ),
		m_selMouseEvent( 0 )
{
}

CmdM1200::CmdM1200
		(
		ISupportsPtr	pOwner
		)
		: VPluginCommand( pOwner ),
		m_pVideoFeedCntl( 0 ),
		m_pDictionary( 0 ),
		m_nVideoFeedID( -1 ),
		m_nVideoSourceID( -1 ),
		m_sVideoSourceName(),
		m_selMouseX( 0 ),
		m_selMouseY( 0 ),
		m_selMouseEvent( 0 )
{
}

CmdM1200::CmdM1200
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VPluginCommand( sName, pOwner ),
		m_pVideoFeedCntl( 0 ),
		m_pDictionary( 0 ),
		m_nVideoFeedID( -1 ),
		m_nVideoSourceID( -1 ),
		m_sVideoSourceName(),
		m_selMouseX( 0 ),
		m_selMouseY( 0 ),
		m_selMouseEvent( 0 )
{
}


/**--------------------------------------------------------------------+\

 * <summary>~CmdM1200 - destructor</summary>

 * <remarks/>

 * (author)J.Griswold  --  17-May-2010

\+---------------------------------------------------------------------*/
CmdM1200::~CmdM1200
		(
		void
		)
{
	if ( m_pVideoFeedCntl )
		m_pVideoFeedCntl->Release();
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/**--------------------------------------------------------------------+\

 * <summary>ConnectVideoFeed - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
NResult	CmdM1200::ConnectVideoFeed
		(
		int videoFeedID,
		int videoSourceID,
		tVideoDisplayWindow& videoFeedDisplay
		)
{
	if ( videoSourceID == m_nVideoSourceID )
	{
		m_nVideoFeedID = videoFeedID;
		m_tVideoDisplay = videoFeedDisplay;
	}
	return m_pVideoFeedCntl->ConnectVideoFeed( videoFeedID, videoSourceID, videoFeedDisplay );
}

/**--------------------------------------------------------------------+\

 * <summary>DisconnectVideoFeed - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
NResult	CmdM1200::DisconnectVideoFeed
		(
		int videoFeedID
		)
{
	if ( videoFeedID == m_nVideoFeedID )
	{
		m_nVideoFeedID = -1;
		::memset( &m_tVideoDisplay, 0, sizeof(m_tVideoDisplay) );
	}
	return m_pVideoFeedCntl->DisconnectVideoFeed( videoFeedID );
}

/**--------------------------------------------------------------------+\

 * <summary>ProcessVideoFeedCntlEvent - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
void	CmdM1200::ProcessVideoFeedCntlEvent
		(
		tVideoEvent* pEvent
		)
{
	m_pVideoFeedCntl->ProcessVideoFeedCntlEvent( pEvent );
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


/**--------------------------------------------------------------------+\

 * <summary>FindInternalInterface - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
void*	CmdM1200::FindInternalInterface
		(
		ConstIXIDRef rIID
		)
{
	void*	p = VPluginCommand::FindInternalInterface( rIID );
	if ( p )
		return p;

	if ( rIID == IXID_IVideoFeedCntl )
		return INTERFACE_THIS( IVideoFeedCntlPtr );
	else
		return 0;
}

/*----------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/**--------------------------------------------------------------------+\

 * <summary>Initialize - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
bool	CmdM1200::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	DbgPrint( "CmdM1200 - Initialize\n" );
	VPluginCommand::Initialize( pApplication, pCommandSetup );

	CApplicationGaugeVDDSPtr	pApplicationVDDS = static_cast<CApplicationGaugeVDDSPtr>(pApplication);

	if ( m_sID.Length() < 1 )
		m_sID = "Send Point External";
	pCommandSetup->RegisterCommand( m_sID );


	CVariantData	v;
	CCharString		s;

	m_pDictionary = pApplication->Dictionary();

	VDictionary::Selector	selPCVideo;
	CCharString				sTemp;

	if ( 0 < m_sVideoSourceName.Length() )
	{
		sTemp = "K:";
		sTemp += m_sVideoSourceName;
	}
	else
	{
		sTemp = "K:PC Video";
	}


	selPCVideo = m_pDictionary->LocateEntry( sTemp );
	if ( selPCVideo )
	{
		CVariantDataPtr	pv = m_pDictionary->GetData( selPCVideo );
		if ( pv )
			m_nVideoSourceID = pv->GetValueInteger();
	}

	CDrawVDDSPtr	pDraw = pApplicationVDDS->DrawVDDS();
	ISupportsPtr	pFeed = pDraw->GetVideoFeedControl();
	m_pVideoFeedCntl = QI_( pFeed, IVideoFeedCntl );
	pDraw->SetVideoFeedControl( (IVideoFeedCntlPtr)this );


	if ( m_pDictionary )
	{
		m_selMouseX = m_pDictionary->LocateEntry( "M:X" );
		m_selMouseY = m_pDictionary->LocateEntry( "M:Y" );
		m_selMouseEvent = m_pDictionary->LocateEntry( "M:Event" );
	}

	return true;
}

/**--------------------------------------------------------------------+\

 * <summary>ProcessRequest - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
bool	CmdM1200::ProcessRequest
		(
		VDictionary::Selector	,//selCommand,
		ConstCVariantDataRef	//vData
		)
{
	if ( -1 < m_nVideoFeedID )
	{
		DbgPrint( "CmdM1200 - ProcessRequest\n" );
		VDDS_GRAPHICS_EVENT_TYPE	eType = VDDS_GRAPHICS_EVENT_LAST;
		VDictionary::Selector		selWidth;
		VDictionary::Selector		selHeight;

		int		nViewLeft	= m_tVideoDisplay.xPosition;
		int		nViewTop	= m_tVideoDisplay.yPosition;
		int		nViewWidth	= m_tVideoDisplay.nWidth;
		int		nViewHeight	= m_tVideoDisplay.nHeight;

		if ( 0 < nViewWidth  &&  0 < nViewHeight )
		{
			int		x = 0;
			int		y = 0;
			int		w = 0;
			int		h = 0;
			CCharString		sWidthName;
			CCharString		sHeightName;
			CVariantDataPtr	pv;

			sWidthName.Format( "D:Video Feed %d.Width", m_nVideoFeedID+1 );
			sHeightName.Format( "D:Video Feed %d.Height", m_nVideoFeedID+1 );

			selWidth = m_pDictionary->LocateEntry( sWidthName );
			selHeight = m_pDictionary->LocateEntry( sHeightName );

			pv = m_pDictionary->GetData( selWidth );
			if ( pv )
				w = pv->GetValueInteger();

			pv = m_pDictionary->GetData( selHeight );
			if ( pv )
				h = pv->GetValueInteger();


			pv = m_pDictionary->GetData( m_selMouseX );
			if ( pv )
				x = pv->GetValueInteger();
			pv = m_pDictionary->GetData( m_selMouseY );
			if ( pv )
				y = pv->GetValueInteger();


			if ( 0 < w  &&  0 < h )
			{

				CCharString	sEvent;
				pv = m_pDictionary->GetData( m_selMouseEvent );
				if ( pv )
					sEvent = pv->GetValueCCharString();
				if ( sEvent == "Down" )
					eType = VDDS_GRAPHICS_EVENT_MOUSE_DOWN;
				else if ( sEvent == "Up" )
					eType = VDDS_GRAPHICS_EVENT_MOUSE_UP;
				else if ( sEvent == "Drag" )
					eType = VDDS_GRAPHICS_EVENT_MOUSE_MOVE;

			// todo: calculate transform
				bool	bProcess = true;

				if ( nViewLeft+nViewWidth < x )
					bProcess = false;
				else if ( nViewTop+nViewHeight < y )
					bProcess = false;
				else if ( x < nViewLeft )
					bProcess = false;
				else if ( y < nViewTop )
					bProcess = false;
				if ( bProcess )
				{

					GFLOAT	xScale = (GFLOAT)w / (GFLOAT)nViewWidth;
					GFLOAT	yScale = (GFLOAT)h / (GFLOAT)nViewHeight;

					x = int(GFLOAT(x - nViewLeft) * xScale);
					y = int(GFLOAT(y - nViewTop) * yScale);

					::Tx232AvalexELOCoordinates( x, y, eType );

				}
			}
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

 * (author)J.Griswold  --  16-May-2010

\+---------------------------------------------------------------------*/
bool	CmdM1200::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = VPluginCommand::Load( pConfig, pLib );
	if ( bResult )
	{
		DbgPrint( "CmdM1200 - Load\n" );
		m_sVideoSourceName = pConfig->GetParameterAsString( "Video Source", "PC Video" );
	}

	return bResult;
}



NAMESPACE_GADGET_END


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

 * (author)J.Griswold  --  17-May-2010

\+---------------------------------------------------------------------*/

