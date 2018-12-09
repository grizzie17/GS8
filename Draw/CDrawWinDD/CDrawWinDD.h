/*---------------------------------------------------------------------+\
|
|	CDrawWinDD.h  --  Draw object implemented using Direct Draw
|
|	Purpose:
|
|	Restrictions/Warnings:

		THIS FILE FOR MS-WINDOWS ONLY

|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		react to new Size function that is declared in VDraw
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add debug mode that will display dirty-rectangle
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add support for switchable double-backing-store option
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement double-backing-store to support the concepts of
		background & foreground data model.
	09-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix the V_MIDDLE vertical-alignment setting
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Change names of the Select/Destroy Pen/Brush/Font functions
		to avoid a conflict with MS-Windows.
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawWinDD
#define _H_CDrawWinDD
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDraw.h"
#include "IDrawWin32.h"
#include "IDrawDebug.h"
#include "CGDIPen.h"
#include "CGDIBrush.h"
#include "CGDIFont.h"
#include "THash.h"

#include "UMachine.h"
#if defined( GL_DIRECTX )		// brackets entire file
#	include <ddraw.h>
#	include <ocidl.h>
#	include <olectl.h>


namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#ifdef CDRAWWINDD_EXPORTS
#	define	CDRAWWINDD_API	__declspec(dllexport)
#else
#	define	CDRAWWINDD_API	__declspec(dllimport)
#endif
#undef CDRAWWINDD_API
#define CDRAWWINDD_API


// this builds a 16 bit color value in 5.5.5 format (1-bit alpha mode)
#define _RGB16BIT555(r,g,b) ((b%32) + ((g%32) << 5) + ((r%32) << 10))

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b%32) + ((g%64) << 5) + ((r%32) << 11))

#if defined( OS_MSWIN_WCE )
#	if ! defined( DDPF_PALETTEINDEXED8 )
#		define DDPF_PALETTEINDEXED8	DDPF_PALETTEINDEXED
#	endif
#	if ! defined( DDPF_PALETTEINDEXEDTO8 )
#		define DDPF_PALETTEINDEXEDTO8	DDPF_PALETTEINDEXED
#	endif
#	if ! defined( DDLOCK_WAIT )
#		define	DDLOCK_WAIT	DDLOCK_WAITNOTBUSY
#	endif
#endif


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CDrawWinDD*		CDrawWinDDPtr;
typedef class CDrawWinDD&		CDrawWinDDRef;
typedef const class CDrawWinDD&	ConstCDrawWinDDRef;




/*
	encapsulates a DDPIXELFORMAT struct intialisation
	and the pxiel format of a DirectDraw surface
*/
struct CDDPIXELFORMAT : DDPIXELFORMAT
{
	DWORD	m_nBitformat;
	CDDPIXELFORMAT(IDirectDrawSurface* Surface)
		:m_nBitformat(0)
	{
		memset(this, 0,sizeof(DDPIXELFORMAT));
		this->dwSize = sizeof(DDPIXELFORMAT);
		if ( SUCCEEDED(Surface->GetPixelFormat(this)) )
		{
			m_nBitformat = this->dwRGBBitCount;
		}
	}

	bool IsValid() const
	{
		return m_nBitformat != 0;
	}

	/*
		whats the format of the pixels on a
		8/16/24/32 bit surface
	*/
	DWORD GetBitCount() const
	{
		return m_nBitformat;
	}
	/*
		are we in 16/24/32 bit mode
	*/
	bool InRGBMode() const
	{
		return ( (this->dwFlags & DDPF_RGB) && !(this->dwFlags & DDPF_PALETTEINDEXED8)  ) ? true: false;
	}
	/*
		are we in 8 bit mode and therefore using a palette
	*/
	bool InPaletteMode() const
	{
		return ((this->dwFlags & DDPF_PALETTEINDEXED8) || (this->dwFlags & DDPF_PALETTEINDEXEDTO8)) ? true: false;
	}
};


struct ColorConverter
{
	virtual ~ColorConverter() {};

	virtual DWORD	Convert( int r, int g, int b ) = 0;
};


struct CRGB8BIT : ColorConverter
{
	DWORD lastasked_,lastgot_;
	IDirectDrawSurface* srfc_;

	CRGB8BIT(IDirectDrawSurface* srfc)
		:srfc_(srfc), lastasked_(~0U), lastgot_(0)
	{	}

