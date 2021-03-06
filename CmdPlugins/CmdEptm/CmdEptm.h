/*---------------------------------------------------------------------+\
|
|	CmdEptm.h  --  Header for CmdEptm Plugin
|
|	Purpose:

		Provide support Pan and Tilt Module

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
	18-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdEptm
#define _H_CmdEptm
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"
#include "IMouseTransform.h"
#include "IPanAndTilt.h"
#include "IPanAndTiltClient.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMatrix3x3.h"
#include "CMutex.h"


/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {

#define	TOUCH_K_POINTCOUNT	5
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CmdEptm*			CmdEptmPtr;
typedef class CmdEptm&			CmdEptmRef;
typedef const class CmdEptm&	ConstCmdEptmRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdEptm : public VPluginCommand,
				implements_ IPanAndTiltClient
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdEptm);

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	virtual
	Yogi::Core::NResult
			EptmState
			(
			GFLOAT		fPan,
			GFLOAT		fTilt,
			long		mFlags
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct UPoint
	{
		long	x;
		long	y;
	} UPoint;

//	protected functions  ------------------------------------------------

	// registered commands
	bool		JoystickStart( Yogi::Common::ConstCVariantDataRef r );
	bool		JoystickMove( Yogi::Common::ConstCVariantDataRef r );
	bool		JoystickStop( Yogi::Common::ConstCVariantDataRef r );

	bool		AutoPanStart( Yogi::Common::ConstCVariantDataRef r );
	bool		AutoPanStop( Yogi::Common::ConstCVariantDataRef r );
	bool		AutoPanDefineLeft( Yogi::Common::ConstCVariantDataRef r );
	bool		AutoPanDefineRight( Yogi::Common::ConstCVariantDataRef r );
	bool		AutoPanChangeSpeed( Yogi::Common::ConstCVariantDataRef r );	// arugment +/-

	bool		EPTMCalculate( Yogi::Common::ConstCVariantDataRef r );

	bool		EPTMHome( Yogi::Common::ConstCVariantDataRef r );
	bool		EPTMSetHome( Yogi::Common::ConstCVariantDataRef r );

	bool		EPTMSlew( Yogi::Common::ConstCVariantDataRef r );
	bool		EPTMSetSlewCenter( Yogi::Common::ConstCVariantDataRef r );

	bool		SendJoystick( GFLOAT x, GFLOAT y );



//	protected data  -----------------------------------------------------

	IPanAndTiltPtr			m_pIPanAndTilt;

	VDictionaryPtr			m_pDictionary;

	VDictionary::Selector	m_nCmdJoystickStart;
	VDictionary::Selector	m_nCmdJoystickMove;
	VDictionary::Selector	m_nCmdJoystickStop;

	VDictionary::Selector	m_nCmdAutoPanStart;
	VDictionary::Selector	m_nCmdAutoPanStop;
	VDictionary::Selector	m_nCmdAutoPanDefineLeft;
	VDictionary::Selector	m_nCmdAutoPanDefineRight;
	VDictionary::Selector	m_nCmdAutoPanChangeSpeed;	// arugment +/-

	VDictionary::Selector	m_nCmdEptmCalculate;

	VDictionary::Selector	m_nCmdEptmHome;
	VDictionary::Selector	m_nCmdEptmSetHome;

	VDictionary::Selector	m_nCmdEptmSlew;
	VDictionary::Selector	m_nCmdEptmSetSlewCenter;

	VDictionary::Selector	m_nUJoystickOriginX;
	VDictionary::Selector	m_nUJoystickOriginY;
	VDictionary::Selector	m_nUJoystickRadius;

	VDictionary::Selector	m_nUJoystickPositionX;
	VDictionary::Selector	m_nUJoystickPositionY;

	VDictionary::Selector	m_nUEPTMPositionX;
	VDictionary::Selector	m_nUEPTMPositionY;

	VDictionary::Selector	m_nUEPTMFlags;

	VDictionary::Selector	m_nIX;
	VDictionary::Selector	m_nIY;

	VDictionary::Selector	m_nSScreenWidth;
	VDictionary::Selector	m_nSScreenHeight;


	long				m_nRadius;
	UPoint				m_tCenter;
	UPoint				m_tRaw;
	UPoint				m_tPosition;

	GFLOAT				m_fPan;
	GFLOAT				m_fTilt;

	GFLOAT				m_fPanLeft;
	GFLOAT				m_fTiltTop;
	GFLOAT				m_fPanRight;
	GFLOAT				m_fTiltBottom;
	GFLOAT				m_fPanSpeed;

	GFLOAT				m_fSlewCenterX;
	GFLOAT				m_fSlewCenterY;


	bool				m_bActive;
	long				m_mFlags;		// state flags from EPTM

	bool				m_bDirty;

	Yogi::Core::CMutex	m_oMutex;



private:
//	private types  ------------------------------------------------------

	typedef	VPluginCommand	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
protected:
	//	VSupports
	virtual
	void*	FindInternalInterface
			(
			Yogi::Common::ConstIXIDRef	rIID
			);

	virtual
	void	FinalRelease
			(
			void
			);

public:
	//	ICommandPlugin
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VCommandSetupPtr		pCommandSetup
			);

	virtual
	bool	ProcessRequest
			(
			VDictionary::Selector	selCommand,
			Yogi::Common::ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr		pLib
			);


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



#endif /* _H_CmdEptm */
