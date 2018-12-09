/*---------------------------------------------------------------------+\
|
|	CServiceRstaEptm.h  --  VDDS implementation of Pan & Tilt module
|
|	Purpose:
|	File Custodian:		J.Griswold
|
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

	22-Jul-2010			J.Griswold		(Reviewed by: J.Griswold)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "CServiceRstaEptm.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformTime.h"
#include "UPlatformThreads.h"

#include "VPluginFactory.h"
#include "UPluginConfiguration.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define	SENDSIZE	8

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( CServiceRstaEptm );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * CServiceRstaEptm - constructor

\+---------------------------------------------------------------------*/
CServiceRstaEptm::CServiceRstaEptm
		(
		void
		)
		: inherited(),
		m_oMoveQueue(),
		m_fPan( 0 ),
		m_fTilt( 0 ),
		m_fPrevPan( 0 ),
		m_fPrevTilt( 0 ),
		m_bAutoPan( false ),
		m_oEptmTxSem(),
		m_oEptmPort(),
		m_oCmmPort(),
		m_aClients(),
		m_aCallbacks(),
		m_pMoveTargetEvent( 0 ),
		m_pMoveCallback( 0 )
{
}


/*---------------------------------------------------------------------+\

 * CServiceRstaEptm - constructor

\+---------------------------------------------------------------------*/
CServiceRstaEptm::CServiceRstaEptm
		(
		ISupportsPtr pOwner
		)
		: inherited(pOwner),
		m_oMoveQueue(),
		m_fPan( 0 ),
		m_fTilt( 0 ),
		m_fPrevPan( 0 ),
		m_fPrevTilt( 0 ),
		m_bAutoPan( false ),
		m_oEptmTxSem(),
		m_oEptmPort(),
		m_oCmmPort(),
		m_aClients(),
		m_aCallbacks(),
		m_pMoveTargetEvent( 0 ),
		m_pMoveCallback( 0 )
{
}