	virtual ~CRGB8BIT()
	{
		if ( srfc_ )
			srfc_->Release();
	}

	DWORD Convert(int r, int g, int b)
	{
		COLORREF dwGDIColor = RGB(r,g,b);
		if(lastasked_==dwGDIColor)
			return lastgot_;

		lastasked_ = dwGDIColor;
		COLORREF       rgbT = 0;
		//  Use GDI SetPixel to color match for us
		HDC hdc;
		if( dwGDIColor != CLR_INVALID && srfc_->GetDC(&hdc) == DD_OK)
		{
			rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
			SetPixel(hdc, 0, 0, dwGDIColor);       // Set our value
			srfc_->ReleaseDC(hdc);
		}

		// Now lock the surface so we can read back the converted color
		DWORD dw = CLR_INVALID;
		DDSURFACEDESC  ddsd;
		ddsd.dwSize = sizeof(ddsd);
		HRESULT hr = srfc_->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
		if(SUCCEEDED(hr))
		{
			dw = *(DWORD *) ddsd.lpSurface;
//			if( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 ) // Mask it to bpp
				dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount) - 1;
			srfc_->Unlock(NULL);
		}

		//  Now put the color that was there back.
		if(dwGDIColor != CLR_INVALID && srfc_->GetDC(&hdc) == DD_OK)
		{
			SetPixel( hdc, 0, 0, rgbT );
			srfc_->ReleaseDC(hdc);
		}

		lastgot_ = dw;
		return dw;
	}

};

struct CRGB24BIT : ColorConverter
{
	DWORD Convert(int r, int g, int b)
	{
		return
			(
				(b << 16)
			|	(g << 8)
			|	(r)
			);
		//return ((b) + ((g) << 8) + ((r) << 16));
	}
};

struct CRGB32BIT : ColorConverter
{
	DWORD Convert(int r, int g, int b)
	{
		int a = 0;
		return
				(
					(a << 24)
				|	(b << 16)
				|	(g << 8)
				|	(r)
				);
		//return ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24));
	}
};

struct CRGBTo16BIT565 : ColorConverter
{
	DWORD Convert(int r, int g, int b)
	{
		const int scale5 = 256/32;
		const int scale6 = 256/64;
		return _RGB16BIT565( r / scale5, g / scale6, b / scale5 );
	}
};

struct CRGBTo16BIT555 : ColorConverter
{
	DWORD Convert(int r, int g, int b)
	{
		const int scale5 = 256/32;
		return _RGB16BIT565( r / scale5, g / scale5, b / scale5 );
	}
};




/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class CDRAWWINDD_API CDrawWinDD : public VXDraw,
							implements_ IDrawWin32,
							implements_ IDrawDebug
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawWinDD );

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



	bool		DirectDrawInit
				(
				void
				);



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

	COLORREF	MakeColorRef( const CColor& c );

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

	bool		MoveTo( long nX, long nY );
	bool		LineTo( long nX, long nY );


	static
	LPDIRECTDRAW
				GetDirectDraw();
	static
	void		ReleaseDirectDraw( LPDIRECTDRAW poDD );



//	protected data  -----------------------------------------------------

	static LPDIRECTDRAW	g_poDD;
	static long			g_nRefDD;		// reference count to g_poDD

	HWND		m_hwnd;


	IDirectDrawSurface*	m_pSurfApplication;
	IDirectDrawSurface*	m_pSurfBackground;
	IDirectDrawSurface*	m_pSurfForeground;
	IDirectDrawSurface*	m_pSurfWindow;

	IDirectDrawSurface*	m_pSurfCurrent;		// the surface that is active

	LPDIRECTDRAWCLIPPER	m_pClipper;
	ColorConverter*		m_pColorConverter;


	EDrawContexts	m_eLastContext;
	bool		m_bDoubleBuffer;
	bool		m_bDisplayDirtyRectangle;
	CColor		m_clrDirtyRectangle;
	CColor		m_clrNone;
	CColor		m_clrBackBuffer;
	CColor		m_clrForeBuffer;
	CColor		m_clrBothBuffer;

	HDC			m_hdc;		// active DC

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
//	private types  ------------------------------------------------------

	typedef VXDraw	inherited;

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

	//	VDrawTmx
public:
	virtual bool	begin( void );
	virtual bool	end( void );

	//	VDraw
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


#endif	// GL_DIRECTX


#endif /* _H_CDrawWinDD */
