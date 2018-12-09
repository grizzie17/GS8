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
	bool		Install( ConstCVariantDataRef r );
	bool		Calibrate( ConstCVariantDataRef	r );
	bool		Start( ConstCVariantDataRef	r );
	bool		Point( ConstCVariantDataRef	r );
	bool		Timeout( ConstCVariantDataRef r );

	bool		SaveData( void );
	bool		LoadData( void );

	CCharString	BuildPath( void );

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
	CVariantData			m_vUPanel;
	VDictionary::Selector	m_nUPhase;
	VDictionary::Selector	m_nUPrompt;

	CMatrix3x3				m_tMatrix;
	CCharString				m_sFilePath;
	CCharString				m_sFilename;
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
			ConstIXIDRef	rIID
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
			ConstCVariantDataRef	vData
			);

	//	IPluginLoadConfiguration
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
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