/*---------------------------------------------------------------------+\

 * CServiceRstaEptm - constructor

\+---------------------------------------------------------------------*/
CServiceRstaEptm::CServiceRstaEptm
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited(sName, pOwner),
		m_oMoveQueue(),
		m_fPan( 0 ),
		m_fTilt( 0 ),
		m_fPrevPan( 0 ),
		m_fPrevTilt( 0 ),
		m_bAutoPan( false ),
		m_oEptmTxSem(),
		m_oEptmPort(),
		m_oCmmPort(),
		m_aClients(),
		m_aCallbacks(),
		m_pMoveTargetEvent( 0 ),
		m_pMoveCallback( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CServiceRstaEptm - destructor

\+---------------------------------------------------------------------*/
CServiceRstaEptm::~CServiceRstaEptm
	(
	void
	)
{
	if ( this->IsRunning() )
		Stop();
}




/*=====================================================================+\
||	 interface implementation functions									|
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IService
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\

 * Start -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::Start
		(
		void
		)
{
	NResult	nr = NR_E_NOTHREAD;

		//sem_init( &m_tEptmTxSem, 0, 0 );

	unsigned char buffer[8];
	CommandSetSoftLimit( buffer, sizeof(buffer),
							178, 178, 90, 90 );
	AppendAction( CMD_SetSoftLimit, GFLOAT_0, GFLOAT_0,
							buffer, sizeof( buffer) );

	CommandStop( buffer, sizeof(buffer) );
	AppendAction( CMD_Move, GFLOAT_0, GFLOAT_0, buffer, sizeof(buffer) );



	CMutexLocker	lock( &m_oMutex );

	m_bRunning = false;
	m_nMilliBroadcast = 0;
	m_nMilliIdle = 0;
	m_bJoystickOnly = true;
	m_bMoving = false;


	m_fAPLeft = 80.0f;
	m_fAPTop = 45.0f;
	m_fAPRight = 10.0f;
	m_fAPBottom = 20.0f ;

	do
	{

		m_bJoystickOnly = false;

		m_oCmmPort.SetMinBytes( 1 );
		m_oCmmPort.SetTimeout(16 );
		nr = m_oCmmPort.Open( CSerial::MODE_ReadWrite );
		if ( NR_FAILED(nr) )
			break;

		if ( ! m_oCmmPort.IsOpen() )
			break;

		m_oEptmPort.SetMinBytes( 1 );
		m_oEptmPort.SetTimeout( 10 );
		nr = m_oEptmPort.Open( CSerial::MODE_ReadWrite );
		if ( NR_FAILED(nr) )
			break;

		if ( ! m_oEptmPort.IsOpen() )
			break;

		CommandStop( m_aNeutral, sizeof(m_aNeutral) );


		nr = NR_E_NOTHREAD;

		m_hCmm = ThreadCreate( (UThreadFunction)CmmThreadGlue, this );
		if ( ! m_hCmm )
		{
			break;
		}


		m_hEptmRx = ThreadCreate( (UThreadFunction)EptmRxThreadGlue, this );
		if ( ! m_hEptmRx )
		{
			ThreadClose( m_hCmm );
			break;
		}


		m_hEptmTx = ThreadCreate( (UThreadFunction)EptmTxThreadGlue, this );
		if ( ! m_hEptmTx )
		{
			ThreadClose( m_hCmm );
			ThreadClose( m_hEptmRx );
			break;
		}


		m_bRunning = true;
		nr = NR_S_SUCCESS;

	} sequence;

	return nr;
}

/*---------------------------------------------------------------------+\

 * Stop -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::Stop
		(
		void
		)
{

	CMutexLocker	lock( &m_oMutex );


	//sem_close( &m_tEptmTxSem );

	if ( m_bAutoPan )
	{
		AutoPanThreadStop();
	}

	if ( m_hEptmTx )
	{
		ThreadClose( m_hEptmTx );
		m_hEptmTx = 0;
	}

	if ( m_hEptmRx )
	{
		ThreadClose( m_hEptmRx );
		m_hEptmRx = 0;
	}

	if ( m_hCmm )
	{
		ThreadClose( m_hCmm );
		m_hCmm = 0;
	}

	m_oEptmPort.Close();
	m_oCmmPort.Close();

	m_bRunning = false;

	return NR_S_SUCCESS;
}






/*---------------------------------------------------------------------+\
|	 IPanAndTilt
\+---------------------------------------------------------------------*/



/*---------------------------------------------------------------------+\

 * MoveViaSpeed -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::MoveViaSpeed
		(
		GFLOAT		fPanNorm,	// IN:	normalized speed for rotation
		GFLOAT		fTiltNorm	// IN:	normalized speed for elevation
		)
{
	NResult	nr = NR_S_SUCCESS;

	if ( ! m_bJoystickOnly )
	{
		//DbgPrint( "MoveViaSpeed: %f, %f\n", (double)fPanNorm, (double)fTiltNorm );
		unsigned char	buffer[SENDSIZE];

		if ( m_bAutoPan )
			AutoPanThreadStop();
		if ( fabsf(fPanNorm) < GFLOAT_EPSILON
			&&	fabsf(fTiltNorm) < GFLOAT_EPSILON )
			CommandStop( buffer, sizeof(buffer) );
		else
			CommandMove( buffer, sizeof(buffer), fPanNorm, fTiltNorm );
//		DbgPrint( "MoveViaSpeed: " );
//		for ( size_t i = 0; i < sizeof(buffer); ++i )
//		{
//			DbgPrint( " %02x ", buffer[i] );
//		}
//		DbgPrint( "\n" );

		AppendAction( CMD_Move, fPanNorm, fTiltNorm, buffer, sizeof(buffer) );
	}

	return nr;
}

/*---------------------------------------------------------------------+\

 * MoveDelta -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::MoveDelta
		(
		GFLOAT		fPan,
		GFLOAT		fTilt,
		GFLOAT		fSpeed
		)
{
	GFLOAT	fCurPan;
	GFLOAT	fCurTilt;

	//m_oMutex.Lock();
	fCurPan = m_fPan;
	fCurTilt = m_fTilt;
	//m_oMutex.Unlock();

	// TODO: normalize angles to something that will actually work.
	fCurPan += fPan;
	fCurTilt += fTilt;

	MoveTo( fCurPan, fCurTilt, fSpeed );

	return NR_S_SUCCESS;
}



/*---------------------------------------------------------------------+\

 * MoveAbsolute -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::MoveAbsolute
		(
		GFLOAT		fPan,
		GFLOAT		fTilt,
		GFLOAT		fSpeed
		)
{

		if ( ! m_oMoveQueue.IsEmpty() )
		{
			DbgPrint( "emptying queue\n" );
			m_oMoveQueue.Clear();
		}

		SetMoveTargetEvent( &CServiceRstaEptm::MoveAbsoluteTargetEvent );

	DbgPrint( "%s - p=%f, t=%f\n", __FUNCTION__, (float)fPan, (float)fTilt );

	MoveTo( -fPan, -fTilt, fSpeed );


	return NR_S_SUCCESS;
}



/*---------------------------------------------------------------------+\

 * AutoPanMoveTargetEvent -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::MoveAbsoluteTargetEvent
		(
		GFLOAT	,//fPan,
		GFLOAT	,//fTilt,
		bool	//bCompleted
		)
{
	DbgPrint( "%s\n", __PRETTY_FUNCTION__ );


	SetMoveTargetEvent( 0 );

	m_oMutex.Lock();
	m_bAutoPan = false;
	m_eAPState = AP_None;
	m_oMutex.Unlock();

	MoveToStop();

}







/*---------------------------------------------------------------------+\

 * AutoPan -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::AutoPan
		(
		GFLOAT		fPanLeft,		// left side of virtual window
		GFLOAT		fTiltTop,
		GFLOAT		fPanRight,		// right side of virtual window
		GFLOAT		fTiltBottom,
		GFLOAT		fSpeed			//	normalized speed value
		)
{
	//CMutexLocker	lock( &m_oMutex );
	m_fAPLeft = -fPanLeft;
	m_fAPTop = -fTiltTop;
	m_fAPRight = -fPanRight;
	m_fAPBottom = -fTiltBottom;
	m_fAPSpeed = m_fSpeed = fSpeed;

	//DbgPrint( "%s\n", __FUNCTION__ );

	if ( ! m_bAutoPan )
		AutoPanThreadStart();

	return NR_S_SUCCESS;
}



/*---------------------------------------------------------------------+\

 * MoveHome -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::MoveHome
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;

	DbgPrint( "CServiceRstaEptm::MoveHome\n" );

	if ( ! m_bJoystickOnly )
	{
		unsigned char	buffer[SENDSIZE];
		CommandHome( buffer, sizeof(buffer) );

		if ( m_bAutoPan )
			AutoPanThreadStop();

		AppendAction( CMD_Home, GFLOAT_0, GFLOAT_0, buffer, sizeof(buffer) );
	}

	return nr;
}


/*---------------------------------------------------------------------+\

 * SetHome -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::SetHome
		(
		void
		)
{
	NResult	nr = NR_S_SUCCESS;

	if ( ! m_bJoystickOnly )
	{
		if ( ! m_bAutoPan )
		{
			unsigned char	buffer[SENDSIZE];
			CommandSetHome( buffer, sizeof(buffer) );

			if ( m_bAutoPan )
				AutoPanThreadStop();

			AppendAction( CMD_SetHome, GFLOAT_0, GFLOAT_0, buffer, sizeof(buffer) );
		}
	}

	return nr;
}


/*---------------------------------------------------------------------+\

 * GetPosition -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::GetPosition
		(
		GFLOAT*		pPan,	// OUT:	rotation position in degrees
		GFLOAT*		pTilt	// OUT: elevation position in degrees
		)
{
	CMutexLocker	lock( &m_oMutex );
	*pPan = m_fPan;
	*pTilt = m_fTilt;
	return NR_S_SUCCESS;
}


/*---------------------------------------------------------------------+\

 * EptmThreadGlue -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::RegisterClient
		(
		IPanAndTiltClientPtr p
		)
{
	m_aClients.AppendData( &p );
	return NR_S_SUCCESS;
}


/*---------------------------------------------------------------------+\

 * EptmThreadGlue -

\+---------------------------------------------------------------------*/
NResult	CServiceRstaEptm::UnregisterClient
		(
		IPanAndTiltClientPtr //p
		)
{
	return NR_S_SUCCESS;
}





/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

unsigned char
g_aSpeed[] = { 0x00, 0x05, 0x10, 0x20, 0x30, 0x40, 0x50, 0x64 };

GFLOAT
g_aScale[] = { 0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1.0 };


/*---------------------------------------------------------------------+\

 * EptmThreadGlue -

\+---------------------------------------------------------------------*/
unsigned char
		CServiceRstaEptm::MakeSpeed
		(
		GFLOAT fSpeed
		)
{
	fSpeed = (GFLOAT)fabs( fSpeed );
	if ( GFLOAT_1 < fSpeed )
		fSpeed = GFLOAT_1;
	if ( GFLOAT_0 < fSpeed )
	{
		//return long(fSpeed * GFLOAT(100));
		long			n = long(fSpeed * GFLOAT(sizeof(g_aSpeed)-1));
		unsigned char	u = g_aSpeed[n];
		if ( 0 == u  &&  GFLOAT(0.125) < fSpeed )
			u = g_aSpeed[1];

		return u;
	}
	else
	{
		return 0;
	}
}


/*---------------------------------------------------------------------+\

 * EptmThreadGlue -

\+---------------------------------------------------------------------*/
GFLOAT	CServiceRstaEptm::ScaleFromSpeed
		(
		unsigned char x
		)
{
	for ( unsigned int i = 0; i < sizeof(g_aSpeed); ++i )
	{
		if ( x == g_aSpeed[i] )
		{
			return g_aScale[i];
		}
	}

	return GFLOAT_1;
}

/*---------------------------------------------------------------------+\

 * EptmThreadGlue -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::AppendAction
		(
		ECommand	eCmd,
		GFLOAT		fPanNorm,
		GFLOAT		fTiltNorm,
		unsigned char*	pBuffer,
		long			nSize
		)
{

#if 0
#if defined( _DEBUG )
	DbgPrint( "AppendAction: " );
	for ( int i = 0; i < nSize; ++i )
	{
		DbgPrint( " %02x ", pBuffer[i] );
	}
	DbgPrint( "\n" );
#endif
#endif

	MoveEntry	entry;

	entry.eCmd = eCmd;
	entry.fPanNorm = fPanNorm;
	entry.fTiltNorm = fTiltNorm;
	memcpy_s( entry.buffer, sizeof(entry.buffer), pBuffer, nSize );

	m_oMoveQueue.AppendEntry( entry );

	m_oEptmTxSem.Signal();

	//sem_post( &m_tEptmTxSem );
	return true;
}



/*---------------------------------------------------------------------+\

 * CommandMove -

\+---------------------------------------------------------------------*/
// pan & tilt movement
long	CServiceRstaEptm::CommandMove
		(
		unsigned char*	pBuffer,
		long			,//nSize,
		GFLOAT			fPanNorm,
		GFLOAT			fTiltNorm
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;		// start byte
	pBuffer[1] = 0x4A;		// address

	unsigned char	nPanSpeed = MakeSpeed(fPanNorm);
	unsigned char	nTiltSpeed = MakeSpeed(fTiltNorm);

	if ( 0 == nPanSpeed  &&  0 == nTiltSpeed )
	{
		if ( fabsf(fTiltNorm) < fabsf(fPanNorm) )
			nPanSpeed = 0x05;
		else
			nTiltSpeed = 0x05;
	}

	// pan-direction
	if ( 0 != nPanSpeed )
		pBuffer[2] = (unsigned char)
					(fPanNorm < GFLOAT_0
					?	k_PanLeft
					: (GFLOAT_0 < fPanNorm ? k_PanRight : k_PanStop ));
	else
		pBuffer[2] = (unsigned char)k_PanStop;

	// tilt-direction
	if ( 0 != nTiltSpeed )
		pBuffer[3] = (unsigned char)
					(fTiltNorm < GFLOAT_0
					?	k_TiltDown
					: (GFLOAT_0 < fTiltNorm ? k_TiltUp : k_TiltStop ));
	else
		pBuffer[3] = (unsigned char)k_TiltStop;
	pBuffer[4] = nPanSpeed;		// pan-speed
	pBuffer[5] = nTiltSpeed;		// tilt-speed
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;		// stop byte

	return nResult;
}

/*---------------------------------------------------------------------+\

 * CommandStop -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CommandStop
		(
		unsigned char*	pBuffer,
		long			//nSize
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;			// start byte
	pBuffer[1] = 0x4A;			// address
	pBuffer[2] = k_PanStop;		// pan-direction
	pBuffer[3] = k_TiltStop;	// tilt-direction
	pBuffer[4] = 0000;			// pan-speed
	pBuffer[5] = 0000;			// tilt-speed
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;			// stop byte

	return nResult;
}



/*---------------------------------------------------------------------+\

 * CommandHome -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CommandHome
		(
		unsigned char*	pBuffer,
		long			//nSize
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;		// start byte
	pBuffer[1] = 0x43;		// address
	pBuffer[2] = 0x01;		// pan-direction
	pBuffer[3] = 0x00;		// tilt-direction
	pBuffer[4] = 0000;		// pan-speed
	pBuffer[5] = 0000;		// tilt-speed
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;		// stop byte

	return nResult;
}


/*---------------------------------------------------------------------+\

 * CommandSetHome -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CommandSetHome
		(
		unsigned char*	pBuffer,
		long			//nSize
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;		// start byte
	pBuffer[1] = 0x50;		// address
	pBuffer[2] = 0x61;		// pan-direction
	pBuffer[3] = 0x73;		// tilt-direction
	pBuffer[4] = 0000;		// pan-speed
	pBuffer[5] = 0000;		// tilt-speed
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;		// stop byte

	return nResult;
}

/*---------------------------------------------------------------------+\

 * CommandZeroCalibration -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CommandZeroCalibration
		(
		unsigned char*	pBuffer,
		long			//nSize
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;		// start byte
	pBuffer[1] = 0x60;		// address
	pBuffer[2] = 0x13;		// pan-direction
	pBuffer[3] = 0x25;		// tilt-direction
	pBuffer[4] = 0000;		// pan-speed
	pBuffer[5] = 0000;		// tilt-speed
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;		// stop byte

	return nResult;
}

/*---------------------------------------------------------------------+\

 * CommandSetSoftLimit -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CommandSetSoftLimit
		(
		unsigned char*	pBuffer,
		long			,//nSize,
		long			nLeft,
		long			nRight,
		long			nDown,
		long			nUp
		)
{
	long	nResult = 8;

	pBuffer[0] = 0x02;		// start byte
	pBuffer[1] = 0x17;		// address
	pBuffer[2] = (unsigned char)nLeft;		// left-limit
	pBuffer[3] = (unsigned char)nRight;		// right-limit
	pBuffer[4] = (unsigned char)nDown;		// down-limit
	pBuffer[5] = (unsigned char)nUp;		// up-limit
	pBuffer[6] = Checksum( &pBuffer[0], 6 );
	pBuffer[7] = 0x03;		// stop byte

	return nResult;
}


/*---------------------------------------------------------------------+\

 * ParseEptmResponse -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::ParseEptmResponse
		(
		unsigned char*	pBuffer,
		long			nSize
		)
{
	bool	bResult = false;

	do_sequence
	{
		if ( 14 != nSize )
		{
			DbgPrint("%s - unexpected buffer size %d\n", __FUNCTION__, nSize );
			break;
		}

		if ( 0x04 != pBuffer[0] )
		{
			DbgPrint("%s - unexpected start byte %02x\n", __FUNCTION__, pBuffer[0] );
			break;
		}

		int	nck = Checksum( &pBuffer[0], 13 );
		if ( nck != pBuffer[13] )
		{
			DbgPrint("%s - incorrect checksum value\n", __FUNCTION__ );
			break;
		}


		GFLOAT	fPan = degreesFromBytes( pBuffer[2], pBuffer[1] );
		GFLOAT	fTilt = degreesFromBytes( pBuffer[4], pBuffer[3] );

		GFLOAT	fSoftLeft = pBuffer[5];
		GFLOAT	fSoftRight = pBuffer[6];
		GFLOAT	fSoftBottom = pBuffer[7];
		GFLOAT	fSoftTop = pBuffer[8];

		GFLOAT	fHomePan = degreesFromBytes( pBuffer[10], pBuffer[9] );
		GFLOAT	fHomeTilt = degreesFromBytes( pBuffer[12], pBuffer[11] );

		m_oMutex.Lock();
		m_fPan = fPan;
		m_fTilt = fTilt;
		if ( m_fPan != m_fPrevPan
			||	m_fTilt != m_fPrevTilt )
		{
			m_fPrevPan = m_fPan;
			m_fPrevTilt = m_fTilt;
			m_bMoving = true;
		}
		else
		{
			m_bMoving = false;
		}
		m_fSoftLeft = fSoftLeft;
		m_fSoftTop = fSoftTop;
		m_fSoftRight = fSoftRight;
		m_fSoftBottom = fSoftBottom;
		m_fHomePan = fHomePan;
		m_fHomeTilt = fHomeTilt;
		m_oMutex.Unlock();

		//DbgPrint( "Eptm Moving = %s\n", m_bMoving?"yes":"no" );

		if ( m_pMoveCallback )
			(this->*m_pMoveCallback)();

		BroadcastToClients();

		bResult = true;
	}
#if 0
	pBuffer[0] == 0x04;

	pBuffer[1] == 0000;		//	x-high
	pBuffer[2] = 0000;		//	x-low

	pBuffer[3] == 0000;		//	y-high
	pBuffer[4] == 0000;		//	y-low

	pBuffer[5] == 0000;		// left soft limit byte
	pBuffer[6] == 0000;		// right soft limit byte

	pBuffer[7] == 0000;		// down soft limit byte
	pBuffer[8] == 0000;		// up soft limit byte

	pBuffer[9] == 0000;		// x-home-high
	pBuffer[10] == 0000;	// x-home-low

	pBuffer[11] == 0000;	// y-home-high
	pBuffer[12] == 0000;	// y-home-low

	pBuffer[13] == 0000;	// checksum
#endif
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ParseCmmMessage -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::ParseCmmMessage
		(
		unsigned char*	pBuffer,
		long			nSize
		)
{
	bool	bResult = false;

	do_sequence
	{
		if ( nSize != 8 )
		{
			DbgPrint( "ParseCmmMessage: bad size = %d\n", nSize );
			break;
		}

		if ( k_ByteStart != pBuffer[0] )
			break;

		if ( k_ByteStop != pBuffer[7] )
			break;

		if ( Checksum( &pBuffer[0], 6 ) != pBuffer[6] )
			break;

		switch ( pBuffer[1] )
		{
		case 0x4A:		// Move
			{
				GFLOAT	fPan = ScaleFromSpeed( pBuffer[4] );
				GFLOAT	fTilt = ScaleFromSpeed( pBuffer[5] );

				switch ( pBuffer[2] )
				{
				case k_PanLeft:
					fPan = -fPan;
					break;
				case k_PanRight:
					// nothing needed
					break;
				case k_PanStop:
				default:
					fPan = GFLOAT_0;
					break;
				}

				switch ( pBuffer[3] )
				{
				case k_TiltDown:
					fTilt = -fTilt;
					break;
				case k_TiltUp:
					// no action needed
					break;
				case k_TiltStop:
				default:
					fTilt = GFLOAT_0;
					break;
				}
				//DbgPrint( "ParseCmmMessage->AppendAction\n" );
				AppendAction( CMD_Move, fPan, fTilt, pBuffer, nSize );
			}
			break;
		case 0x43:		// Home
			AppendAction( CMD_Home, GFLOAT_0, GFLOAT_0, pBuffer, nSize );
			break;
		case 0x50:		// Set Home
			AppendAction( CMD_SetHome, GFLOAT_0, GFLOAT_0, pBuffer, nSize );
			break;
		default:
			AppendAction( CMD_None, GFLOAT_0, GFLOAT_0, pBuffer, nSize );
			break;
		}

		bResult = true;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Checksum -

\+---------------------------------------------------------------------*/
unsigned char
		CServiceRstaEptm::Checksum
		(
		unsigned char*	p,
		long			nCount
		)
{
	unsigned char	nSum = 0;
	unsigned char*	pEnd = p + nCount;

	BEGIN_IGNORE_WARNING( 4244 )	// possible loss of data

	while ( p < pEnd )
	{
		nSum += *p++;
	}

	END_IGNORE_WARNING

	nSum = ~nSum + 1;

	return nSum;
}


/*---------------------------------------------------------------------+\

 * intFromBytes -

\+---------------------------------------------------------------------*/
int		CServiceRstaEptm::intFromBytes
		(
		unsigned char nLow,
		unsigned char nHigh
		)
{
	short	nValue = 0;

	nValue = nHigh << 8;
	nValue |= nLow;

	return (int)nValue;
}


GFLOAT	CServiceRstaEptm::floatFromHalf
		(
		unsigned short	n
		)
{
	typedef union uif
	{
		unsigned int	i;
		GFLOAT			f;
	} uif;
	unsigned short y = n;
	uif fl;
    int s = (y >> 15) & 0x00000001;
    int e = (y >> 10) & 0x0000001f;
    int m =  y        & 0x000003ff;

    if (e == 0)
    {
		if (m == 0)
		{
			//
			// Plus or minus zero
			//
			fl.i = s << 31;
			return fl.f;
		}
		else
		{
			//
			// Denormalized number -- renormalize it
			//
			while (!(m & 0x00000400))
			{
				m <<= 1;
				e -=  1;
			}

			e += 1;
			m &= ~0x00000400;
		}
    }
    else if (e == 31)
    {
		if (m == 0)
		{
			//
			// Positive or negative infinity
			//
			fl.i = (s << 31) | 0x7f800000;
			return fl.f;
		}
		else
		{
			//
			// Nan -- preserve sign and significand bits
			//
			fl.i = (s << 31) | 0x7f800000 | (m << 13);
			return fl.f;
		}
    }

    //
    // Normalized number
    //
    e = e + (127 - 15);
    m = m << 13;

    //
    // Assemble s, e and m.
    //
	fl.i = (s << 31) | (e << 23) | m;
	return fl.f;
}



/*---------------------------------------------------------------------+\

 * degreesFromBytes -

\+---------------------------------------------------------------------*/
GFLOAT	CServiceRstaEptm::degreesFromBytes
		(
		unsigned char nLow,
		unsigned char nHigh
		)
{
	unsigned short	nValue = 0;
	const float kStep = 135.0f;

	nValue = (unsigned short)nHigh << 8;
	nValue |= (unsigned short)nLow;

	float	f = float((short)nValue) / kStep;

	return f;
}



/*---------------------------------------------------------------------+\

 * BroadcastToClients -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::BroadcastToClients
		(
		void
		)
{
	long	nMilli = milliseconds();
	if ( m_nMilliBroadcast + 300 < nMilli )
	{
		m_nMilliBroadcast = nMilli;

		BroadcastToClientsNow();

	}
}

/*---------------------------------------------------------------------+\

 * BroadcastToClientsNow -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::BroadcastToClientsNow
		(
		void
		)
{
	//DbgPrint( "BroadcastToClients: p=%f, t=%f\n", m_fPan, m_fTilt );

	if ( 0 < m_aClients.Length() )
	{
		// invert the coordinate system
		GFLOAT	fPan = -m_fPan;
		GFLOAT	fTilt = -m_fTilt;

		m_nMilliBroadcast = milliseconds();


		TArrayEnumerator<IPanAndTiltClientPtr>
				tEnum = m_aClients.GetEnumerator();


		while ( tEnum.MoveNext() )
		{
			IPanAndTiltClientPtr*	hI = tEnum.Current();
			if ( hI )
			{
				long	mFlags = 0;
				if ( ! m_bJoystickOnly )
					mFlags |= EPTM_M_AcceptInput;
				if ( m_bAutoPan )
					mFlags |= EPTM_M_ScanActive;
				(*hI)->EptmState( fPan, fTilt, mFlags );
			}
		}
	}
}

/*---------------------------------------------------------------------+\

 * EptmTxThreadGlue -

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceRstaEptm::EptmTxThreadGlue
		(
		void*	pArg
		)
{
	CServiceRstaEptmPtr	pThis = (CServiceRstaEptmPtr)pArg;
	if ( pThis )
	{
		return pThis->EptmTxThread();
	}
	else
	{
		return (UThreadRtn)0;
	}
}


/*---------------------------------------------------------------------+\

 * EptmTxThread -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceRstaEptm::EptmTxThread
		(
		void
		)
{
	bool			b = false;
	long			nCount = 0;
	unsigned char	buffer[32];

	memcpy_s( buffer, sizeof(buffer), m_aNeutral, sizeof(m_aNeutral) );
	nCount = sizeof(m_aNeutral);

	/*
	Read from circular queue and format message to send to Eptm
	*/

	loop_forever
	{

		MoveEntry	entry;

		b = m_oMoveQueue.FetchEntry( entry );

		if ( b )
		{
			memcpy_s( buffer, sizeof(buffer), entry.buffer, sizeof(entry.buffer) );
			nCount = sizeof(entry.buffer);

			if ( 0 < nCount )
			{
#if 0
#if defined( _DEBUG )
				DbgPrint( "EptmTxThread: " );
				for ( int i = 0; i < nCount; ++i )
				{
					DbgPrint( " %02x ", buffer[i] );
				}
				DbgPrint( "\n" );
#endif
#endif
				m_oEptmPort.Write( buffer, nCount );
				m_bMoving = true;
			}
		}
		else
		{
			if ( 0 < nCount )
			{
				m_oEptmPort.Write( buffer, nCount );
			}
			if ( m_bMoving
				||  m_bAutoPan
				||	milliseconds() < m_nMilliIdle + 1000 )
			{
				millisleep( 200 );
			}
			else
			{
				//DbgPrint("sem_wait\n");
				m_oEptmTxSem.Wait();
				//sem_wait( &m_tEptmTxSem );
			}
		}
	}
	return (UThreadRtn)0;
}


