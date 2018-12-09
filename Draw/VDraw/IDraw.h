/*---------------------------------------------------------------------+\
|
|	IDraw.h  --  brief description of what IDraw.h is for
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
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IDraw
#define _H_IDraw
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "IDrawTmx.h"

#include "CColor.h"
#include "CVariantData.h"


namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/

typedef interface_ IDraw*	IDrawPtr;

// lie and create some aliases to be compatible with legacy
typedef interface_ IDraw	VDraw;
typedef interface_ IDraw*	VDrawPtr;

extern const IXID	IXID_IDraw;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IDraw : public IDrawTmx
{
	typedef struct FPoint
	{
		GFLOAT	x;
		GFLOAT	y;
	} FPoint, *FPointPtr, &FPointRef;

	typedef enum EAlignments
	{
		A_LEFT = 0,
		A_CENTER,
		A_RIGHT
	} EAlignments;

	typedef enum EVerticalAlignments
	{
		V_BASELINE = 0,
		V_MIDDLE,
		V_TOP,
		V_ABSBOTTOM,
		V_CAPLINE
	} EVerticalAlignments;

	typedef enum EFitments
	{
		F_FILL = 0,			// fill image to rectangle
		F_SCALED,			// enlarge image to meet the edge, maintains aspect
		F_ZOOM,				// enlarges the smallest dimension to meet the edge, maintains aspect
		F_ORIGINAL			// maintains original size
	} EFitments;

	typedef enum ENightColorModes
	{
		C_NORMAL = 0,		// draw items using normal (defined) colors
		C_LUMINOUS,			// draw items using the luminous algorithm
		C_BRIGHT			// draw items in normal color when in dark/night mode
	} ENightColorModes;

	typedef enum EDayModes
	{
		D_NORMAL = 0,
		D_NIGHT,
		D_DARK
	} EDayModes;

	// used for rendering Rectangles
	typedef enum CORNERSTYLE
	{
		C_SQUARE = 0,
		C_BEVEL = 1,		//	chamfer
		C_ROUND = 2,		//	roundover
		C_COVE = 3,			//	indent round
		C_RABBET = 4		//	indent square
	} CORNERSTYLE;

	// text styles
	static const int	TS_NORMAL	= 0x0000;
	static const int	TS_BOLD		= 0x0001;
	static const int	TS_ITALIC	= 0x0002;
	static const int	TS_UNDERLINE= 0x0004;



	typedef enum EDrawContexts
	{
		CTX_UNDEFINED = 0,
		CTX_FOREGROUND,
		CTX_BACKGROUND,
		CTX_APPLICATION
	} EDrawContexts;


	typedef struct VImage
	{
		VImage() {};
		virtual void	Destroy() {};

	protected:
		virtual ~VImage() {};
	} VImage, *VImagePtr;




	// window/screen re/size
	virtual bool	Size( long nWidth, long nHeight ) PURE;

	virtual bool	BeginContext( EDrawContexts ctx ) PURE;
	virtual bool	EndContext( void ) PURE;
	virtual EDrawContexts
					CurrentContext( void ) PURE;

	// identify if this draw object has context support
	virtual bool	SupportsContext( void ) PURE;

	virtual bool	PushCropRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					) PURE;
	virtual bool	PopCropRectangle( void ) PURE;

	// call to attempt to refresh rectangle to screen
	virtual bool	RefreshRectangle
					(
					void
					) PURE;

	virtual bool	SetUpdateRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					) PURE;
	virtual bool	GetUpdateRectangle
					(
					long*	pLeft,
					long*	pTop,
					long*	pRight,
					long*	pBottom
					) PURE;


	virtual bool	DayMode( EDayModes eMode ) PURE;

	// --- Style properties ---

	virtual bool	LineWidth( short nWidth ) PURE;
	virtual bool	LineColor( Yogi::Core::ConstCColorRef rColor ) PURE;
	virtual bool	FillColor( Yogi::Core::ConstCColorRef rColor ) PURE;
	virtual bool	HaloColor( Yogi::Core::ConstCColorRef rColor ) PURE;

	virtual bool	BackgroundColor( Yogi::Core::ConstCColorRef rColor ) PURE;	// identify color to be used for background
	virtual bool	NightColor( ENightColorModes eMode ) PURE;

	virtual bool	FontParams
					(
					const char*	sFontName,
					GFLOAT		fFontHeight
					) PURE;


	// --- Geometry graphics ---

	virtual bool	Line
					(
					GFLOAT	xStart,
					GFLOAT	yStart,
					GFLOAT	xEnd,
					GFLOAT	yEnd
					) PURE;


	// implemented as a Polyline
	virtual bool	Arc
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius,
					GFLOAT	fStartAngle,
					GFLOAT	fEndAngle
					) PURE;

	virtual bool	Circle
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius
					) PURE;

	virtual bool	Ellipse
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nHeight,
					GFLOAT	nWidth
					) PURE;

	// implemented as a Polygon
	virtual bool	Pie
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius,
					GFLOAT	fStartAngle,
					GFLOAT	fEndAngle
					) PURE;

	virtual bool	Polygon
					(
					long		nNumPoints,
					FPointPtr	pPointList
					) PURE;

	virtual bool	Polyline
					(
					long		nNumPoints,
					FPointPtr	pPointList
					) PURE;

	virtual bool	BeginPolygon
					(
					void
					) PURE;

	virtual bool	EndPolygon
					(
					void
					) PURE;

	virtual bool	BeginPolyline
					(
					void
					) PURE;

	virtual bool	EndPolyline
					(
					void
					) PURE;

	virtual bool	Polypoint
					(
					GFLOAT	x,
					GFLOAT	y
					) PURE;

	virtual bool	Rectangle
					(
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					CORNERSTYLE	eStyle = C_SQUARE,
					GFLOAT		nCornerSize = 0.0f
					) PURE;

	virtual bool	TextString
					(
					GFLOAT			xPosition,
					GFLOAT			yPosition,
					EAlignments		eAlign,
					EVerticalAlignments	eVertAlign,
					const char*		sString,
					long			nCount = -1
					) PURE;

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
					) PURE;

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
					) PURE;

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
					) PURE;

	virtual bool	ImageLoadFile
					(
					const char*	sSource,
					VImagePtr*	ppImage
					) PURE;

	virtual bool	ImageRelease
					(
					VImagePtr	pImage
					) PURE;
};


/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/


}}


#endif /* _H_IDraw */
