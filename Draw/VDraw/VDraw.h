/*---------------------------------------------------------------------+\
|
|	VDraw.h  --  Base class for Draw objects
|
|	Purpose:
|
|	Restrictions/Warnings:

		The draw object assumes that the coordinate system is based upon
		the 0,0 coordinate being located in the upper-left corner of the
		screen/window and ascending Y is down the screen.

		Any other systems need to override the InitialMatrix function
		and provide a matrix that will provide the needed interface.  The
		default implementation simply returns the identity matrix.

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	25-Jun-2013			J.Griswold
		Change font-name members to be MAXPATH in length
	25-Mar-2010			J.Griswold		(Reviewed by: M.Rose) [1]
		Fixed compile time directive with OS_LINUX_VDDS
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix implementation of Size
	14-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix include to windows.h
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Support the concept of drawing context for foreground and background
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Support for generic font names 'sans-serif', 'serif' and 'monospace'
	19-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VDraw
#define _H_VDraw
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VPluginWithAggregate.h"
#include "IDraw.h"

#include "CColor.h"
#include "CMatrix3x3.h"
#include "TArray.h"
#include "CCharString.h"
#include "CVariantData.h"
#include "UFloat.h"

#include "UOSIncludes.h"

#include "UDeclSpec.h"


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

typedef class VXDraw*		VXDrawPtr;
typedef class VXDraw&		VXDrawRef;
typedef const class VXDraw&	ConstVDrawRef;

#if defined(OS_MSWIN)

#	define	VDRAWPOINT	POINT
#	define	VDRAWVALUE	LONG
#	define	VDRAWCAST_VALUE( x )	intFromFloat( x )

#else

#	define	VDRAWPOINT	VDraw::FPoint
#	define	VDRAWVALUE	float
#	define	VDRAWCAST_VALUE( x )	((VDRAWVALUE)(x))

#endif



/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class DECL_CLASS VXDraw : public VPluginWithAggregate,
				implements_ IDraw
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VXDraw );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IDraw


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
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					const char*	sSource,
					EFitments	eFitment = F_FILL,
					EAlignments	eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
					EVerticalAlignments	eVertAlign = V_MIDDLE
					);

	virtual bool	ImagePreloaded
					(
					GFLOAT		xPosition,
					GFLOAT		yPosition,
					GFLOAT		nWidth,
					GFLOAT		nHeight,
					VImagePtr	pImage,
					EFitments	eFitment = F_FILL,
					EAlignments	eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
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


public:
	//	public types  -------------------------------------------------------


protected:
//	protected types  ----------------------------------------------------

	typedef struct XImage : public IDraw::VImage
	{
		XImage() : nWidth( 0 ), nHeight( 0 ) {};
		virtual ~XImage(){};
		virtual void	Destroy() { delete this; };

		long	nWidth;
		long	nHeight;

	} XImage, *XImagePtr;


	typedef struct XCropRect
	{
		long	nLeft;
		long	nTop;
		long	nRight;
		long	nBottom;
	} XCropRect;

//	protected functions  ------------------------------------------------


	virtual CMatrix3x3
			InitialMatrix( void );

	void	TransformPoint
			(
			GFLOAT&	rfXOut,
			GFLOAT&	rfYOut,
			GFLOAT	fXIn,
			GFLOAT	fYIn
			);

	float	TransformLength
			(
			GFLOAT	fInLength
			);

	void	GenActiveMatrix( void );
	void	ResetWorld( void );

	GFLOAT	normalizeAngle( GFLOAT r );	// input is radians






	virtual void	MergeCropStack();

	virtual
	bool	PolypointNoTmx
			(
			GFLOAT	x,
			GFLOAT	y
			);

	bool	ArcStrokeAsPolyline
			(
			GFLOAT	xAxis,
			GFLOAT	yAxis,
			GFLOAT	nRadius,
			GFLOAT	fStartAngle,
			GFLOAT	fEndAngle
			);

	bool	CircleStrokeAsPolygon
			(
			GFLOAT	xAxis,
			GFLOAT	yAxis,
			GFLOAT	nRadius
			);

	bool	PieStrokeAsPolygon
			(
			GFLOAT	xAxis,
			GFLOAT	yAxis,
			GFLOAT	nRadius,
			GFLOAT	fStartAngle,
			GFLOAT	fEndAngle
			);

	int		SegmentsFromCircleRadius( GFLOAT r );

	bool	RectangleStrokeAsPolygon
			(
			GFLOAT		xPosition,
			GFLOAT		yPosition,
			GFLOAT		nWidth,
			GFLOAT		nHeight,
			CORNERSTYLE	eCornerStyle,	//= C_SQUARE,
			GFLOAT		nCornerSize		//= 0.0f
			);


//	protected data  -----------------------------------------------------

	IDrawTmx2Ptr	m_pTmx;

	long 			m_nWindowWidth;
	long			m_nWindowHeight;

	EDrawContexts	m_eDrawContext;

	Yogi::Core::TArray<XCropRect>	m_aCropStack;
	long				m_nCropStackTop;
	XCropRect			m_tCropCurrent;		// crop-stack merged into single rect

	long			m_nUpdateLeft;
	long			m_nUpdateTop;
	long			m_nUpdateRight;
	long			m_nUpdateBottom;

	EDayModes		m_eDayMode;

	short			m_nLineWidth;
	Yogi::Core::CColor	m_tLineColor;
	Yogi::Core::CColor	m_tFillColor;
	Yogi::Core::CColor	m_tHaloColor;
	Yogi::Core::CColor	m_tBackgroundColor;
	ENightColorModes m_eNightColor;

	char			m_sFontName[MAXPATH];
	GFLOAT			m_fFontHeight;

	// system font names to be used for special names
	char			m_sFontSansSerif[MAXPATH];	// 'sans-serif'
	char			m_sFontSerif[MAXPATH];		// 'serif'
	char			m_sFontMonospace[MAXPATH];	// 'monospace'

	Yogi::Core::TArray<VDRAWPOINT>	m_tPointList;

private:
//	private types  ------------------------------------------------------

	typedef VPluginWithAggregate	inherited;

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
			VPluginConfigurationPtr pConfig,
			VPluginLibraryPtr		pLib
			);


	//	VDrawTmx
public:

	virtual bool	begin( void );
	virtual bool	end( void );
	virtual bool	margin
					(
					int		nLeft,
					int		nTop,
					int		nRight,
					int		nBottom
					);

	// transformations
	virtual bool	push
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
	virtual bool	pop( void );



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

inline
void	VXDraw::TransformPoint
		(
		GFLOAT&	rfXOut,
		GFLOAT&	rfYOut,
		GFLOAT	fXIn,
		GFLOAT	fYIn
		)
{
	return m_pTmx->TransformPoint( rfXOut, rfYOut, fXIn, fYIn );
}

inline
GFLOAT	VXDraw::TransformLength
		(
		GFLOAT	fInLength
		)
{
	return m_pTmx->TransformLength( fInLength );
}

inline
void	VXDraw::GenActiveMatrix
		(
		void
		)
{
	m_pTmx->GenActiveMatrix();
}

inline
void	VXDraw::ResetWorld
		(
		void
		)
{
	m_pTmx->ResetWorld();
}

inline
GFLOAT	VXDraw::normalizeAngle
		(
		GFLOAT r
		)
{
	return m_pTmx->normalizeAngle( r );
}




}}


#endif /* _H_VDraw */