/*---------------------------------------------------------------------+\

 * EptmRxThreadGlue -

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceRstaEptm::EptmRxThreadGlue
		(
		void*	pArg
		)
{
	CServiceRstaEptmPtr	pThis = (CServiceRstaEptmPtr)pArg;
	if ( pThis )
	{
		return pThis->EptmRxThread();
	}
	else
	{
		return (UThreadRtn)0;
	}
}


/*---------------------------------------------------------------------+\

 * EptmRxThread -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceRstaEptm::EptmRxThread
		(
		void
		)
{
	/*
	Read Serial port and parse resulting message
	Save information from message
	send message to CMM
	*/

	if ( ! m_oEptmPort.IsOpen() )
		return (UThreadRtn)0;

	long	nRead = 0;
	unsigned char	buffer[64];

	//TQueue<unsigned char>	oQueue;

	m_oEptmPort.Flush();

	loop_forever
	{
		nRead = EptmRead( buffer, sizeof(buffer) );

		if ( 0 < nRead )
		{
#if 0
#if defined( _DEBUG )
			DbgPrint( "EPTM.Read: " );
			for ( int i = 0; i < nRead; ++i )
			{
				DbgPrint( " %02x ", buffer[i] );
			}
			DbgPrint( "\n" );
#endif
#endif

			// pass on to CMM
			m_oCmmPort.Write( buffer, nRead );

			// parse message
			ParseEptmResponse( buffer, nRead );


		}

	}

	return (UThreadRtn)0;
}



