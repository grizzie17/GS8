/*---------------------------------------------------------------------+\
|
|	CmdEptm.cpp  --  Plugin to process touch screen points
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	18-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "stdafx.h"
#include "CmdEptm.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UFloat.h"
#include "CApplicationGauge.h"
#include "CScreen.h"
#include "CGauge.h"
#include "CFactoryPanel.h"
#include "CFactoryGauge.h"
#include "CServiceManager.h"

#include "VPluginFactory.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

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
PLUGIN_CREATE_FACTORY( CmdEptm );




/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CmdEptm - constructor

\+---------------------------------------------------------------------*/
CmdEptm::CmdEptm
		(
		void
		)
		: inherited(),
		m_pIPanAndTilt( 0 ),
		m_pDictionary( 0 ),
		m_nCmdJoystickStart( 0 ),
		m_nCmdJoystickMove( 0 ),
		m_nCmdJoystickStop( 0 ),
		m_nUJoystickOriginX( 0 ),
		m_nUJoystickOriginY( 0 ),
		m_nUJoystickRadius( 0 ),
		m_oMutex()
{
}

CmdEptm::CmdEptm
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_pIPanAndTilt( 0 ),
		m_pDictionary( 0 ),
		m_nCmdJoystickStart( 0 ),
		m_nCmdJoystickMove( 0 ),
		m_nCmdJoystickStop( 0 ),
		m_nUJoystickOriginX( 0 ),
		m_nUJoystickOriginY( 0 ),
		m_nUJoystickRadius( 0 ),
		m_oMutex()
{
}

CmdEptm::CmdEptm
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_pIPanAndTilt( 0 ),
		m_pDictionary( 0 ),
		m_nCmdJoystickStart( 0 ),
		m_nCmdJoystickMove( 0 ),
		m_nCmdJoystickStop( 0 ),
		m_nUJoystickOriginX( 0 ),
		m_nUJoystickOriginY( 0 ),
		m_nUJoystickRadius( 0 ),
		m_oMutex()
{
}



