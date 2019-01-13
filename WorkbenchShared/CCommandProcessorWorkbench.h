/*---------------------------------------------------------------------+\
|
|	CCommandProcessorWorkbench.h  --  Example command processor class
|
|	Purpose:
|
| optional topics (delete if not used)
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
	26-Mar-2010			J.Griswold		(Reviewed by: M.Rose) [1]
		Add support for new ESA vehicle
	18-Feb-2010			J.Griswold		(Reviewed by: M.Rose)
		Reworked to use base class as CCommandProcessor
	10-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add "new" commands for editing cameras
		Also add "Blackout" command
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add commands for editing cameras
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for the new "Constants" dictionary page
	25-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add command to toggle which VehicleData XML processor
		that we are going to use.
	12-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add access to the Reload function on the application
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCommandProcessorWorkbench
#define _H_CCommandProcessorWorkbench
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCommandProcessorForPlugins.h"

#include "CVariantData.h"
#include "CApplicationGauge.h"
#include "CDictPageVariantRead.h"
#include "VDictionary.h"


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
typedef class CCommandProcessorWorkbench*		CCommandProcessorWorkbenchPtr;
typedef class CCommandProcessorWorkbench&		CCommandProcessorWorkbenchRef;
typedef const class CCommandProcessorWorkbench&	ConstCCommandProcessorWorkbenchRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CCommandProcessorWorkbench : public CCommandProcessorForPlugins
{
//	class lifecycle  ----------------------------------------------------
public:
					CCommandProcessorWorkbench();
	virtual			~CCommandProcessorWorkbench();

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------




protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


	// functions

	//VDictionary::Selector	m_cSystemShutdown;
	//long					m_nSystemShutdown;


	//VDictionary::Selector	m_cViewLayout;
	//VDictionary::Selector	m_cVideoFeed1;
	//VDictionary::Selector	m_cVideoFeed2;
	//VDictionary::Selector	m_cVideoFeed3;
	//VDictionary::Selector	m_cVideoFeed4;

	//long					m_nViewLayout;
	//long					m_nVideoFeed1;
	//long					m_nVideoFeed2;
	//long					m_nVideoFeed3;
	//long					m_nVideoFeed4;

	// cached values
	Yogi::Common::CVariantData		m_xViewLayout;
	Yogi::Common::CVariantData		m_xVideoFeed1;
	Yogi::Common::CVariantData		m_xVideoFeed2;
	Yogi::Common::CVariantData		m_xVideoFeed3;
	Yogi::Common::CVariantData		m_xVideoFeed4;

	bool					m_bVideoDirty;


	VDictionary::Selector	m_cEditCamera;

	VDictionary::Selector	m_cCameraAutoCalibration;
	VDictionary::Selector	m_cCameraOnePointCalibration;
	VDictionary::Selector	m_cCameraPolarity;
	VDictionary::Selector	m_cCameraZoomMode;
	VDictionary::Selector	m_cCameraZoom;
	VDictionary::Selector	m_cCameraBrightness;
	VDictionary::Selector	m_cCameraContrast;
	VDictionary::Selector	m_cCameraSharpness;
	VDictionary::Selector	m_cCameraModeControl;
	VDictionary::Selector	m_cReverse;

	long					m_nCameraCapAutoCalibration;
	long					m_nCameraCapOnePointCalibration;
	long					m_nCameraCapPolarity;
	long					m_nCameraCapZoomMode;
	long					m_nCameraCapZoom;
	long					m_nCameraCapBrightness;
	long					m_nCameraCapContrast;
	long					m_nCameraCapSharpness;
	long					m_nCameraCapModeControl;
	long					m_nReverse;

	VDictionary::Selector	m_cUDPDayBrightnessIncrease;
	VDictionary::Selector	m_cUDPDayBrightnessDecrease;
	VDictionary::Selector	m_cUDPDayContrastIncrease;
	VDictionary::Selector	m_cUDPDayContrastDecrease;
	VDictionary::Selector	m_cUDPDaySharpnessIncrease;
	VDictionary::Selector	m_cUDPDaySharpnessDecrease;

	VDictionary::Selector	m_cTogglePolarity;
	VDictionary::Selector	m_cIRGainIncrease;
	VDictionary::Selector	m_cIRGainDecrease;
	VDictionary::Selector	m_cIRLevelIncrease;
	VDictionary::Selector	m_cIRLevelDecrease;
	VDictionary::Selector	m_cIRPerformOnePtCal;
	VDictionary::Selector	m_cIRToggleAutoCalMode;
	VDictionary::Selector	m_cIROpenShutter;
	VDictionary::Selector	m_cIRCloseShutter;
	VDictionary::Selector	m_cIRPowerDown;

	VDictionary::Selector	m_cIRULSetAGCModeNormal;
	VDictionary::Selector	m_cIRULSetAGCModeLAP;
	VDictionary::Selector	m_cIRULSigmaIncrease;
	VDictionary::Selector	m_cIRULSigmaDecrease;
	VDictionary::Selector	m_cIRULSharpenIncrease;
	VDictionary::Selector	m_cIRULSharpenDecrease;
	VDictionary::Selector	m_cIRULToggleZoomMode;
	VDictionary::Selector	m_cIRULZoomIncrease;
	VDictionary::Selector	m_cIRULZoomDecrease;



private:
//	private functions  --------------------------------------------------

	typedef	CCommandProcessorForPlugins	inherited;

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VFunctionProcessor
public:
	virtual bool	ProcessRequest
					(
					VDictionary::Selector				sel,
					Yogi::Common::ConstCVariantDataRef	vData
					);

	//	CCommandProcessor
public:
	virtual void	InitializeFunctions( void );


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



#endif /* _H_CCommandProcessorWorkbench */