/*---------------------------------------------------------------------+\

 * EptmRead -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::EptmRead
		(
		unsigned char*	buffer,
		long			//nSize
		)
{
	const long	nMaxMsgSize = 14;
	long		nRead = 0;
	long		n = 0;

	//DbgPrint( "%s:", __FUNCTION__ );

	do
	{
		n = long(m_oEptmPort.Read( buffer, 1 ));
//		if ( 0 < n )
//			DbgPrint( " %02x ", buffer[0] );
	} while ( 0 < n  &&  0x04 != *buffer );

	if ( 0 < n )
	{
		nRead = n;
		do
		{
			n = long(m_oEptmPort.Read( buffer+nRead, nMaxMsgSize-nRead ));
			if ( 0 < n )
			{
//				for ( int i = nRead; i < nRead+n; ++i )
//				{
//					DbgPrint( " %02x ", buffer[i] );
//				}

				nRead += n;
			}
		} while ( nRead < nMaxMsgSize );

		if ( Checksum( &buffer[0], 13 ) != buffer[13] )
		{
			nRead = 0;
			//DbgPrint( "%s - read rejected for bad checksum\n", __FUNCTION__ );
		}
	}

	//DbgPrint( "\n" );

	return nRead;

}





/*---------------------------------------------------------------------+\

 * CmmThreadGlue -

\+---------------------------------------------------------------------*/
//static
UThreadRtn
		CServiceRstaEptm::CmmThreadGlue
		(
		void*	pArg
		)
{
	CServiceRstaEptmPtr	pThis = (CServiceRstaEptmPtr)pArg;
	if ( pThis )
	{
		return pThis->CmmThread();
	}
	else
	{
		return (UThreadRtn)0;
	}
}




