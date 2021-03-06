/*---------------------------------------------------------------------+\
|
|	CDrawGTK.h  --  Implementation of draw object for MS-Windows
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:

		THIS FILE FOR LINUX ONLY

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	10-Jul-2013			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawGTK
#define _H_CDrawGTK
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#include "CGDIPen.h"
//#include "CGDIBrush.h"
//#include "CGDIFont.h"
#include "THash.h"

#include "UMachine.h"
#if defined( GL_GTK )		// brackets entire file
#include "VDraw.h"
#include "IDrawWin32.h"
#include "IDrawDebug.h"


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

typedef class CDrawGTK*			CDrawGTKPtr;
typedef class CDrawGTK&			CDrawGTKRef;
typedef const class CDrawGTK&	ConstCDrawGTKRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDrawGTK : public VXDraw,
				implements_ IDrawWin32,
				implements_ IDrawDebug
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawGTK );

public:
//	supported interfaces  -----------------------------------------------

	//	ISupports
	DECLARE_ISUPPORTS;

	//	IDrawWin32

	virtual
	void	SetHDC
			(
			HWND	wnd,
			HDC		hDC,
			LPRECT	pRect = NULL
			);


	virtual
	void	UpdateRect
			(
			LPRECT	pRect
			);

	//	IDrawDebug

	virtual
	void	SetDoubleBackingstore
			(
			bool	b
			);

	virtual
	void	SetDisplayDirtyRectangle
			(
			bool	b
			);


public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------



protected:
//	protected types  ----------------------------------------------------

	struct XOleImage : public XImage
	{
		XOleImage() : XImage(), nmW(0), nmH(0), pPicture( 0 ) {};

		long		nmW;
		long		nmH;
		LPPICTURE	pPicture;

	protected:
		virtual ~XOleImage() { if ( pPicture ) pPicture->Release(); };
	};

	typedef THashTable<CGDIPen::Parameters, CGDIPen>		PenList;
	typedef THashTable<CGDIBrush::Parameters, CGDIBrush>	BrushList;
	typedef THashTable<CGDIFont::Parameters, CGDIFont>		FontList;

//	protected functions  ------------------------------------------------

	bool		BufferCreate( void );
	bool		BufferDestroy( void );

	bool		PenSelect( void );
	bool		PenHaloSelect( void );
	void		PenDestroy( void );

	bool		BrushSelect( void );
	bool		BrushHaloSelect( void );
	void		BrushDestroy( void );

	bool		FontSelect( void );
	bool		FontHaloSelect( void );
	void		FontDestroy( void );

	void		ResetPenBrush( void );


//	protected data  -----------------------------------------------------

	EDrawContexts	m_eLastContext;
	bool		m_bDoubleBuffer;
	bool		m_bDisplayDirtyRectangle;
	CColor		m_clrDirtyRectangle;
	CColor		m_clrNone;
	CColor		m_clrBackBuffer;
	CColor		m_clrForeBuffer;
	CColor		m_clrBothBuffer;

	HDC			m_hdc;		// active DC
	HDC			m_hdcWindow;
	HDC			m_hdcApplication;
	HDC			m_hdcBackground;
	HDC			m_hdcForeground;
	HBITMAP		m_pBMApplication;
	HBITMAP		m_pBMBackground;
	HBITMAP		m_pBMForeground;
	HANDLE		m_pOldApplication;
	HANDLE		m_pOldBackground;
	HANDLE		m_pOldForeground;
	//int			m_nCX;		// width of buffer
	//int			m_nCY;		// height of buffer

	PenList		m_oPenList;
	CGDIPenPtr	m_pPen;
	BrushList	m_oBrushList;
	CGDIBrushPtr m_pBrush;
	FontList	m_oFontList;
	CGDIFontPtr	m_pFont;
	//HPEN		m_hPen;
	//HPEN		m_hPenHalo;
	//HBRUSH		m_hBrush;
	//HBRUSH		m_hBrushHalo;
	//HFONT		m_hFont;
	//HFONT		m_hFontHalo;
	TEXTMETRIC	m_tTextMetric;
	//HGDIOBJ		m_hPenOld;
	//HGDIOBJ		m_hBrushOld;
	//HGDIOBJ		m_hFontOld;
	RECT		m_tUpdateRect;
	HRGN		m_hClipRegion;


private:

	typedef	VXDraw	inherited;

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
	virtual bool	begin( void );
	virtual bool	end( void );


	//	IDraw
public:

	virtual bool	Size( long nWidth, long nHeight );
	virtual bool	BeginContext( EDrawContexts ctx );
	virtual bool	EndContext( void );
	virtual bool	SupportsContext( void );

	virtual bool	PushCropRectangle
					(
					long	nLeft,
					long	nTop,
					long	nRight,
					long	nBottom
					);
	virtual bool	PopCropRectangle( void );

	virtual bool	RefreshRectangle( void );

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


	virtual bool	LineWidth( short nWidth );
	virtual bool	LineColor( CColorRef rColor );
	virtual bool	FillColor( CColorRef rColor );
	virtual bool	HaloColor( CColorRef rColor );

	virtual bool	FontParams( const char* sFontName, GFLOAT fFontHeight );


	// --- Geometry graphics ---

	virtual bool	Line
					(
					GFLOAT	xStart,
					GFLOAT	yStart,
					GFLOAT	xEnd,
					GFLOAT	yEnd
					);


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

	virtual bool	Pie
					(
					GFLOAT	xAxis,
					GFLOAT	yAxis,
					GFLOAT	nRadius,
					GFLOAT	fStartAngle,
					GFLOAT	fEndAngle
					);


	virtual bool	EndPolyline
					(
					void
					);

	virtual bool	EndPolygon
					(
					void
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


#endif	// GL_GTK


#endif /* _H_CDrawGTK */