/*---------------------------------------------------------------------+\

 * ~CmdEptm - destructor

\+---------------------------------------------------------------------*/
CmdEptm::~CmdEptm
		(
		void
		)
{
	if ( m_pIPanAndTilt )
	{
		m_pIPanAndTilt->UnregisterClient( (IPanAndTiltClientPtr)INTERFACE_THIS( IPanAndTiltClientPtr ) );
		m_pIPanAndTilt->Release();
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


NResult	CmdEptm::EptmState
		(
		GFLOAT	fPan,
		GFLOAT	fTilt,
		long	mFlags
		)
{
	CVariantData	v;

	CMutexLocker	lock( &m_oMutex );

	m_fPan = fPan;
	//v = m_fPan;
	//m_pDictionary->PutData( m_nUEPTMPositionX, &v );

	m_fTilt = fTilt;
	//v = m_fTilt;
	//m_pDictionary->PutData( m_nUEPTMPositionY, &v );

	m_mFlags = mFlags;
	//v = m_mFlags;
	//m_pDictionary->PutData( m_nUEPTMFlags, &v );

	m_bDirty = true;

	return NR_S_SUCCESS;
}





/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


bool	CmdEptm::JoystickStart
		(
		ConstCVariantDataRef
		)
{
	CVariantDataPtr	pv;

	pv = m_pDictionary->GetData( m_nUJoystickOriginX );
	if ( pv )
		m_tCenter.x = *pv;

	pv = m_pDictionary->GetData( m_nUJoystickOriginY );
	if ( pv )
		m_tCenter.y = *pv;

	pv = m_pDictionary->GetData( m_nUJoystickRadius );
	if ( pv )
		m_nRadius = *pv;

	long	x = 0;
	long	y = 0;

	pv = m_pDictionary->GetData( m_nIX );
	if ( pv )
		x = *pv;

	pv = m_pDictionary->GetData( m_nIY );
	if ( pv )
		y = *pv;

	GFLOAT	dx;
	GFLOAT	dy;
	GFLOAT	fLen;		// length of vector

	dx = GFLOAT(x - m_tCenter.x);
	dy = GFLOAT(y - m_tCenter.y);

	GFLOAT	ax = fabs(dx);
	GFLOAT	ay = fabs(dy);

	// calculate the vector length
	if ( ax < GFLOAT_EPSILON )
	{
		fLen = GFLOAT(ay);
	}
	else if ( ay < GFLOAT_EPSILON )
	{
		fLen = GFLOAT(ax);
	}
	else
	{
		fLen = ::sqrt( dx * dx  +  dy * dy );
	}

	if ( m_nRadius < fLen )
	{
		dx = GFLOAT_0;
		dy = GFLOAT_0;
		m_bActive = false;
	}
	else
	{
		m_bActive = true;
		SendJoystick( dx, dy );
	}


	CVariantData	v;
	v = dx;
	m_pDictionary->PutData( m_nUJoystickPositionX, &v );

	v = dy;
	m_pDictionary->PutData( m_nUJoystickPositionY, &v );



	return true;
}


bool	CmdEptm::JoystickMove
		(
		ConstCVariantDataRef
		)
{
	if ( m_bActive )
	{
		long	x = 0;
		long	y = 0;
		CVariantDataPtr	pv;

		pv = m_pDictionary->GetData( m_nIX );
		if ( pv )
			x = *pv;

		pv = m_pDictionary->GetData( m_nIY );
		if ( pv )
			y = *pv;

		GFLOAT	dx;
		GFLOAT	dy;
		GFLOAT	fLen;		// length of vector

		dx = GFLOAT(x - m_tCenter.x);
		dy = GFLOAT(y - m_tCenter.y);

		GFLOAT	ax = fabs(dx);
		GFLOAT	ay = fabs(dy);

		// calculate the vector length
		if ( ax < GFLOAT_EPSILON )
		{
			fLen = GFLOAT(ay);
		}
		else if ( ay < GFLOAT_EPSILON )
		{
			fLen = GFLOAT(ax);
		}
		else
		{
			fLen = ::sqrt( dx * dx  +  dy * dy );
		}

		if ( m_nRadius < fLen )
		{
			// calculate the intersection point
			dx = dx / fLen * GFLOAT(m_nRadius);
			dy = dy / fLen * GFLOAT(m_nRadius);
		}

		CVariantData	v;

		SendJoystick( dx, dy );

		v = dx;
		m_pDictionary->PutData( m_nUJoystickPositionX, &v );

		v = dy;
		m_pDictionary->PutData( m_nUJoystickPositionY, &v );



	}
	return true;
}


bool	CmdEptm::JoystickStop
		(
		ConstCVariantDataRef
		)
{

	CVariantData	v = 0L;

	m_pDictionary->PutData( m_nUJoystickPositionX, &v );
	m_pDictionary->PutData( m_nUJoystickPositionY, &v );

	if ( m_bActive )
	{
		SendJoystick( GFLOAT_0, GFLOAT_0 );
		m_bActive = false;
	}

	return true;
}


bool	CmdEptm::AutoPanStart
		(
		ConstCVariantDataRef //r
		)
{
	if ( m_pIPanAndTilt )
		m_pIPanAndTilt->AutoPan( m_fPanLeft, m_fTiltTop, m_fPanRight, m_fTiltBottom, m_fPanSpeed );
	return true;
}


bool	CmdEptm::AutoPanStop
		(
		ConstCVariantDataRef //r
		)
{
	SendJoystick( GFLOAT_0, GFLOAT_0 );
	return true;
}


bool	CmdEptm::AutoPanDefineLeft
		(
		ConstCVariantDataRef //r
		)
{
	m_fPanLeft = m_fPan;
	m_fTiltTop = m_fTilt;
	return true;
}

bool	CmdEptm::AutoPanDefineRight
		(
		ConstCVariantDataRef //r
		)
{
	m_fPanRight = m_fPan;
	m_fTiltBottom = m_fTilt;
	return true;
}


bool	CmdEptm::AutoPanChangeSpeed
		(
		ConstCVariantDataRef r
		)
{
	GFLOAT	f = r.GetValueFloat();
	m_fPanSpeed += f;
	m_fPanSpeed = umin( umax( m_fPanSpeed, GFLOAT_0 ), GFLOAT_1 );
	if ( m_pIPanAndTilt )
		m_pIPanAndTilt->AutoPan( m_fPanLeft, m_fTiltTop, m_fPanRight, m_fTiltBottom, m_fPanSpeed );
	return true;
}


bool	CmdEptm::EPTMCalculate
		(
		ConstCVariantDataRef	//r
		)
{
	CVariantData	v;

	if ( m_bDirty )
	{
		CMutexLocker	lock( &m_oMutex );

		v = m_fPan;
		m_pDictionary->PutData( m_nUEPTMPositionX, &v );

		v = m_fTilt;
		m_pDictionary->PutData( m_nUEPTMPositionY, &v );

		v = m_mFlags;
		m_pDictionary->PutData( m_nUEPTMFlags, &v );

		m_bDirty = false;
	}

	return true;
}


bool	CmdEptm::EPTMHome
		(
		ConstCVariantDataRef //r
		)
{
	if ( m_pIPanAndTilt )
		m_pIPanAndTilt->MoveHome();
	return true;
}


bool	CmdEptm::EPTMSetHome
		(
		ConstCVariantDataRef //r
		)
{
	if ( m_pIPanAndTilt )
		m_pIPanAndTilt->SetHome();
	return true;
}


bool	CmdEptm::EPTMSlew
		(
		ConstCVariantDataRef //r
		)
{
	long	x = 0;
	long	y = 0;
	long	w = 0;
	long	h = 0;
	CVariantDataPtr	pv;

	pv = m_pDictionary->GetData( m_nIX );
	if ( pv )
		x = *pv;

	pv = m_pDictionary->GetData( m_nIY );
	if ( pv )
		y = *pv;

	pv = m_pDictionary->GetData( m_nSScreenWidth );
	if ( pv )
		w = *pv;


	pv = m_pDictionary->GetData( m_nSScreenHeight );
	if ( pv )
		h = *pv;


	GFLOAT	p;
	GFLOAT	t;

	GFLOAT	fw = 40.0f;		// field of view
	GFLOAT	fh = fw * 0.75f;


	p = (GFLOAT)x / (GFLOAT)w * fw - (fw / 2.0f) + m_fSlewCenterX;
	t = (fh / 2.0f) - (GFLOAT)y / (GFLOAT)h * fh  + m_fSlewCenterY;


	if ( m_pIPanAndTilt )
		m_pIPanAndTilt->MoveAbsolute( p, t, 0.75f );


	return true;
}


bool	CmdEptm::EPTMSetSlewCenter
		(
		ConstCVariantDataRef //r
		)
{
	m_fSlewCenterX = m_fPan;
	m_fSlewCenterY = m_fTilt;

	return true;
}





bool	CmdEptm::SendJoystick
		(
		GFLOAT x,
		GFLOAT y
		)
{
	x /= GFLOAT( m_nRadius );
	y /= GFLOAT( m_nRadius );
	if ( m_pIPanAndTilt )
	{
		m_pIPanAndTilt->MoveViaSpeed( x, -y );
		//DbgPrint( "SendJoystick: p=%f, t=%f\n", x, y );
	}
	return true;
}





/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CmdEptm::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		pI = 0;
	}

	return pI;
}