/*---------------------------------------------------------------------+\

 * CmmThread -

\+---------------------------------------------------------------------*/
UThreadRtn
		CServiceRstaEptm::CmmThread
		(
		void
		)
{
	/*
	read serial port
	parse message and append to circular queue
	send semaphore to EptmTx thread
	*/

	if ( ! m_oCmmPort.IsOpen() )
		return (UThreadRtn)0;

	unsigned char	buffer[64];
	long			nRead;
	bool			bJoy;
	long			nMilli;

	m_oCmmPort.Flush();

	loop_forever
	{
		bJoy = m_bJoystickOnly;
		nRead = CmmRead( buffer, sizeof(buffer) );
		nMilli = milliseconds();
		if ( 0 < nRead )
		{
			if ( 0 == memcmp( buffer, m_aNeutral, sizeof(m_aNeutral) ) )
			{
				if ( m_nMilliIdle )
				{
					if ( m_nMilliIdle < nMilli )
						bJoy = false;
					else
						bJoy = true;
				}
				else
				{
					m_nMilliIdle = nMilli + 10 * 1000;
					bJoy = true;
				}
			}
			else
			{
//				DbgPrint( "CMM.Read: " );
//				for ( int i = 0; i < nRead; ++i )
//				{
//					DbgPrint( " %02x ", buffer[i] );
//				}
//				DbgPrint( "\n" );
				bJoy = true;
				m_nMilliIdle = 0;
			}
			// parse message

			if ( bJoy )
			{
				if ( m_bAutoPan )
					AutoPanThreadStop();
				ParseCmmMessage( buffer, nRead );
			}
		}
		else
		{
			if ( m_nMilliIdle )
			{
				if ( m_nMilliIdle < nMilli )
					bJoy = false;
				else
					bJoy = true;
			}
		}
		if ( m_bJoystickOnly != bJoy )
		{
			m_bJoystickOnly = bJoy;
			BroadcastToClientsNow();
		}
	}

	return (UThreadRtn)0;
}


