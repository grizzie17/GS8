/*---------------------------------------------------------------------+\
|
|	CmdTouchCalibrate.h  --  Header for CmdTouchCalibrate Plugin
|
|	Purpose:

		Provide support for touch screen calibration

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
	18-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CmdTouchCalibrate
#define _H_CmdTouchCalibrate
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginCommand.h"
#include "IMouseTransform.h"

#include "THash.h"
#include "CCharString.h"
#include "CCharStringHash.h"
#include "CVariantData.h"
#include "VDictionary.h"
#include "CMatrix3x3.h"


namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#define	TOUCH_K_POINTCOUNT	5
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CmdTouchCalibrate*		CmdTouchCalibratePtr;
typedef class CmdTouchCalibrate&		CmdTouchCalibrateRef;
typedef const class CmdTouchCalibrate&	ConstCmdTouchCalibrateRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CmdTouchCalibrate : public VPluginCommand,
						implements_ IMouseTransform
{
//	class lifecycle  ----------------------------------------------------
public:

	COM_LIFECYCLE(CmdTouchCalibrate);

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;


	//	IMouseTransform
	virtual
	bool	SetSize
			(
			long	nWidth,
			long	nHeight
			);


	virtual
	bool	Transform
			(
			GFLOAT*		pOutX,
			GFLOAT*		pOutY,
			GFLOAT&		rInX,
			GFLOAT&		rInY
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct UPoint
	{
		GFLOAT	x;
		GFLOAT	y;
	} UPoint;

//	protected functions  ------------------------------------------------

	// registered commands
	bool		Install( Yogi::Common::ConstCVariantDataRef r );
	bool		Calibrate( Yogi::Common::ConstCVariantDataRef	r );
	bool		Start( Yogi::Common::ConstCVariantDataRef	r );
	bool		Point( Yogi::Common::ConstCVariantDataRef	r );
	bool		Timeout( Yogi::Common::ConstCVariantDataRef r );

	bool		SaveData( void );
	bool		LoadData( void );

	Yogi::Core::CCharString	BuildPath( void );

	bool		GenerateMatrix( void );
	bool		ValidateMatrix( void );
	void		MidPoint( GFLOAT* px, GFLOAT* py, UPoint& pt1, UPoint& pt2 );

	void		SetVariable( int n );

//	protected data  -----------------------------------------------------

	VDictionaryPtr			m_pDictionary;

	VDictionary::Selector	m_nCmdInstall;
	VDictionary::Selector	m_nCmdCalibrate;
	VDictionary::Selector	m_nCmdStart;
	VDictionary::Selector	m_nCmdPoint;
	VDictionary::Selector	m_nCmdTimeout;

	VDictionary::Selector	m_nUPointX;
	VDictionary::Selector	m_nUPointY;
	VDictionary::Selector	m_nUScreenX;
	VDictionary::Selector	m_nUScreenY;
	VDictionary::Selector	m_nUPanel;
	Yogi::Common::CVariantData	m_vUPanel;
	VDictionary::Selector	m_nUPhase;
	VDictionary::Selector	m_nUPrompt;

	Yogi::Common::CMatrix3x3	m_tMatrix;
	Yogi::Core::CCharString	m_sFilePath;
	Yogi::Core::CCharString	m_sFilename;
	GFLOAT					m_fTolerance;	// number of pixels for fudge
	GFLOAT					m_fScreenWidth;
	GFLOAT					m_fScreenHeight;

	int		m_nCount;

	UPoint	m_aPoints[TOUCH_K_POINTCOUNT];	// reference display points
	UPoint	m_aScreen[TOUCH_K_POINTCOUNT];	// touch screen points




private:
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
			VDictionary::Selector				selCommand,
			Yogi::Common::ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			Yogi::Common::VPluginConfigurationPtr	pConfig,
			Yogi::Common::VPluginLibraryPtr			pLib
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



#endif /* _H_CmdTouchCalibrate */