void	CmdEptm::FinalRelease
		(
		void
		)
{
	inherited::FinalRelease();
}




/*---------------------------------------------------------------------+\
|	ICommandPlugin
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Initialize -

\+---------------------------------------------------------------------*/
bool	CmdEptm::Initialize
		(
		CApplicationGaugePtr	pApplication,
		VCommandSetupPtr		pCommandSetup
		)
{
	bool	bResult = inherited::Initialize( pApplication, pCommandSetup );
	if ( bResult )
	{

		m_nCmdJoystickStart = pCommandSetup->RegisterCommand( "JOYSTICK START" );
		m_nCmdJoystickMove = pCommandSetup->RegisterCommand( "JOYSTICK MOVE" );
		m_nCmdJoystickStop = pCommandSetup->RegisterCommand( "JOYSTICK STOP" );

		m_nCmdAutoPanStart = pCommandSetup->RegisterCommand( "AUTOPAN START" );
		m_nCmdAutoPanStop = pCommandSetup->RegisterCommand( "AUTOPAN STOP" );
		m_nCmdAutoPanDefineLeft = pCommandSetup->RegisterCommand( "AUTOPAN DEFINE LEFT" );
		m_nCmdAutoPanDefineRight = pCommandSetup->RegisterCommand( "AUTOPAN DEFINE RIGHT" );
		m_nCmdAutoPanChangeSpeed = pCommandSetup->RegisterCommand( "AUTOPAN CHANGE SPEED" );

		m_nCmdEptmCalculate = pCommandSetup->RegisterCommand( "EPTM CALCULATE" );

		m_nCmdEptmHome = pCommandSetup->RegisterCommand( "EPTM HOME" );
		m_nCmdEptmSetHome = pCommandSetup->RegisterCommand( "EPTM SET HOME" );

		m_nCmdEptmSlew = pCommandSetup->RegisterCommand( "EPTM SLEW" );
		m_nCmdEptmSetSlewCenter = pCommandSetup->RegisterCommand( "EPTM SET SLEW CENTER" );


		m_pDictionary = m_pApplication->Dictionary();
		if ( m_pDictionary )
		{
			m_nUJoystickOriginX = m_pDictionary->LocateEntry( "U:JOYSTICK ORIGIN X" );
			m_nUJoystickOriginY = m_pDictionary->LocateEntry( "U:JOYSTICK ORIGIN Y" );
			m_nUJoystickRadius = m_pDictionary->LocateEntry( "U:JOYSTICK RADIUS" );

			m_nUJoystickPositionX = m_pDictionary->LocateEntry( "U:JOYSTICK POSITION X" );
			m_nUJoystickPositionY = m_pDictionary->LocateEntry( "U:JOYSTICK POSITION Y" );

			m_nUEPTMPositionX = m_pDictionary->LocateEntry( "U:EPTM POSITION X" );
			m_nUEPTMPositionY = m_pDictionary->LocateEntry( "U:EPTM POSITION Y" );

			m_nUEPTMFlags = m_pDictionary->LocateEntry( "U:EPTM FLAGS" );

			m_mFlags = EPTM_M_AcceptInput;

			CVariantData	v = m_mFlags;
			m_pDictionary->PutData( m_nUEPTMFlags, &v );

			m_nIX = m_pDictionary->LocateEntry( "I:Mouse X" );
			m_nIY = m_pDictionary->LocateEntry( "I:Mouse Y" );

			m_nSScreenWidth = m_pDictionary->LocateEntry( "S:SCREEN WIDTH" );
			m_nSScreenHeight = m_pDictionary->LocateEntry( "S:SCREEN HEIGHT" );

			v = (long)EPTM_M_AcceptInput;
			CCharString	sAcceptInput("EPTM ACCEPT INPUT");
			m_pConstantsPage->AddEntry(sAcceptInput, v );

			v = (long)EPTM_M_ScanActive;
			CCharString	sScanActive("EPTM SCAN ACTIVE");
			m_pConstantsPage->AddEntry(sScanActive, v );

			m_bActive = false;

		}

		CServiceManagerPtr	pSvcMgr = (CServiceManagerPtr)m_pApplication->FindObject( "ServiceManager" );
		if ( pSvcMgr )
		{
			m_pIPanAndTilt = (IPanAndTiltPtr)pSvcMgr->FindServiceByIF( IXID_IPanAndTilt );
			if ( m_pIPanAndTilt )
			{
				DbgPrint( "IPanAndTilt interface found\n" );

				m_pIPanAndTilt->RegisterClient( (IPanAndTiltClientPtr)INTERFACE_THIS( IPanAndTiltClientPtr ) );
			}
			else
			{
				LogPrint( "Unable to locate IPanAndTilt interface\n" );
				bResult = false;
			}
		}
		else
		{
			LogPrint( "Unable to find ServiceManager for Eptm command\n" );
			bResult = false;
		}


		m_bDirty = true;


	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * ProcessRequest -

\+---------------------------------------------------------------------*/
bool	CmdEptm::ProcessRequest
		(
		VDictionary::Selector	selCommand,
		ConstCVariantDataRef	vData
		)
{
	bool	bResult = true;
	if ( selCommand == m_nCmdEptmCalculate )
		bResult = EPTMCalculate( vData );
	else if ( selCommand == m_nCmdJoystickStart )
		bResult = JoystickStart( vData );
	else if ( selCommand == m_nCmdJoystickMove )
		bResult = JoystickMove( vData );
	else if ( selCommand == m_nCmdJoystickStop )
		bResult = JoystickStop( vData );
	else if ( selCommand == m_nCmdEptmHome )
		bResult = EPTMHome( vData );
	else if ( selCommand == m_nCmdEptmSetHome )
		bResult = EPTMSetHome( vData );
	else if ( selCommand == m_nCmdEptmSlew )
		bResult = EPTMSlew( vData );
	else if ( selCommand == m_nCmdEptmSetSlewCenter )
		bResult = EPTMSetSlewCenter( vData );
	else if ( selCommand == m_nCmdAutoPanStart )
		bResult = AutoPanStart( vData );
	else if ( selCommand == m_nCmdAutoPanStop )
		bResult = AutoPanStop( vData );
	else if ( selCommand == m_nCmdAutoPanChangeSpeed )
		bResult = AutoPanChangeSpeed( vData );
	else if ( selCommand == m_nCmdAutoPanDefineLeft )
		bResult = AutoPanDefineLeft( vData );
	else if ( selCommand == m_nCmdAutoPanDefineRight )
		bResult = AutoPanDefineRight( vData );
	else
		bResult = inherited::ProcessRequest( selCommand, vData );
	return bResult;
}

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\

 * Load -

\+---------------------------------------------------------------------*/
bool	CmdEptm::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		m_fPanLeft = -160.0f;
		m_fPanRight = 160.0f;
		m_fTiltTop = 40.0f;
		m_fTiltBottom = -10.0f;
		m_fPanSpeed = 0.6f;
		m_fPanSpeed = GFLOAT(0.75);

		m_fSlewCenterX = GFLOAT_0;
		m_fSlewCenterY = GFLOAT_0;
	}

	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