/*---------------------------------------------------------------------+\

 * CmmRead -

\+---------------------------------------------------------------------*/
long	CServiceRstaEptm::CmmRead
		(
		unsigned char*	buffer,
		long			//nSize
		)
{
	const long	nMaxMsgSize = 8;
	long		nRead = 0;
	long		n = 0;

	do
	{
		n = long(m_oCmmPort.Read( buffer, 1 ));
	} while ( 0 < n  &&  k_ByteStart != *buffer );

	if ( 0 < n )
	{
		nRead = n;
		do
		{
			n = long(m_oCmmPort.Read( buffer+nRead, nMaxMsgSize-nRead ));
			if ( 0 < n )
				nRead += n;
		} while ( nRead < nMaxMsgSize );

		if ( k_ByteStop != buffer[nRead-1] )
			nRead = 0;

		if ( Checksum( &buffer[0], 6 ) != buffer[6] )
			nRead = 0;
	}

	return nRead;

}



/*---------------------------------------------------------------------+\

 * AutoPanThreadStart -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::AutoPanThreadStart
		(
		void
		)
{
	bool	bResult = false;
	//if ( ! m_bAutoPan )
	{
		// TODO: calculate speed and direction for initial pass

		DbgPrint( "%s\n", __FUNCTION__ );

		//m_fAPSpeed = m_fSpeed;


		if ( ! m_oMoveQueue.IsEmpty() )
		{
			DbgPrint( "emptying queue\n" );
			m_oMoveQueue.Clear();
		}

		m_oMutex.Lock();
		GFLOAT	f;
		if ( m_fAPLeft < m_fAPRight )
		{
			f = m_fAPLeft;
			m_fAPLeft = m_fAPRight;
			m_fAPRight = f;
		}

		if ( m_fAPBottom < m_fAPTop )
		{
			f = m_fAPBottom;
			m_fAPBottom = m_fAPTop;
			m_fAPTop = f;
		}

		m_bAutoPan = true;
		m_eAPState = AP_Home;

		m_oMutex.Unlock();

		SetMoveTargetEvent( &CServiceRstaEptm::AutoPanMoveTargetEvent );
		MoveTo( m_fAPLeft, m_fAPBottom, m_fAPSpeed );

		bResult = true;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * AutoPanThreadStop -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::AutoPanThreadStop
		(
		void
		)
{
	bool	bResult = true;

	GFLOAT	fPan;
	GFLOAT	fTilt;
	DbgPrint( "%s\n", __FUNCTION__ );

	fPan = m_fPan;
	fTilt = m_fTilt;

	if ( m_pMoveTargetEvent )
		(this->*m_pMoveTargetEvent)( fPan, fTilt, false );
	SetMoveTargetEvent( 0 );

	m_oMutex.Lock();
	m_bAutoPan = false;
	m_eAPState = AP_None;
	m_oMutex.Unlock();

	MoveToStop();


	return bResult;
}


/*---------------------------------------------------------------------+\

 * AutoPanMoveTargetEvent -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::AutoPanMoveTargetEvent
		(
		GFLOAT	,//fPan,
		GFLOAT	,//fTilt,
		bool	bCompleted
		)
{
	// increment state
	// calculate new target and call MoveTo
	//DbgPrint( "%s\n", __FUNCTION__ );

	if ( m_bAutoPan  &&  bCompleted )
	{
		switch ( m_eAPState )
		{
		case AP_None:
			m_eAPState = AP_Home;
			MoveTo( m_fAPLeft, m_fAPBottom, m_fAPSpeed );
			break;

		case AP_Home:
			m_eAPState = AP_MoveRight;
			m_fAPRow = m_fAPBottom;
			MoveToX( m_fAPRight, m_fAPSpeed );
			break;

		case AP_MoveLeft:
			m_eAPState = AP_RowLeft;
			m_fAPRow -= m_fAPRowSpacing;
			if ( m_fAPRow < m_fAPTop )
			{
				m_fAPRow = m_fAPBottom;
				MoveToY( m_fAPRow, m_fAPSpeed );
				//m_eAPState = AP_Home;
				//MoveTo( m_fAPLeft, m_fAPBottom, m_fAPSpeed );
			}
			else
			{
				MoveToY( m_fAPRow, m_fAPSpeed );
			}
			break;

		case AP_RowLeft:
			m_eAPState = AP_MoveRight;
			MoveToX( m_fAPRight, m_fAPSpeed );
			break;

		case AP_MoveRight:
			m_eAPState = AP_RowRight;
			m_fAPRow -= m_fAPRowSpacing;
			if ( m_fAPRow < m_fAPTop )
			{
				m_fAPRow = m_fAPBottom;
				MoveToY( m_fAPRow, m_fAPSpeed );

				//m_eAPState = AP_Home;
				//MoveTo( m_fAPLeft, m_fAPBottom, m_fAPSpeed );
			}
			else
			{
				MoveToY( m_fAPRow, m_fAPSpeed );
			}
			break;

		case AP_RowRight:
			m_eAPState = AP_MoveLeft;
			MoveToX( m_fAPLeft, m_fAPSpeed );
			break;

		default:
			DbgPrint( "%s - unexpected enum state\n", __PRETTY_FUNCTION__ );
			//AutoPanThreadStop();
			break;
		}
	}
}







/*---------------------------------------------------------------------+\

 * MoveTo -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveTo
		(
		GFLOAT	fPan,
		GFLOAT	fTilt,
		GFLOAT	fSpeed
		)
{
	bool	bResult = true;

	// TODO: normalize pan&tilt to actual degrees that we can handle

	//DbgPrint( "%s\n", __FUNCTION__ );

	m_fTargetPan = fPan;
	m_fTargetTilt = fTilt;
	m_fAPSpeed = m_fSpeed = fSpeed;

	RegisterMoveToCallback( &CServiceRstaEptm::MoveToCallback );

	// get the ball rolling
	MoveToCallback();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * MoveTo -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveToX
		(
		GFLOAT	fX,
		GFLOAT	fSpeed
		)
{
	bool	bResult = true;

	// TODO: normalize pan&tilt to actual degrees that we can handle

	//DbgPrint( "%s\n", __FUNCTION__ );

	m_fTargetPan = fX;
	m_fTargetTilt = m_fTilt;
	m_fAPSpeed = m_fSpeed = fSpeed;

	RegisterMoveToCallback( &CServiceRstaEptm::MoveToXCallback );

	// get the ball rolling
	MoveToXCallback();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * MoveTo -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveToY
		(
		GFLOAT	fY,
		GFLOAT	fSpeed
		)
{
	bool	bResult = true;

	// TODO: normalize pan&tilt to actual degrees that we can handle

	//DbgPrint( "%s\n", __FUNCTION__ );

	m_fTargetPan = m_fPan;
	m_fTargetTilt = fY;
	m_fAPSpeed = m_fSpeed = fSpeed;

	RegisterMoveToCallback( &CServiceRstaEptm::MoveToYCallback );

	// get the ball rolling
	MoveToYCallback();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * MoveToStop -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::MoveToStop
		(
		void
		)
{
	unsigned char	buffer[SENDSIZE];

	DbgPrint( "%s", __FUNCTION__ );

	m_oMutex.Lock();
	m_fTargetPan = m_fPan;
	m_fTargetTilt = m_fTilt;
	m_oMutex.Unlock();

	UnregisterMoveToCallback( &CServiceRstaEptm::MoveToCallback );
	CommandStop( buffer, sizeof(buffer) );
	AppendAction( CMD_Move, GFLOAT_0, GFLOAT_0, buffer, sizeof(buffer) );

	DbgPrint( ".\n" );
}


/*---------------------------------------------------------------------+\

 * RegisterMoveToCallback -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::RegisterMoveToCallback
		(
		FuncCallbackPtr p
		)
{
	m_pMoveCallback = p;
}


/*---------------------------------------------------------------------+\

 * UnregisterMoveToCallback -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::UnregisterMoveToCallback
		(
		FuncCallbackPtr //p
		)
{
	m_pMoveCallback = 0;
}


/*---------------------------------------------------------------------+\

 * MoveToCallback -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveToCallback
		(
		void
		)
{
	bool			bResult = true;
	unsigned char	buffer[SENDSIZE];

	GFLOAT	fPan;
	GFLOAT	fTilt;

	//m_oMutex.Lock();
	fPan = m_fPan;
	fTilt = m_fTilt;
	//m_oMutex.Unlock();

	//DbgPrint( "%s: p=%f, t=%f\n", __FUNCTION__, m_fTargetPan, m_fTargetTilt );

	GFLOAT	fNewPan = fPan - m_fTargetPan;
	GFLOAT	fNewTilt = fTilt - m_fTargetTilt;
	GFLOAT	fLen = (GFLOAT)::sqrt( fNewPan * fNewPan  +  fNewTilt * fNewTilt );

	if ( fLen < GFLOAT_1_2 )
	{
		if ( m_pMoveTargetEvent )
			(this->*m_pMoveTargetEvent)( fPan, fTilt, true );
		//BroadcastToClients();
	}
	else
	{
		// normalize the vector
		if ( GFLOAT_EPSILON < fLen )
		{
			fNewPan = fNewPan / fLen;
			fNewTilt = fNewTilt / fLen;
		}
		else
		{
			fNewPan = GFLOAT_1;
			fNewTilt = GFLOAT_0;
		}

		GFLOAT	fSpeed;
		if ( GFLOAT(4) < fLen )
			fSpeed = m_fAPSpeed;
		else
			fSpeed = fLen / GFLOAT(4) * (m_fAPSpeed - GFLOAT(0.125f));
		if ( m_fAPSpeed < fSpeed )
			fSpeed = m_fAPSpeed;
		if ( fSpeed < GFLOAT(0.125) )
			fSpeed = GFLOAT(0.125);
		fNewPan *= fSpeed;
		fNewTilt *= fSpeed;


		//DbgPrint( "%s: newpan=%f, newtilt=%f\n", __FUNCTION__, fNewPan, fNewTilt );


		CommandMove( buffer, sizeof(buffer), fNewPan, fNewTilt );
		AppendAction( CMD_Move, fNewPan, fNewTilt, buffer, sizeof(buffer) );

	}


	return bResult;
}

/*---------------------------------------------------------------------+\

 * MoveToCallback -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveToXCallback
		(
		void
		)
{
	bool			bResult = true;
	unsigned char	buffer[SENDSIZE];

	GFLOAT	fPan;
	GFLOAT	fTilt;

	//m_oMutex.Lock();
	fPan = m_fPan;
	fTilt = m_fTilt;
	//m_oMutex.Unlock();

	//DbgPrint( "%s: p=%f, t=%f\n", __FUNCTION__, m_fTargetPan, m_fTargetTilt );

	GFLOAT	fNewPan = fPan - m_fTargetPan;
	GFLOAT	fLen = fabsf(fNewPan);

	if ( fLen < GFLOAT_1_2 )
	{
		if ( m_pMoveTargetEvent )
			(this->*m_pMoveTargetEvent)( fPan, fTilt, true );
		//BroadcastToClients();
	}
	else
	{
		// normalize the vector
		if ( GFLOAT_EPSILON < fLen )
		{
			fNewPan = fNewPan / fLen;
		}
		else
		{
			fNewPan = GFLOAT_1;
		}

		GFLOAT	fSpeed;
		if ( GFLOAT(4) < fLen )
			fSpeed = m_fAPSpeed;
		else
			fSpeed = fLen / GFLOAT(4) * (m_fAPSpeed - GFLOAT(0.125f));
		fSpeed = umin(m_fAPSpeed, fSpeed);
		fSpeed = umax( fSpeed, GFLOAT(0.125) );
		fNewPan *= fSpeed;

		CommandMove( buffer, sizeof(buffer), fNewPan, GFLOAT_0 );
		AppendAction( CMD_Move, fNewPan, GFLOAT_0, buffer, sizeof(buffer) );

	}


	return bResult;
}


/*---------------------------------------------------------------------+\

 * MoveToCallback -

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::MoveToYCallback
		(
		void
		)
{
	bool			bResult = true;
	unsigned char	buffer[SENDSIZE];

	GFLOAT	fPan;
	GFLOAT	fTilt;

	//m_oMutex.Lock();
	fPan = m_fPan;
	fTilt = m_fTilt;
	//m_oMutex.Unlock();

	GFLOAT	fNewTilt = fTilt - m_fTargetTilt;
	GFLOAT	fLen = fabsf(fNewTilt);

	if ( fLen < GFLOAT_1_2 )
	{
		if ( m_pMoveTargetEvent )
			(this->*m_pMoveTargetEvent)( fPan, fTilt, true );
		//BroadcastToClients();
	}
	else
	{
		// normalize the vector
		if ( GFLOAT_EPSILON < fLen )
		{
			fNewTilt = fNewTilt / fLen;
		}
		else
		{
			fNewTilt = GFLOAT_1;
		}

		GFLOAT	fSpeed;
		if ( GFLOAT(4) < fLen )
			fSpeed = m_fAPSpeed;
		else
			fSpeed = fLen / GFLOAT(4) * (m_fAPSpeed - GFLOAT(0.125f));
		if ( m_fAPSpeed < fSpeed )
			fSpeed = m_fAPSpeed;
		if ( fSpeed < GFLOAT(0.125) )
			fSpeed = GFLOAT(0.125);
		fNewTilt *= fSpeed;

		CommandMove( buffer, sizeof(buffer), GFLOAT_0, fNewTilt );
		AppendAction( CMD_Move, GFLOAT_0, fNewTilt, buffer, sizeof(buffer) );

	}


	return bResult;
}


/*---------------------------------------------------------------------+\

 * SetMoveTargetEvent -

\+---------------------------------------------------------------------*/
void	CServiceRstaEptm::SetMoveTargetEvent
		(
		MoveTargetEventPtr	p
		)
{
	m_pMoveTargetEvent = p;
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

 * FindInternalInterface - COM overload for interface query

\+---------------------------------------------------------------------*/
void*	CServiceRstaEptm::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	p = inherited::FindInternalInterface( rIID );
	if ( !p )
	{
		if ( rIID == IXID_IPanAndTilt )
			p = INTERFACE_THIS( IPanAndTiltPtr );
	}

	return p;
}

