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
	12-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CServiceRstaEptm
#define _H_CServiceRstaEptm
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/

#include "VPluginService.h"

#include "IService.h"
#include "IPanAndTilt.h"

#include "UPlatform.h"
#include "UPlatformThreads.h"
#include "UNResult.h"
#include "CMutex.h"
#include "CSemaphore.h"
#include "CSerial.h"
#include "TQueue.h"
#include "TArray.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CServiceRstaEptm*			CServiceRstaEptmPtr;
typedef class CServiceRstaEptm&			CServiceRstaEptmRef;
typedef const class CServiceRstaEptm&	ConstCServiceRstaEptmRef;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

class CServiceRstaEptm : public VPluginService,
						implements_ IPanAndTilt
{
//	class lifecycle  ----------------------------------------------------
	COM_LIFECYCLE( CServiceRstaEptm );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;



	//	IPanAndTilt
	virtual
	NResult	MoveViaSpeed
			(
			GFLOAT		fPanNorm,	// IN:	normalized speed for rotation
			GFLOAT		fTiltNorm	// IN:	normalized speed for elevation
			);

	virtual
	NResult	MoveDelta
			(
			GFLOAT		fPan,
			GFLOAT		fTilt,
			GFLOAT		fSpeed
			);


	virtual
	NResult	MoveAbsolute
			(
			GFLOAT		fPan,
			GFLOAT		fTilt,
			GFLOAT		fSpeed
			);

	virtual
	NResult	AutoPan
			(
			GFLOAT		fPanLeft,		// left side of virtual window
			GFLOAT		fTiltTop,
			GFLOAT		fPanRight,		// right side of virtual window
			GFLOAT		fTiltBottom,
			GFLOAT		fSpeed			//	normalized speed value
			);

	virtual
	NResult	MoveHome
			(
			void
			);

	virtual
	NResult	SetHome
			(
			void
			);

	virtual
	NResult	GetPosition
			(
			GFLOAT*		pPan,	// OUT:	rotation position in degrees
			GFLOAT*		pTilt	// OUT: elevation position in degrees
			);

	virtual
	NResult	RegisterClient
			(
			IPanAndTiltClientPtr p
			);

	virtual
	NResult	UnregisterClient
			(
			IPanAndTiltClientPtr p
			);

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

protected:
//	protected types  ----------------------------------------------------

	typedef bool (CServiceRstaEptm::*FuncCallbackPtr)( void );
	typedef void (CServiceRstaEptm::*MoveTargetEventPtr)( GFLOAT fPan, GFLOAT fTilt, bool bCompleted );

	typedef enum
	{
		AP_None = 0,
		AP_MoveLeft,	// panning to the left
		AP_MoveRight,	// panning to the right
		AP_RowLeft,		// changing row on left side
		AP_RowRight,	// changing row on right side
		AP_Home			// moving to lower-left corner
	} EAutoPanState;

	typedef enum
	{
		k_ByteStart	= 0x02,		// start byte
		k_ByteStop	= 0x03		// stop byte
	} EByteCtl;

	typedef enum
	{
		k_PanLeft	= 0x6C,
		k_PanRight	= 0x72,
		k_PanStop	= 0x73
	} EPan;

	typedef enum
	{
		k_TiltDown	= 0x64,
		k_TiltUp	= 0x75,
		k_TiltStop	= 0x73
	} ETilt;

	typedef enum
	{
		CMD_None = 0,
		CMD_Move,
		CMD_Home,
		CMD_SetHome,
		CMD_ZeroCalibration,
		CMD_SetSoftLimit
	} ECommand;


	typedef struct MoveEntry
	{
		ECommand	eCmd;
		GFLOAT		fPanNorm;
		GFLOAT		fTiltNorm;
		unsigned char buffer[8];

		MoveEntry() : eCmd( CMD_None ), fPanNorm( GFLOAT_0 ), fTiltNorm( GFLOAT_0 ) {};
		MoveEntry( int ) : eCmd( CMD_None ), fPanNorm( GFLOAT_0 ), fTiltNorm( GFLOAT_0 ) {};
		MoveEntry( const MoveEntry& r )
			: eCmd( r.eCmd ), fPanNorm( r.fPanNorm ), fTiltNorm( r.fTiltNorm )
			{
				memcpy_s( buffer, sizeof(buffer), r.buffer, sizeof(r.buffer) );
			};
	} MoveEntry;

	typedef	TQueue<MoveEntry>	MoveQueue;

	//typedef struct PTMControl
	//{
	//	unsigned char	start;		//	0x02
	//	unsigned char	address;	//	0x60
	//	unsigned char	panDir;
	//	unsigned char	tiltDir;
	//	unsigned char	panSpeed;
	//	unsigned char	tiltspeed;
	//	unsigned char	checksum;
	//	unsigned char	stop;		//	0x03
	//} PTMControl, *PTMControlPtr;


	//typedef struct PTMResponse
	//{
	//	unsigned char	start;		//	0x04
	//	unsigned char	xCounterHigh;
	//	unsigned char	xCounterLow;
	//	unsigned char	yCounterHigh;
	//	unsigned char	yCounterLow;
	//	unsigned char	leftSoftLimit;
	//	unsigned char	rightSoftLimit;
	//	unsigned char	downSoftLimit;
	//	unsigned char	upSoftLimit;
	//	unsigned char	panHomeHigh;
	//	unsigned char	panHomeLow;
	//	unsigned char	tiltHomeHigh;
	//	unsigned char	tiltHomeLow;
	//	unsigned char	checksum;
	//} PTMResponse, *PTMResponsePtr;


	//typedef struct Device
	//{
	//	struct termios TermOptions;
	//	pthread_t      Thread;
	//	int            SerialFd;
	//	CCharString    DevNodeName;
	//	CCharString    Parity;
	//	CCharString    FlowControl;
	//	unsigned long  BaudRate;
	//	unsigned long  DataBits;
	//	unsigned long  StopBits;
	//} tDevice, *tDevicePtr;

//	protected functions  ------------------------------------------------


	unsigned char
			MakeSpeed
			(
			GFLOAT	fSpeed
			);

	GFLOAT	ScaleFromSpeed
			(
			unsigned char x
			);

	bool	AppendAction
			(
			ECommand	eCmd,
			GFLOAT		fPanNorm,
			GFLOAT		fTiltNorm,
			unsigned char*	pBuffer,
			long		nSize
			);


	long	CommandMove
			(
			unsigned char*	pBuffer,
			long			nSize,
			GFLOAT			fPanNorm,
			GFLOAT			fTiltNorm
			);

	long	CommandHome
			(
			unsigned char*	pBuffer,
			long			nSize
			);

	long	CommandStop
			(
			unsigned char*	pBuffer,
			long			nSize
			);

	long	CommandSetHome
			(
			unsigned char*	pBuffer,
			long			nSize
			);

	long	CommandZeroCalibration
			(
			unsigned char*	pBuffer,
			long			nSize
			);

	long	CommandSetSoftLimit
			(
			unsigned char*	pBuffer,
			long			nSize,
			long			nLeft,
			long			nRight,
			long			nDown,
			long			nUp
			);

	static
	UThreadRtn
			EptmTxThreadGlue
			(
			void*	pThis
			);

	UThreadRtn
			EptmTxThread
			(
			void
			);

	long	EptmRead
			(
			unsigned char* buffer,
			long nSize
			);

	static
	UThreadRtn
			EptmRxThreadGlue
			(
			void*	pThis
			);

	UThreadRtn
			EptmRxThread
			(
			void
			);

	static
	UThreadRtn
			CmmThreadGlue
			(
			void*	pThis
			);

	UThreadRtn
			CmmThread
			(
			void
			);

	long	CmmRead
			(
			unsigned char* buffer,
			long nSize
			);

	bool	MoveTo
			(
			GFLOAT	fPan,	// degrees
			GFLOAT	fTilt,	// degrees
			GFLOAT	fSpeed	// normalized speed
			);

	bool	MoveToX
			(
			GFLOAT	fX,
			GFLOAT	fSpeed
			);

	bool	MoveToY
			(
			GFLOAT	fY,
			GFLOAT	fSpeed
			);

	void	RegisterMoveToCallback
			(
			FuncCallbackPtr p
			);

	void	UnregisterMoveToCallback
			(
			FuncCallbackPtr p
			);

	void	MoveToStop
			(
			void
			);

	bool	MoveToCallback
			(
			void
			);

	bool	MoveToXCallback
			(
			void
			);

	bool	MoveToYCallback
			(
			void
			);

	void	SetMoveTargetEvent
			(
			MoveTargetEventPtr p
			);


	bool	AutoPanThreadStart
			(
			void
			);

	bool	AutoPanThreadStop
			(
			void
			);

	void	AutoPanMoveTargetEvent
			(
			GFLOAT	fPan,
			GFLOAT	fTilt,
			bool	bCompleted
			);

	void	MoveAbsoluteTargetEvent
			(
			GFLOAT	fPan,
			GFLOAT	fTilt,
			bool	bCompleted
			);


	void	BroadcastToClients(void);
	void	BroadcastToClientsNow(void);


	bool	ParseEptmResponse
			(
			unsigned char*	pBuffer,
			long			nSize
			);

	bool	ParseCmmMessage
			(
			unsigned char*	pBuffer,
			long			nSize
			);


	unsigned char
			Checksum
			(
			unsigned char*	p,
			long			nCount
			);

	int		intFromBytes
			(
			unsigned char	nLow,
			unsigned char	nHigh
			);

	GFLOAT	floatFromHalf
			(
			unsigned short	n
			);

	GFLOAT	degreesFromBytes
			(
			unsigned char	nLow,
			unsigned char	nHigh
			);

//	protected data  -----------------------------------------------------


	MoveQueue	m_oMoveQueue;


	// current position
	GFLOAT		m_fPan;
	GFLOAT		m_fTilt;

	GFLOAT		m_fSoftLeft;
	GFLOAT		m_fSoftTop;
	GFLOAT		m_fSoftRight;
	GFLOAT		m_fSoftBottom;

	GFLOAT		m_fHomePan;
	GFLOAT		m_fHomeTilt;

	GFLOAT		m_fPrevPan;		// position last broadcast to clients
	GFLOAT		m_fPrevTilt;
	long		m_nMilliBroadcast;
	bool		m_bMoving;

	GFLOAT		m_fTargetPan;	// used by MoveTo
	GFLOAT		m_fTargetTilt;

	GFLOAT		m_fSpeed;

	bool		m_bAutoPan;		// is auto-pan active?
	GFLOAT		m_fAPLeft;
	GFLOAT		m_fAPTop;
	GFLOAT		m_fAPRight;
	GFLOAT		m_fAPBottom;
	GFLOAT		m_fAPRow;
	GFLOAT		m_fAPRowSpacing;
	GFLOAT		m_fAPSpeed;
	EAutoPanState	m_eAPState;

	UThreadHdl	m_hEptmTx;
	CSemaphore	m_oEptmTxSem;
	UThreadHdl	m_hEptmRx;
	UThreadHdl	m_hCmm;

	CSerial		m_oEptmPort;
	CSerial		m_oCmmPort;

	TArray<IPanAndTiltClientPtr>	m_aClients;
	TArray<FuncCallbackPtr>			m_aCallbacks;

	BEGIN_IGNORE_WARNING( 4121 )	// forced alignment warning
	MoveTargetEventPtr		m_pMoveTargetEvent;
	FuncCallbackPtr			m_pMoveCallback;
	END_IGNORE_WARNING

	bool		m_bJoystickOnly;
	long		m_nMilliIdle;
	unsigned char	m_aNeutral[8];


private:
//	private types  ------------------------------------------------------

	typedef	VPluginService	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------


//============================== Overrides ==============================

	// VSupports
protected:
	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

	//	IPluginLoadConfiguration
public:
	virtual
	bool	Load
			(
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);

	//	IService
public:
	virtual
	NResult	Start
			(
			void
			);

	virtual
	NResult	Stop
			(
			void
			);



public:

private:
};


/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


}}


#endif /* _H_CServiceRstaEptm */
