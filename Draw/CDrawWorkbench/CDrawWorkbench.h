/*---------------------------------------------------------------------+\
|
|	CDrawWorkbench.h  --  Implementation of draw object for MS-Windows
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
	17-Feb-2012			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawWorkbench
#define _H_CDrawWorkbench
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregate.h"
#include "IDraw.h"
#include "IApplicationUser.h"
#include "CCharStringHash.h"

#include "Chronos.h"




namespace Yogi { namespace Common {
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

typedef class CDrawWorkbench*		CDrawWorkbenchPtr;
typedef class CDrawWorkbench&		CDrawWorkbenchRef;
typedef const class CDrawWorkbench&	ConstCDrawWorkbenchRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDrawWorkbench : public VPluginWithAggregate,
						implements_ Yogi::Gadget::IApplicationUser,
						implements_ IDraw
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawWorkbench );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IApplicationUser
	virtual
	bool	SetApplication
			(
			Yogi::Gadget::CApplicationGaugePtr	p	// IN:	application pointer
			);



public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------



protected:
//	protected types  ----------------------------------------------------

//	protected functions  ------------------------------------------------

//	protected data  -----------------------------------------------------


	IDrawPtr	m_pDraw;

	Yogi::Gadget::CApplicationGaugePtr
				m_pApplication;
	int			m_nFeed;

	THashTable< Yogi::Core::CCharString, VImagePtr >	m_oVideoCache;
	Chronos		m_oChronos;


private:

	typedef	VPluginWithAggregate	inherited;

//	private functions  --------------------------------------------------

//	private data  -------------------------------------------------------

//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

#if 0 //def _DEBUG
	virtual
	void	FinalRelease
			(
			void
			);

	virtual
	NRefCount
			InternalAddRef
			(
			void
			);

	virtual
	NRefCount
			InternalRelease
			(
			void
			);
#endif // _DEBUG

	//	IPluginLoadConfiguration
public:
	virtual
	bool	Load
			(
			VPluginConfigurationPtr	pConfig,
			VPluginLibraryPtr		pLib
			);


	//	IDrawTmx
public:
	virtual
	bool	begin
			(
			void
			);

	virtual
	bool	end
			(
			void
			);

	virtual
	bool	margin
			(
			int		nLeft,
			int		nTop,
			int		nRight,
			int		nBottom
			);

	virtual
	bool	push
			(
			GFLOAT	xPosition,
			GFLOAT	yPosition,
			GFLOAT	xShift,
			GFLOAT	yShift,
			GFLOAT	xAxis,
			GFLOAT	yAxis,
			GFLOAT	rotation,
			GFLOAT	scale
			);
	virtual
	bool	pop
			(
			void
			);

	//	IDraw
public:

	// window/screen re/size
	virtual bool	Size( long nWidth, long nHeight );

	virtual bool	BeginContext( EDrawContexts ctx );
	virtual bool	EndContext( void );
	virtual EDrawContexts
		CurrentContext( void );

	// identify if this draw object has context support
	virtual bool	SupportsContext( void );

	virtual bool	PushCropRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		);
	virtual bool	PopCropRectangle( void );

	virtual bool	RefreshRectangle
		(
		void
		);

	virtual bool	SetUpdateRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		);
	virtual bool	GetUpdateRectangle
		(
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		);


	virtual bool	DayMode( EDayModes eMode );

	// --- Style properties ---

	virtual bool	LineWidth( short nWidth );
	virtual bool	LineColor( Yogi::Core::ConstCColorRef rColor );
	virtual bool	FillColor( Yogi::Core::ConstCColorRef rColor );
	virtual bool	HaloColor( Yogi::Core::ConstCColorRef rColor );

	virtual bool	BackgroundColor( Yogi::Core::ConstCColorRef rColor );	// identify color to be used for background
	virtual bool	NightColor( ENightColorModes eMode );

	virtual bool	FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		);


	// --- Geometry graphics ---

	virtual bool	Line
		(
		GFLOAT	xStart,
		GFLOAT	yStart,
		GFLOAT	xEnd,
		GFLOAT	yEnd
		);


	// implemented as a Polyline
	virtual bool	Arc
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		);

	virtual bool	Circle
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius
		);

	virtual bool	Ellipse
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nHeight,
		GFLOAT	nWidth
		);

	// implemented as a Polygon
	virtual bool	Pie
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		);

	virtual bool	Polygon
		(
		long		nNumPoints,
		FPointPtr	pPointList
		);

	virtual bool	Polyline
		(
		long		nNumPoints,
		FPointPtr	pPointList
		);

	virtual bool	BeginPolygon
		(
		void
		);

	virtual bool	EndPolygon
		(
		void
		);

	virtual bool	BeginPolyline
		(
		void
		);

	virtual bool	EndPolyline
		(
		void
		);

	virtual bool	Polypoint
		(
		GFLOAT	x,
		GFLOAT	y
		);

	virtual bool	Rectangle
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		CORNERSTYLE	eStyle = C_SQUARE,
		GFLOAT		nCornerSize = 0.0f
		);

	virtual bool	TextString
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		EAlignments		eAlign,
		EVerticalAlignments	eVertAlign,
		const char*		sString,
		long			nCount = -1
		);

	virtual bool	Video
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		GFLOAT			nWidth,
		GFLOAT			nHeight,
		CVariantDataRef	rSource,
		EFitments		eFitment = F_FILL,
		EAlignments		eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign = V_MIDDLE,
		bool			bMirror = false
		);

	virtual bool	Image
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		GFLOAT			nWidth,
		GFLOAT			nHeight,
		const char*		sSource,
		EFitments		eFitment = F_FILL,
		EAlignments		eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign = V_MIDDLE
		);

	virtual bool	ImagePreloaded
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		GFLOAT			nWidth,
		GFLOAT			nHeight,
		VImagePtr		pImage,
		EFitments		eFitment = F_FILL,
		EAlignments		eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign = V_MIDDLE
		);

	virtual bool	ImageLoadFile
		(
		const char*	sSource,
		VImagePtr*	ppImage
		);

	virtual bool	ImageRelease
		(
		VImagePtr	pImage
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




#endif /* _H_CDrawWorkbench */