/*--------------------------------------------------------------------+\

 * Load - XML class data loader

\+---------------------------------------------------------------------*/
bool	CServiceRstaEptm::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = true;

	bResult = inherited::Load( pConfig, pLib );

	//m_deviceName = pConfig->GetID();

	CCharString			sPort;
	unsigned long		nBaud;
	unsigned int		nDataBits;
	GFLOAT				fStopBits;
	CSerial::EStopBits	eStopBits;
	CSerial::EParitys	eParity;
	CSerial::EFlow		eFlow;

	VPluginConfiguration::EnumDatum PLGParity[]
	= {
		{ CSerial::PAR_NONE, "NONE" },
		{ CSerial::PAR_ODD, "ODD" },
		{ CSerial::PAR_EVEN, "EVEN" },
		{ CSerial::PAR_MARK, "MARK" },
		{ CSerial::PAR_SPACE, "SPACE" }
	};

	VPluginConfiguration::EnumDatum	PLGFlow[]
	= {
		{ CSerial::FLOW_OFF, "OFF" },
		{ CSerial::FLOW_HARDWARE, "HARDWARE" },
		{ CSerial::FLOW_XONXOFF, "XONXOFF" }
	};


	m_fAPRowSpacing = pConfig->GetParameterAsFloat( "Auto Pan Row Spacing", GFLOAT(15.0) );


	sPort = pConfig->GetParameterAsString( "EPTM::Port", "" );
	nBaud = pConfig->GetParameterAsUnsigned( "EPTM::Baud", 19200 );
	nDataBits = pConfig->GetParameterAsUnsigned( "EPTM::DataBits", 8 );
	fStopBits = pConfig->GetParameterAsFloat( "EPTM::StopBits", 1 );
	if ( fStopBits == GFLOAT_1 )
		eStopBits = CSerial::STOP_1;
	else if ( fStopBits == GFLOAT(1.5) )
		eStopBits = CSerial::STOP_1_5;
	else if ( fStopBits == GFLOAT_2 )
		eStopBits = CSerial::STOP_2;
	else
		eStopBits = CSerial::STOP_1;
	eParity = (CSerial::EParitys)pConfig->GetParameterAsEnum( "EPTM::Parity", PLGParity,
										sizeof(PLGParity)/sizeof(VPluginConfiguration::EnumDatum),
										0
										);
	eFlow = (CSerial::EFlow)pConfig->GetParameterAsEnum( "EPTM::Flow", PLGFlow,
										sizeof(PLGFlow)/sizeof(VPluginConfiguration::EnumDatum),
										0
										);

	m_oEptmPort.SetPortName( sPort.Pointer() );
	m_oEptmPort.SetBaud( nBaud );
	m_oEptmPort.SetDataBits( nDataBits );
	m_oEptmPort.SetStopBits( eStopBits );
	m_oEptmPort.SetHandshaking( eFlow );

	DbgPrint("EPTM::Port = %s\n", sPort.Pointer());
	DbgPrint("EPTM::Baud = %d\n", nBaud );
	DbgPrint("EPTM::DataBits = %d\n", nDataBits);
	DbgPrint("EPTM::StopBits = %d\n", eStopBits);
	DbgPrint("EPTM::Flow = %d\n", eFlow);


	sPort = pConfig->GetParameterAsString( "CMM::Port", "" );
	nBaud = pConfig->GetParameterAsUnsigned( "CMM::Baud", 19200 );
	nDataBits = pConfig->GetParameterAsUnsigned( "CMM::DataBits", 8 );
	fStopBits = pConfig->GetParameterAsFloat( "CMM::StopBits", 1 );
	if ( fStopBits == GFLOAT_1 )
		eStopBits = CSerial::STOP_1;
	else if ( fStopBits == GFLOAT(1.5) )
		eStopBits = CSerial::STOP_1_5;
	else if ( fStopBits == GFLOAT_2 )
		eStopBits = CSerial::STOP_2;
	else
		eStopBits = CSerial::STOP_1;
	eParity = (CSerial::EParitys)pConfig->GetParameterAsEnum( "CMM::Parity", PLGParity,
										sizeof(PLGParity)/sizeof(VPluginConfiguration::EnumDatum),
										0
										);
	eFlow = (CSerial::EFlow)pConfig->GetParameterAsEnum( "CMM::Flow", PLGFlow,
										sizeof(PLGFlow)/sizeof(VPluginConfiguration::EnumDatum),
										0
										);

	m_oCmmPort.SetPortName( sPort.Pointer() );
	m_oCmmPort.SetBaud( nBaud );
	m_oCmmPort.SetDataBits( nDataBits );
	m_oCmmPort.SetStopBits( eStopBits );
	m_oCmmPort.SetHandshaking( eFlow );
	m_oCmmPort.SetParity( eParity );

	DbgPrint("CMM::Port = %s\n", sPort.Pointer());
	DbgPrint("CMM::Baud = %d\n", nBaud );
	DbgPrint("CMM::DataBits = %d\n", nDataBits);
	DbgPrint("CMM::StopBits = %d\n", eStopBits);
	DbgPrint("CMM::Flow = %d\n", eFlow);
	DbgPrint("CMM::Parity = %d\n", eParity);


	return bResult;
}


}}
