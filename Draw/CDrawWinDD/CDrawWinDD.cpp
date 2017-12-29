/*---------------------------------------------------------------------+\
|
|	CDrawWinDD.cpp  --  Draw object implemented using Direct Draw
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	11-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fixed a bug so a line width zero is not drawn
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		react to new Size function that is declared in VDraw
	18-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add debug mode that will display dirty-rectangle
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		React to change to the CColor class.
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "Stdafx.h"

#include "CDrawWinDD.h"
#include "VPluginFactory.h"

#if defined(GL_DIRECTX)		// brackets entire file


#include <wingdi.h>
#include <math.h>
#include <float.h>

#include <ocidl.h>
#include <olectl.h>

#include <atlbase.h>
#include <atlwin.h>

#include <ddraw.h>

#include "TPointer.h"

NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/


#if defined( OS_MSWIN_WCE )
#	if ! defined( DDSCAPS_OFFSCREENPLAIN )
#		define	DDSCAPS_OFFSCREENPLAIN	DDSCAPS_OVERLAY
#	endif
#	if ! defined( DDBLT_WAIT )
#		define	DDBLT_WAIT	DDBLT_WAITNOTBUSY
#	endif
#endif

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
LPDIRECTDRAW	CDrawWinDD::g_poDD = NULL;
long			CDrawWinDD::g_nRefDD = 0;
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

PLUGIN_CREATE_FACTORY( CDrawWinDD );

/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDrawWinDD - constructor

\+---------------------------------------------------------------------*/
CDrawWinDD::CDrawWinDD
		(
		void
		)
		: inherited(),
		m_hwnd( 0 ),
		m_pSurfApplication( 0 ),
		m_pSurfBackground( 0 ),
		m_pSurfForeground( 0 ),
		m_pSurfWindow( 0 ),
		m_pSurfCurrent( 0 ),
		m_pClipper( 0 ),
		m_eLastContext( CTX_UNDEFINED ),
		m_bDoubleBuffer( true ),
		m_bDisplayDirtyRectangle( false ),
		m_hdc( 0 ),
		m_oPenList(),
		m_pPen( 0 ),
		m_oBrushList(),
		m_pBrush( 0 ),
		m_oFontList(),
		m_pFont( 0 ),
		//m_hPen( 0 ),
		//m_hPenHalo( 0 ),
		//m_hBrush( 0 ),
		//m_hBrushHalo( 0 ),
		//m_hPenOld( 0 ),
		//m_hBrushOld( 0 ),
		m_tUpdateRect()
{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );

	m_clrNone = CColor::ColorFromName( "background" );
	m_clrBackBuffer = CColor::ColorFromName( "magenta" );
	m_clrForeBuffer = CColor::ColorFromName( "deepskyblue" );
	m_clrBothBuffer = CColor::ColorFromName( "limegreen" );

}

CDrawWinDD::CDrawWinDD
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_hwnd( 0 ),
		m_pSurfApplication( 0 ),
		m_pSurfBackground( 0 ),
		m_pSurfForeground( 0 ),
		m_pSurfWindow( 0 ),
		m_pSurfCurrent( 0 ),
		m_pClipper( 0 ),
		m_eLastContext( CTX_UNDEFINED ),
		m_bDoubleBuffer( true ),
		m_bDisplayDirtyRectangle( false ),
		m_hdc( 0 ),
		m_oPenList(),
		m_pPen( 0 ),
		m_oBrushList(),
		m_pBrush( 0 ),
		m_oFontList(),
		m_pFont( 0 ),
		//m_hPen( 0 ),
		//m_hPenHalo( 0 ),
		//m_hBrush( 0 ),
		//m_hBrushHalo( 0 ),
		//m_hPenOld( 0 ),
		//m_hBrushOld( 0 ),
		m_tUpdateRect()
{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );

	m_clrNone = CColor::ColorFromName( "background" );
	m_clrBackBuffer = CColor::ColorFromName( "magenta" );
	m_clrForeBuffer = CColor::ColorFromName( "deepskyblue" );
	m_clrBothBuffer = CColor::ColorFromName( "limegreen" );

}

CDrawWinDD::CDrawWinDD
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_hwnd( 0 ),
		m_pSurfApplication( 0 ),
		m_pSurfBackground( 0 ),
		m_pSurfForeground( 0 ),
		m_pSurfWindow( 0 ),
		m_pSurfCurrent( 0 ),
		m_pClipper( 0 ),
		m_eLastContext( CTX_UNDEFINED ),
		m_bDoubleBuffer( true ),
		m_bDisplayDirtyRectangle( false ),
		m_hdc( 0 ),
		m_oPenList(),
		m_pPen( 0 ),
		m_oBrushList(),
		m_pBrush( 0 ),
		m_oFontList(),
		m_pFont( 0 ),
		//m_hPen( 0 ),
		//m_hPenHalo( 0 ),
		//m_hBrush( 0 ),
		//m_hBrushHalo( 0 ),
		//m_hPenOld( 0 ),
		//m_hBrushOld( 0 ),
		m_tUpdateRect()
{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );

	m_clrNone = CColor::ColorFromName( "background" );
	m_clrBackBuffer = CColor::ColorFromName( "magenta" );
	m_clrForeBuffer = CColor::ColorFromName( "deepskyblue" );
	m_clrBothBuffer = CColor::ColorFromName( "limegreen" );

}


/*---------------------------------------------------------------------+\

 * ~CDrawWinDD - destructor

\+---------------------------------------------------------------------*/
CDrawWinDD::~CDrawWinDD
		(
		void
		)
{
	ResetPenBrush();

	BufferDestroy();

	ReleaseDirectDraw( 0 );

	if ( m_pColorConverter )
		delete m_pColorConverter;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * DirectDrawInit -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::DirectDrawInit
		(
		)
{
	bool	bResult = false;


	// create main DirectDraw object

	if ( m_hwnd )
	{
		HRESULT	hr;
		LPDIRECTDRAW	poDD = GetDirectDraw();

		if ( poDD )
		{
			hr = poDD->SetCooperativeLevel( m_hwnd, DDSCL_NORMAL );
			if ( DD_OK != hr )
			{
				ReleaseDirectDraw( poDD );
			}
			else
			{
				bResult = true;
			}
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * SetHDC -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::SetHDC
		(
		HWND	hWindow,
		HDC		,//hDC,
		LPRECT	pRect
		)
{
	m_hwnd = hWindow;

	int	cx = 0;
	int	cy = 0;
	if ( pRect )
	{
		cx = pRect->right - pRect->left;
		cy = pRect->bottom - pRect->top;
	}
	if ( 0 == cx )
		cx = 400;
	if ( 0 == cy )
		cy = 300;

	if ( m_nWindowWidth < cx  ||  m_nWindowHeight < cy )
	{
		Size( cx, cy );
	}
}


/*---------------------------------------------------------------------+\

 * UpdateRect -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::UpdateRect
		(
		LPRECT	pRect
		)
{
	m_tUpdateRect = *pRect;
}




/*---------------------------------------------------------------------+\

 * SetDoubleBackingstore -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::SetDoubleBackingstore
		(
		bool	b
		)
{
	m_bDoubleBuffer = b;
}

/*---------------------------------------------------------------------+\

 * SetDisplayDirtyRectangle -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::SetDisplayDirtyRectangle
		(
		bool	b
		)
{
	m_bDisplayDirtyRectangle = b;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * GetDirectDraw -

\+---------------------------------------------------------------------*/
//static
LPDIRECTDRAW
		CDrawWinDD::GetDirectDraw
		(
		void
		)
{
	LPDIRECTDRAW	poDD = NULL;

	if ( ! g_poDD )
	{
		HRESULT	hr;

		hr = ::DirectDrawCreate( NULL, &poDD, NULL );
		if ( DD_OK == hr )
		{
			g_poDD = poDD;
			g_nRefDD = 1;
		}
	}
	else
	{
		++g_nRefDD;
		poDD = g_poDD;
	}
	return poDD;
}


/*---------------------------------------------------------------------+\

 * ReleaseDirectDraw -

\+---------------------------------------------------------------------*/
//static
void	CDrawWinDD::ReleaseDirectDraw
		(
		LPDIRECTDRAW	//poDD
		)
{
	if ( 0 < g_nRefDD )
	{
		--g_nRefDD;
		if ( g_nRefDD < 1 )
		{
			g_poDD->Release();
			g_poDD = 0;
		}
	}
}


/*---------------------------------------------------------------------+\

 * BufferCreate -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::BufferCreate
		(
		void
		)
{
	bool	bResult = false;
	if ( m_hwnd )
	{
		DirectDrawInit();

		HRESULT			hr;
		DDSURFACEDESC	ddsd;

		// create primary surface
		ZeroMemory( &ddsd, sizeof(ddsd) );
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		hr = g_poDD->CreateSurface( &ddsd, &m_pSurfWindow, NULL );

		// create a clipper and attach to the primary surface
		hr = g_poDD->CreateClipper( 0, &m_pClipper, NULL );
		hr = m_pClipper->SetHWnd( 0, m_hwnd );
		hr = m_pSurfWindow->SetClipper( m_pClipper );



		ZeroMemory( &ddsd, sizeof(ddsd) );
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		ddsd.dwWidth = m_nWindowWidth;
		ddsd.dwHeight = m_nWindowHeight;
		hr = g_poDD->CreateSurface( &ddsd, &m_pSurfApplication, NULL );

		m_pSurfApplication->GetDC( &m_hdc );

#if 1
		FillColor( m_tBackgroundColor );
		if ( BrushSelect() )
		{
			RECT	rct;
			rct.left = 0;
			rct.top = 0;
			rct.right = m_nWindowWidth;
			rct.bottom = m_nWindowHeight;

			::FillRect( m_hdc, &rct, m_pBrush->ToHBRUSH() );
			BrushDestroy();
		}
#else

		LOGBRUSH	brush;

		brush.lbStyle = BS_SOLID;
		brush.lbColor = m_tBackgroundColor;
		brush.lbHatch = static_cast<ULONG_PTR>(~0);

		HBRUSH	hBB = ::CreateBrushIndirect( &brush );
		if ( hBB )
		{
			HGDIOBJ	hOld = ::SelectObject( m_hdc, hBB );

			RECT	rct;
			rct.left = 0;
			rct.top = 0;
			rct.right = m_nWindowWidth;
			rct.bottom = m_nWindowHeight;


			::FillRect( m_hdc, &rct, hBB );

			::SelectObject( m_hdc, hOld );
			::DeleteObject( hBB );
		}
#endif

		m_pSurfApplication->ReleaseDC( m_hdc );


		ZeroMemory( &ddsd, sizeof(ddsd) );
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		ddsd.dwWidth = m_nWindowWidth;
		ddsd.dwHeight = m_nWindowHeight;
		hr = g_poDD->CreateSurface( &ddsd, &m_pSurfBackground, NULL );

		ZeroMemory( &ddsd, sizeof(ddsd) );
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		ddsd.dwWidth = m_nWindowWidth;
		ddsd.dwHeight = m_nWindowHeight;
		hr = g_poDD->CreateSurface( &ddsd, &m_pSurfForeground, NULL );


		// work out the pixel format for color conversions
		CDDPIXELFORMAT pf(m_pSurfWindow);
		if ( pf.IsValid() )
		{
			if(pf.InRGBMode())
			{
				DWORD tst = pf.GetBitCount();
				if ( 15 == tst ) // 16 bit 555
				{
					m_pColorConverter = new CRGBTo16BIT555;
				}
				else if(16 == tst) // 16 bit 565
				{
					m_pColorConverter = new CRGBTo16BIT565;
				}
				else if(24 == tst) // 24 bit
				{
					m_pColorConverter = new CRGB24BIT;
				}
				else if(32 == tst) // 32 bit
				{
					m_pColorConverter = new CRGB32BIT;
				}
			}
			else if ( pf.InPaletteMode() )
			{
				m_pColorConverter = new CRGB8BIT(m_pSurfWindow);
			}
			else
			{
				// oops
			}
		}

	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * BufferDestroy -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::BufferDestroy
		(
		void
		)
{
	if ( m_pSurfWindow )
	{
		m_pSurfWindow->Release();
		m_pSurfWindow = 0;
	}

	if ( m_pSurfForeground )
	{
		m_pSurfForeground->Release();
		m_pSurfForeground = 0;
	}

	if ( m_pSurfBackground )
	{
		m_pSurfBackground->Release();
		m_pSurfBackground = 0;
	}

	if ( m_pSurfApplication )
	{
		m_pSurfApplication->Release();
		m_pSurfApplication = 0;
	}

	if ( m_pClipper )
	{
		m_pClipper->Release();
		m_pClipper = 0;
	}

	m_pSurfCurrent = 0;

	return true;
}


/*---------------------------------------------------------------------+\

 * PenSelect -

\+---------------------------------------------------------------------*/
const unsigned int	kBitsColor	= 3;
const unsigned int	kBitsAll	= 0xFF;
const unsigned int	kColorsAll	= kBitsAll + 1;
const unsigned char a216[] = { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };
const unsigned char a3bits[] = { 0x00, 0x33, 0x55, 0x77, 0x99, 0xBB, 0xDD, 0xFF };
const unsigned char a2bits[] = { 0x00, 0x66, 0x99, 0xFF };
const unsigned int	kColorRamp = kBitsAll / sizeof(a216);
const unsigned int	kColorRamp2 = kColorRamp / 4;
const unsigned int	kColorDiv = kColorsAll / kColorRamp;
inline unsigned int VDDSINDEX( unsigned int x )
{
	if ( kBitsAll == x )
	{
		return sizeof(a216) - 1;
	}
	else
	{
		unsigned int y = (x + kColorRamp2) / kColorRamp;
		if ( sizeof(a216) <= y )
			y = sizeof(a216) - 1;
		return y;
	}
}

inline unsigned int VDDSINDEX2( unsigned int x )
{
	if ( kBitsAll == x )
	{
		return sizeof(a2bits) - 1;
	}
	else
	{
		unsigned int y = x * sizeof(a2bits) / kBitsAll;
		//int y = (x + kColorRamp2) / kColorRamp;
		if ( sizeof(a2bits) <= y )
			y = sizeof(a2bits) - 1;
		return y;
	}
}

inline unsigned int VDDSINDEX3( unsigned int x )
{
	if ( kBitsAll == x )
	{
		return sizeof(a3bits) - 1;
	}
	else
	{
		unsigned int y = x * sizeof(a3bits) / kBitsAll;
		//int y = (x + kColorRamp2) / kColorRamp;
		if ( sizeof(a3bits) <= y )
			y = sizeof(a3bits) - 1;
		return y;
	}
}


inline unsigned int	VDDSEMULATE( unsigned int x )
{
	return a216[ VDDSINDEX( x ) ];
}

inline unsigned int	VDDSEMULATE2( unsigned int x )
{
	return a2bits[ VDDSINDEX2( x ) ];
}

inline unsigned int	VDDSEMULATE3( unsigned int x )
{
	return a3bits[ VDDSINDEX3( x ) ];
}

inline unsigned int	VDDSVALUE( unsigned int x )
{
	return VDDSEMULATE( x );
	//return VDDSINDEX( x ) << 5;
}


inline
COLORREF
		CDrawWinDD::MakeColorRef
		(
		const CColor&	rColor
		)
{
	COLORREF	c = 0;

	unsigned int	r = rColor.GetRed();
	unsigned int	g = rColor.GetGreen();
	unsigned int	b = rColor.GetBlue();

#if 1
	if ( m_pColorConverter )
		c = m_pColorConverter->Convert( r, g, b );
	else
		c = RGB( r, g, b );
#else


	if ( 2 == r  &&  2 == g  &&  2 == b )
	{
		c = RGB( r, g, b );
	}
	else
	{
#	if 0
		unsigned int	rv = VDDSEMULATE2( r );
		unsigned int	gv = VDDSEMULATE2( g );
		unsigned int	bv = VDDSEMULATE2( b );

		if ( 0 == rv  &&  0 == gv  &&  0 == bv )
		{
			if ( 0 < r  ||  0 < g  ||  0 < b )
				rv = gv = bv = 2;
		}
		c = RGB( rv, gv, bv );

#	else
		c = RGB( r, g, b );

#	endif
	}
#endif

	return c;
}



/*---------------------------------------------------------------------+\

 * PenSelect -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::PenSelect
		(
		void
		)
{
#if 1
	if ( ! m_pPen )
	{
		CGDIPen::Parameters	parm;

		if ( CColor::BackgroundColor() == m_tLineColor )
			parm.oColor = m_tBackgroundColor;
		else
			parm.oColor = m_tLineColor;
		parm.nWidth = m_nLineWidth;

		CGDIPenPtr	pPen = m_oPenList.Find( parm );
		if ( ! pPen )
		{
			CGDIPen	oPen( parm.oColor, parm.nWidth );
			m_oPenList.Add( parm, oPen );
			pPen = m_oPenList.Find( parm );
		}
		if ( pPen )
		{
			m_pPen = pPen;
			m_pPen->Select( m_hdc );
		}
	}
#else
	if ( ! m_hPen )
	{
		LOGPEN	params;

		if ( m_tLineColor.IsNonColor()  ||  m_nLineWidth < 1 )
		{
			//params.lopnStyle = PS_NULL;
			m_hPen = (HPEN)::GetStockObject( NULL_PEN );
		}
		else
		{
			params.lopnStyle = PS_SOLID;
			if ( CColor::BackgroundColor() == m_tLineColor )
				params.lopnColor = MakeColorRef(m_tBackgroundColor);
			else
				params.lopnColor = MakeColorRef(m_tLineColor);
			params.lopnWidth.x = m_nLineWidth;
			params.lopnWidth.y = m_nLineWidth;
			m_hPen = ::CreatePenIndirect( &params );
		}
		if ( ! m_hPen )
			return false;
	}

	m_hPenOld = ::SelectObject( m_hdc, m_hPen );
#endif
	return true;
}


/*---------------------------------------------------------------------+\

 * PenHaloSelect -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::PenHaloSelect
		(
		void
		)
{
#if 1
	if ( m_tHaloColor.IsNonColor() )
		return false;

	if ( m_nLineWidth < 1 )
		return false;

	if ( m_pPen )
	{
		m_pPen->Deselect();
		m_pPen = 0;
	}

	CGDIPen::Parameters	parm;

	if ( CColor::BackgroundColor() == m_tHaloColor )
		parm.oColor = m_tBackgroundColor;
	else
		parm.oColor = m_tHaloColor;
	parm.nWidth = m_nLineWidth;

	CGDIPenPtr	pPen = m_oPenList.Find( parm );
	if ( ! pPen )
	{
		CGDIPen	oPen( parm.oColor, parm.nWidth );
		m_oPenList.Add( parm, oPen );
		pPen = m_oPenList.Find( parm );
	}
	if ( pPen )
	{
		m_pPen = pPen;
		m_pPen->Select( m_hdc );
	}
#else
	if ( m_tHaloColor.IsNonColor() )
		return false;

	if ( m_nLineWidth < 1 )
		return false;

	if ( ! m_hPenHalo )
	{
		LOGPEN	params;

		if ( m_tHaloColor.IsNonColor()  ||  m_nLineWidth < 1 )
			params.lopnStyle = PS_NULL;
		else
			params.lopnStyle = PS_SOLID;
		if ( CColor::BackgroundColor() == m_tHaloColor )
			params.lopnColor = MakeColorRef(m_tBackgroundColor);
		else
			params.lopnColor = MakeColorRef(m_tHaloColor);
		params.lopnWidth.x = m_nLineWidth + 2;
		params.lopnWidth.y = m_nLineWidth + 2;
		m_hPenHalo = ::CreatePenIndirect( &params );
		//m_hPen = ::CreatePen( 0, m_nLineWidth, m_tLineColor );
		if ( ! m_hPenHalo )
			return false;
	}

	m_hPenOld = ::SelectObject( m_hdc, m_hPenHalo );
#endif
	return true;
}


/*---------------------------------------------------------------------+\

 * BrushSelect -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::BrushSelect
		(
		void
		)
{
#if 1
	if ( ! m_pBrush )
	{
		CGDIBrush::Parameters	parm;

		if ( CColor::BackgroundColor() == m_tFillColor )
			parm.oColor = m_tBackgroundColor;
		else
			parm.oColor = m_tFillColor;

		CGDIBrushPtr	pBrush = m_oBrushList.Find( parm );
		if ( ! pBrush )
		{
			CGDIBrush	oBrush( parm.oColor );
			m_oBrushList.Add( parm, oBrush );
			pBrush = m_oBrushList.Find( parm );
		}
		if ( pBrush )
		{
			m_pBrush = pBrush;
			m_pBrush->Select( m_hdc );
		}
	}
#else
	if ( ! m_hBrush )
	{
		LOGBRUSH	brush;

		if ( m_tFillColor.IsNonColor() )
		{
			//brush.lbStyle = BS_NULL;
			m_hBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
		else
		{
			brush.lbStyle = BS_SOLID;
			if ( CColor::BackgroundColor() == m_tFillColor )
				brush.lbColor = MakeColorRef(m_tBackgroundColor);
			else
				brush.lbColor = MakeColorRef(m_tFillColor);
			brush.lbHatch = static_cast<ULONG_PTR>(~0);
			m_hBrush = ::CreateBrushIndirect( &brush );
		}

		if ( ! m_hBrush )
			return false;
	}

	m_hBrushOld = ::SelectObject( m_hdc, m_hBrush );
#endif
	return true;
}


/*---------------------------------------------------------------------+\

 * FontSelect -

\+---------------------------------------------------------------------*/
//BEGIN_OVERRUN_WARNING
bool	CDrawWinDD::FontSelect
		(
		void
		)
{
#if 1
	if ( ! m_pFont )
	{
		CGDIFont::Parameters	parm;

		strcpy_s( parm.sName, sizeof(parm.sName), m_sFontName );
		parm.nHeight = long(TransformLength( m_fFontHeight ));

		CGDIFontPtr	pFont = m_oFontList.Find( parm );
		if ( ! pFont )
		{
			CGDIFont	oFont( parm.sName, parm.nHeight );
			m_oFontList.Add( parm, oFont );
			pFont = m_oFontList.Find( parm );
		}
		if ( pFont )
		{
			m_pFont = pFont;
			if ( m_pFont->Select( m_hdc ) )
				::GetTextMetrics( m_hdc, &m_tTextMetric );
		}
	}
#else
	if ( ! m_hFont )
	{
#if defined( OS_MSWIN_WCE )
		LOGFONT		f = {0};

		f.lfHeight = LONG(TransformLength( m_fFontHeight ));
		TArrayPointer<WCHAR> wsFont = ::WideStringFromString( m_sFontName );
		::wcscpy_s( f.lfFaceName, sizeof(f.lfFaceName), wsFont );

		m_hFont = CreateFontIndirectW( &f );
#else
		LOGFONTA	f;
		::memset( &f, 0, sizeof(f) );

		f.lfHeight = LONG(TransformLength( m_fFontHeight ));
		::strcpy_s( f.lfFaceName, sizeof(f.lfFaceName), m_sFontName );

		m_hFont = ::CreateFontIndirectA( &f );
#endif
		if ( ! m_hFont )
			return false;
	}

	if ( m_hFont )
	{
		m_hFontOld = ::SelectObject( m_hdc, m_hFont );
		if ( m_hFontOld )
			::GetTextMetrics( m_hdc, &m_tTextMetric );
	}
#endif
	return true;
}
//END_OVERRUN_WARNING

/*---------------------------------------------------------------------+\

 * PenDestroy -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::PenDestroy
		(
		void
		)
{
#if 1
	if ( m_pPen )
	{
		m_pPen->Deselect();
		m_pPen = 0;
	}
#else
	if ( m_hPen )
	{
		if ( m_hPenOld )
		{
			::SelectObject( m_hdc, m_hPenOld );
			m_hPenOld = NULL;
		}
		::DeleteObject( m_hPen );
		m_hPen = NULL;
	}

	if ( m_hPenHalo )
	{
		::DeleteObject( m_hPenHalo );
		m_hPenHalo = NULL;
	}
#endif
}

/*---------------------------------------------------------------------+\

 * BrushDestroy -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::BrushDestroy
		(
		void
		)
{
#if 1
	if ( m_pBrush )
	{
		m_pBrush->Deselect();
		m_pBrush = 0;
	}
#else
	if ( m_hBrush )
	{
		if ( m_hBrushOld )
		{
			::SelectObject( m_hdc, m_hBrushOld );
			m_hBrushOld = NULL;
		}
		::DeleteObject( m_hBrush );
		m_hBrush = NULL;
	}

	if ( m_hBrushHalo )
	{
		::DeleteObject( m_hBrushHalo );
		m_hBrushHalo = NULL;
	}
#endif
}


/*---------------------------------------------------------------------+\

 * FontDestroy -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::FontDestroy
		(
		void
		)
{
#if 1
	if ( m_pFont )
	{
		m_pFont->Deselect();
		m_pFont = 0;
	}
#else
	if ( m_hFont )
	{
		if ( m_hFontOld )
		{
			::SelectObject( m_hdc, m_hFontOld );
			m_hFontOld = NULL;
		}
		::DeleteObject( m_hFont );
		m_hFont = NULL;
	}
#endif

	//if ( m_hFontHalo )
	//{
	//	::DeleteObject( m_hFontHalo );
	//	m_hFontHalo = NULL;
	//}
}


/*---------------------------------------------------------------------+\

 * ResetPenBrush -

\+---------------------------------------------------------------------*/
void	CDrawWinDD::ResetPenBrush
		(
		void
		)
{
	BrushDestroy();
	PenDestroy();
	FontDestroy();
}





/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CDrawWinDD::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDrawWin32 )
			pI = INTERFACE_THIS( IDrawWin32Ptr );
		else if ( rIID == IXID_IDrawDebug )
			pI = INTERFACE_THIS( IDrawDebugPtr );
		else
			pI = 0;
	}

	return pI;
}

/*---------------------------------------------------------------------+\

 * Load - fetch configuration parameters

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = inherited::Load( pConfig, pLib );
	if ( bResult )
	{
		bool	bDoubleBackingstore = true;
		bool	bDisplayDR = false;

		bDisplayDR = pConfig->GetParameterAsBool( "Display Dirty Rectangle", false );
		bDoubleBackingstore
				= pConfig->GetParameterAsBool( "Double Backingstore", true );
		SetDoubleBackingstore( bDoubleBackingstore );
		SetDisplayDirtyRectangle( bDisplayDR );

		CVariantDataPtr	pv;

		pv = pConfig->GetParameter( "Background Color" );
		if ( pv )
		{
			CColor	clrBackground = *pv;
			BackgroundColor( clrBackground );
		}
	}
	return bResult;
}




/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::begin
		(
		void
		)
{
	bool	bResult = inherited::begin();

	m_eLastContext = CTX_UNDEFINED;

	if ( bResult )
	{
		if ( ! m_pSurfWindow )
		{
			BufferCreate();
		}
		else
		{
			if ( m_pSurfApplication->IsLost()
				||	m_pSurfBackground->IsLost()
				||	m_pSurfForeground->IsLost()
				||	m_pSurfWindow->IsLost()
				 )
			{
				BufferDestroy();
				BufferCreate();
			}
		}

		if ( ! m_bDoubleBuffer )
		{
			bResult = BeginContext( IDraw::CTX_BACKGROUND );
		}
		else if ( m_bDisplayDirtyRectangle )
		{
			m_clrDirtyRectangle = m_clrNone;
		}
	}

	return bResult;

}

/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::end
		(
		void
		)
{

	if ( ! m_bDoubleBuffer )
		EndContext();

	ResetPenBrush();

	if ( m_bDoubleBuffer )
		m_pSurfCurrent = m_pSurfForeground;
	else
		m_pSurfCurrent = m_pSurfBackground;

	if ( ! m_pSurfCurrent )
		m_pSurfCurrent = m_pSurfForeground;
	if ( m_pSurfCurrent )
	{

		RECT	rctSrc;
		rctSrc.left = umin( m_nUpdateLeft, m_tUpdateRect.left );
		rctSrc.top = umin( m_nUpdateTop, m_tUpdateRect.top );
		rctSrc.right = umax( m_nUpdateRight, m_tUpdateRect.right );
		rctSrc.bottom = umax( m_nUpdateBottom, m_tUpdateRect.bottom );

		RECT	rctClient = rctSrc;

		::ClientToScreen(m_hwnd, (LPPOINT)&rctClient);
		::ClientToScreen(m_hwnd, (LPPOINT)(&rctClient)+1);

		SelectClipRgn( m_hdc, NULL );

		m_pSurfWindow->Blt(
							&rctClient,		// destination
							m_pSurfCurrent,	// source surface
							&rctSrc,		// source rectangle, NULL = entire surface
							DDBLT_WAIT, NULL );
		//DbgPrint( "surface blt hr = %lx\n", hr );
		m_pSurfCurrent = 0;
	}

	//if ( m_bDisplayDirtyRectangle )
	//{
	//	m_hdc = m_hdcWindow;
	//	LineWidth( 1 );
	//	//CColor	cPurple( "magenta" );
	//	LineColor( m_clrDirtyRectangle );
	//	BeginPolyline();
	//	Polypoint( GFLOAT(m_nUpdateLeft), GFLOAT(m_nUpdateTop) );
	//	Polypoint( GFLOAT(m_nUpdateRight), GFLOAT(m_nUpdateTop) );
	//	Polypoint( GFLOAT(m_nUpdateRight), GFLOAT(m_nUpdateBottom) );
	//	Polypoint( GFLOAT(m_nUpdateLeft), GFLOAT(m_nUpdateBottom) );
	//	Polypoint( GFLOAT(m_nUpdateLeft), GFLOAT(m_nUpdateTop) );
	//	EndPolyline();
	//	ResetPenBrush();
	//}

	return inherited::end();
}





/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Size
		(
		long	nWidth,
		long	nHeight
		)
{
	bool	bResult = true;
	long	w = m_nWindowWidth;
	long	h = m_nWindowHeight;

	if ( nWidth < 1 )
		nWidth = 400;
	if ( nHeight < 1 )
		nHeight = 300;

	bResult = inherited::Size( nWidth, nHeight );
	if ( bResult )
	{
		if ( m_nWindowWidth != w  ||  m_nWindowHeight != h )
		{
         //DbgPrint( "New Window Size = %ld, %ld\n", m_nWindowWidth, m_nWindowHeight );
			BufferDestroy();
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * BeginContext -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::BeginContext
		(
		IDraw::EDrawContexts ctx
		)
{
	bool			bResult = inherited::BeginContext( ctx );
	if ( bResult )
	{
		HRESULT	hr;

		m_nCropStackTop = 0;
		//PushCropRectangle( 0, 0, m_nWindowWidth, m_nWindowHeight );
		PushCropRectangle( m_nUpdateLeft, m_nUpdateTop, m_nUpdateRight, m_nUpdateBottom );

		RECT	rct;
		rct.left = m_tCropCurrent.nLeft;
		rct.top = m_tCropCurrent.nTop;
		rct.right = m_tCropCurrent.nRight;
		rct.bottom = m_tCropCurrent.nBottom;

		//DbgPrint( "UpdateRect: %ld, %ld, %ld, %ld\n", rct.left, rct.top, rct.right, rct.bottom );

		//RECT	rctSrc;
		//rct.left = 0 < m_nUpdateLeft ? m_nUpdateLeft : 0;
		//rct.top = 0 < m_nUpdateTop ? m_nUpdateTop : 0;
		//rct.right = m_nUpdateRight < m_nWindowWidth ? m_nUpdateRight : m_nWindowWidth;
		//rct.bottom = m_nUpdateBottom < m_nWindowHeight ? m_nUpdateBottom : m_nWindowHeight;
		//m_hClipRegion = CreateRectRgn( rctSrc.left, rctSrc.top,
		//								rctSrc.right, rctSrc.bottom );

		if ( m_hClipRegion )
		{
			SelectClipRgn( m_hdc, NULL );
			::DeleteObject( m_hClipRegion );
			m_hClipRegion = 0;
		}

		m_hClipRegion = CreateRectRgn( m_tCropCurrent.nLeft, m_tCropCurrent.nTop,
									m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
		if ( IDraw::CTX_APPLICATION == ctx )
		{
			if ( ! SUCCEEDED( m_pSurfApplication->GetDC( &m_hdc ) ) )
			{
				bResult = false;
			}
			else
			{
				m_clrDirtyRectangle = m_clrBackBuffer;

				if ( m_hClipRegion )
				{
					SelectClipRgn( m_hdc, m_hClipRegion );
				}

#if 1
				FillColor( m_tBackgroundColor );
				if ( BrushSelect() )
				{
					::FillRect( m_hdc, &rct, m_pBrush->ToHBRUSH() );
					BrushDestroy();
				}
#else
				LOGBRUSH	brush = {0};

				brush.lbStyle = BS_SOLID;
				brush.lbColor = m_tBackgroundColor;
				brush.lbHatch = static_cast<ULONG_PTR>(~0);

				HBRUSH	hBB = ::CreateBrushIndirect( &brush );
				if ( hBB )
				{
					HGDIOBJ	hOld = ::SelectObject( m_hdc, hBB );
					if ( hOld )
					{
						::FillRect( m_hdc, &rct, hBB );
						::SelectObject( m_hdc, hOld );
					}

					::DeleteObject( hBB );
				}
#endif
				m_pSurfCurrent = m_pSurfApplication;
			}
		}
		else if ( VDraw::CTX_BACKGROUND == ctx )
		{
			RECT	rctClient = rct;

			hr = m_pSurfBackground->Blt(
									&rctClient,		// destination
									m_pSurfApplication,			// source surface
									&rct,		// source rectangle, NULL = entire surface
									DDBLT_WAIT, NULL );
			//DbgPrint( "surface blt hr = %lx\n", hr );

			if ( ! SUCCEEDED( m_pSurfBackground->GetDC( &m_hdc ) ) )
			{
				bResult = false;
			}
			else
			{
				m_pSurfCurrent = m_pSurfBackground;
				//m_hdc = m_hdcBackground;

				m_clrDirtyRectangle = m_clrBackBuffer;

				if ( m_hClipRegion )
				{
					SelectClipRgn( m_hdc, m_hClipRegion );
				}
			}
		}
		else if ( VDraw::CTX_FOREGROUND == ctx )
		{
			//if ( m_pSurfCurrent )
			{
				RECT	rctClient = rct;

				hr = m_pSurfForeground->Blt(
										&rctClient,		// destination
										m_pSurfBackground,			// source surface
										&rct,		// source rectangle, NULL = entire surface
										DDBLT_WAIT, NULL );
				//DbgPrint( "surface blt hr = %lx\n", hr );
			}
			m_pSurfForeground->GetDC( &m_hdc );
			m_pSurfCurrent = m_pSurfForeground;
			//m_hdc = m_hdcForeground;

			if ( m_clrDirtyRectangle == m_clrNone )
				m_clrDirtyRectangle = m_clrForeBuffer;
			else
				m_clrDirtyRectangle = m_clrBothBuffer;

			if ( m_hClipRegion )
			{
				SelectClipRgn( m_hdc, m_hClipRegion );
			}

			//BitBlt( m_hdcForeground, m_nUpdateLeft, m_nUpdateTop,
			//	m_nUpdateRight-m_nUpdateLeft, m_nUpdateBottom-m_nUpdateTop,
			//	m_hdcBackground, m_nUpdateLeft, m_nUpdateTop, SRCCOPY );
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * EndContext -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::EndContext
		(
		void
		)
{
	bool	bResult = true;

	PopCropRectangle();	// update rect
	//PopCropRectangle();	// window rect

	ResetPenBrush();
	if ( m_hClipRegion )
	{
		SelectClipRgn( m_hdc, NULL );
		DeleteObject( m_hClipRegion );
		m_hClipRegion = 0;
	}

	if ( m_pSurfCurrent )
		m_pSurfCurrent->ReleaseDC( m_hdc );



	m_hdc = 0;

	m_eLastContext = m_eDrawContext;

	bResult = inherited::EndContext();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::SupportsContext
		(
		void
		)
{
	return m_bDoubleBuffer;
}

/*---------------------------------------------------------------------+\

 * PushCropRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::PushCropRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	bool	bResult = inherited::PushCropRectangle( nLeft, nTop, nRight, nBottom );

	if ( bResult )
	{
		if ( m_hClipRegion )
			DeleteObject( m_hClipRegion );
		m_hClipRegion = CreateRectRgn( m_tCropCurrent.nLeft, m_tCropCurrent.nTop,
									m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
		if ( m_hClipRegion )
			SelectClipRgn( m_hdc, m_hClipRegion );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * PopCropRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::PopCropRectangle
		(
		void 
		)
{
	bool	bResult = inherited::PopCropRectangle();

	if ( bResult )
	{
		if ( m_hClipRegion )
		{
			DeleteObject( m_hClipRegion );
			m_hClipRegion = 0;
			SelectClipRgn( m_hdc, NULL );
		}
		if ( 0 < m_nCropStackTop )
		{
			m_hClipRegion = CreateRectRgn( m_tCropCurrent.nLeft, m_tCropCurrent.nTop,
				m_tCropCurrent.nRight, m_tCropCurrent.nBottom );

			if ( m_hClipRegion )
				SelectClipRgn( m_hdc, m_hClipRegion );
		}
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * RefreshRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::RefreshRectangle
		(
		void
		)
{
	bool	bResult = false;

	if ( m_bDoubleBuffer )
	{
		if ( m_pSurfWindow->IsLost() )
		{
			RECT	rctUpdate = m_tUpdateRect; //{ 0, 0, m_nWindowWidth, m_nWindowHeight };
			RECT	rctClient = rctUpdate;

			::ClientToScreen(m_hwnd, (LPPOINT)&rctClient);
			::ClientToScreen(m_hwnd, (LPPOINT)(&rctClient)+1);

			m_pSurfWindow->Blt(
							&rctClient,			// destination
							m_pSurfForeground,	// source surface
							&rctUpdate,		// source rectangle, NULL = entire surface
							DDBLT_WAIT, NULL );

			bResult = true;
		}
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * SetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::SetUpdateRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	if ( m_bDoubleBuffer )
	{
		return inherited::SetUpdateRectangle( nLeft, nTop, nRight, nBottom );
	}
	else
	{
		m_nUpdateLeft = 0;
		m_nUpdateTop = 0;
		m_nUpdateRight = m_nWindowWidth;
		m_nUpdateBottom = m_nWindowHeight;
		return true;
	}
}


/*---------------------------------------------------------------------+\

 * GetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::GetUpdateRectangle
		(
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		)
{
	*pLeft = m_nUpdateLeft;
	*pTop = m_nUpdateTop;
	*pRight = m_nUpdateRight;
	*pBottom = m_nUpdateBottom;
	return true;
}



/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::LineWidth
		(
		short nWidth
		)
{
	bool	bResult = inherited::LineWidth( nWidth );
	if ( bResult )
		ResetPenBrush();
	return bResult;
}

/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::LineColor
		(
		CColorRef rColor
		)
{
	bool	bResult = inherited::LineColor( rColor );
	if ( bResult )
		ResetPenBrush();
	return bResult;
}

/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::FillColor
		(
		CColorRef rColor
		)
{
	bool	bResult = inherited::FillColor( rColor );
	if ( bResult )
		ResetPenBrush();
	return bResult;
}


/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::HaloColor
		(
		CColorRef //rColor
		)
{
#if 1
	return true;
#else
	bool	bResult = inherited::HaloColor( rColor );
	if ( bResult )
		ResetPenBrush();
	return bResult;
#endif
}


/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	bool	bResult = inherited::FontParams( sFontName, fFontHeight );
	if ( bResult )
		ResetPenBrush();
	return bResult;
}



/*---------------------------------------------------------------------+\

 * Line -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Line
		(
		GFLOAT	xStart,
		GFLOAT	yStart,
		GFLOAT	xEnd,
		GFLOAT	yEnd
		)
{
	bool	bResult = true;
	GFLOAT	fX;
	GFLOAT	fY;

	POINT	points[2];

	TransformPoint( fX, fY, xStart, yStart );
	points[0].x = intFromFloat(fX);
	points[0].y = intFromFloat(fY);

	TransformPoint( fX, fY, xEnd, yEnd );
	points[1].x = intFromFloat(fX);
	points[1].y = intFromFloat(fY);

	if ( PenHaloSelect() )
	{
		::Polyline( m_hdc, points, 2 );
		PenDestroy();
	}

	PenSelect();
	::Polyline( m_hdc, points, 2 );

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Arc -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Arc
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
#if defined( OS_MSWIN_WCE )

	return inherited::Arc( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );

#else

	fStartAngle = normalizeAngle( fStartAngle );
	fEndAngle = normalizeAngle( fEndAngle );
	if ( ::fabsf(fStartAngle - fEndAngle) < GFLOAT_EPSILON )
	{
		return Circle( xAxis, yAxis, nRadius );
	}
	else
	{
		GFLOAT	r = TransformLength( nRadius );

		GFLOAT	x;
		GFLOAT	y;

		GFLOAT	xStart;
		GFLOAT	yStart;

		CMatrix3x3	rot = CMatrix3x3::_Rotate( fStartAngle );
		rot.Transform( xStart, yStart, GFLOAT_1, GFLOAT_0 );

		GFLOAT	xEnd;
		GFLOAT	yEnd;
		rot = CMatrix3x3::_Rotate( fEndAngle );
		rot.Transform( xEnd, yEnd, GFLOAT_1, GFLOAT_0 );

		xStart *= r;
		yStart *= r;

		xEnd *= r;
		yEnd *= r;


		TransformPoint( x, y, xAxis, yAxis );
		TransformPoint( xStart, yStart, xStart+xAxis, yStart+yAxis );
		TransformPoint( xEnd, yEnd, xEnd+xAxis, yEnd+yAxis );

		BrushDestroy();

		if ( PenHaloSelect() )
		{
			::Arc( m_hdc, intFromFloat(x-r), intFromFloat(y-r),
						intFromFloat(x+r), intFromFloat(y+r),
						intFromFloat(xStart), intFromFloat(yStart),
						intFromFloat(xEnd), intFromFloat(yEnd) );
			PenDestroy();
		}

		PenSelect();
		::Arc( m_hdc, intFromFloat(x-r), intFromFloat(y-r),
					intFromFloat(x+r), intFromFloat(y+r),
					intFromFloat(xStart), intFromFloat(yStart),
					intFromFloat(xEnd), intFromFloat(yEnd) );
		return true;
	}
#endif
}


/*---------------------------------------------------------------------+\

 * Circle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Circle
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius
		)
{
	GFLOAT	x1;
	GFLOAT	y1;
	GFLOAT	x2;
	GFLOAT	y2;

	//if ( m_bMatrixAffine )
	{
		GFLOAT	x;
		GFLOAT	y;
		GFLOAT	r;
		TransformPoint( x, y, xAxis, yAxis );
		r = TransformLength( nRadius );
		r = r < 0 ? -r : r;

		x1 = x - r;
		y1 = y - r;
		x2 = x + r;
		y2 = y + r;
	}
	//else
	//{
	//	TransformPoint( x1, y1, xAxis - nRadius, yAxis - nRadius );
	//	TransformPoint( x2, y2, xAxis + nRadius, yAxis + nRadius );
	//}

	if ( PenHaloSelect() )
	{
		BrushDestroy();
		::Ellipse( m_hdc, intFromFloat(x1), intFromFloat(y1),
						intFromFloat(x2), intFromFloat(y2) );
		PenDestroy();
	}

	PenSelect();
	BrushSelect();
	::Ellipse( m_hdc, intFromFloat(x1), intFromFloat(y1),
					intFromFloat(x2), intFromFloat(y2) );
	return true;
}

/*---------------------------------------------------------------------+\

 * Ellipse -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Ellipse
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nHeight,
		GFLOAT	nWidth
		)
{
	GFLOAT	x1;
	GFLOAT	y1;
	GFLOAT	x2;
	GFLOAT	y2;

	TransformPoint( x1, y1, xAxis - nWidth, yAxis - nHeight );
	TransformPoint( x2, y2, xAxis + nWidth, yAxis + nHeight );

	if ( PenHaloSelect() )
	{
		BrushDestroy();
		::Ellipse( m_hdc, intFromFloat(x1), intFromFloat(y1),
			intFromFloat(x2), intFromFloat(y2) );
		PenDestroy();
	}

	PenSelect();
	BrushSelect();
	::Ellipse( m_hdc, intFromFloat(x1), intFromFloat(y1),
		intFromFloat(x2), intFromFloat(y2) );
	return true;
}

/*---------------------------------------------------------------------+\

 * Pie -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Pie
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
#if defined( OS_MSWIN_WCE )

	return inherited::Pie( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );

#else

	fStartAngle = normalizeAngle( fStartAngle );
	fEndAngle = normalizeAngle( fEndAngle );
	if ( ::fabsf(fStartAngle - fEndAngle) < GFLOAT_EPSILON )
	{
		return Circle( xAxis, yAxis, nRadius );
	}
	else
	{
		GFLOAT	r = TransformLength( nRadius );

		GFLOAT	x;
		GFLOAT	y;

		GFLOAT	xStart;
		GFLOAT	yStart;

		CMatrix3x3	rot = CMatrix3x3::_Rotate( fStartAngle );
		rot.Transform( xStart, yStart, GFLOAT_1, GFLOAT_0 );

		GFLOAT	xEnd;
		GFLOAT	yEnd;
		rot = CMatrix3x3::_Rotate( fEndAngle );
		rot.Transform( xEnd, yEnd, GFLOAT_1, GFLOAT_0 );

		xStart *= r;
		yStart *= r;

		xEnd *= r;
		yEnd *= r;


		TransformPoint( x, y, xAxis, yAxis );
		TransformPoint( xStart, yStart, xStart+xAxis, yStart+yAxis );
		TransformPoint( xEnd, yEnd, xEnd+xAxis, yEnd+yAxis );

		if ( PenHaloSelect() )
		{
			BrushDestroy();
			::Pie( m_hdc, intFromFloat(x-r), intFromFloat(y-r),
						intFromFloat(x+r), intFromFloat(y+r),
						intFromFloat(xStart), intFromFloat(yStart),
						intFromFloat(xEnd), intFromFloat(yEnd) );
			PenDestroy();
		}

		BrushSelect();
		PenSelect();
		::Pie( m_hdc, intFromFloat(x-r), intFromFloat(y-r),
					intFromFloat(x+r), intFromFloat(y+r),
					intFromFloat(xStart), intFromFloat(yStart),
					intFromFloat(xEnd), intFromFloat(yEnd) );
		return true;
	}
#endif
}

/*---------------------------------------------------------------------+\

 * EndPolyline -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::EndPolyline
		(
		void
		)
{
	size_t	n = m_tPointList.Length();
	if ( 0 < n )
	{
		VDRAWPOINT*	p = m_tPointList.PointArray();
		if ( p )
		{
			BrushDestroy();
			if ( PenHaloSelect() )
			{
				::Polyline( m_hdc, p, int(n) );
				PenDestroy();
			}

			PenSelect();
			::Polyline( m_hdc, p, int(n) );
		}
	}
	return true;
}

/*---------------------------------------------------------------------+\

 * EndPolygon -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::EndPolygon
		(
		void
		)
{
	size_t	n = m_tPointList.Length();
	if ( 0 < n )
	{
		VDRAWPOINT*	p = m_tPointList.PointArray();
		if ( p )
		{
			//if ( PenHaloSelect() )
			//{
			//	BrushDestroy();
			//	::Polygon( m_hdc, p, int(n) );
			//	PenDestroy();
			//}
			BrushSelect();
			PenSelect();
			::Polygon( m_hdc, p, int(n) );
		}
	}
	return true;
}

/*---------------------------------------------------------------------+\

 * Rectangle -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Rectangle
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		CORNERSTYLE	eStyle, 	//= C_SQUARE,
		GFLOAT		nCornerSize //= 0.0f
		)
{
	bool	bResult = false;

	if ( C_SQUARE == eStyle  ||  nCornerSize < GFLOAT_EPSILON )
	{
		GFLOAT	x, y;
		GFLOAT	w, h;

		TransformPoint( x, y, xPosition, yPosition );
		w = TransformLength( nWidth );
		h = TransformLength( nHeight );
		BrushSelect();
		PenSelect();
		::Rectangle( m_hdc, int(x), int(y), int(x+w), int(y+h) );
		bResult = true;
	}
#if ! defined( OS_MSWIN_WCE )
	else if ( C_ROUND == eStyle )
	{
		GFLOAT	x, y;
		GFLOAT	w, h;
		int		c;

		TransformPoint( x, y, xPosition, yPosition );
		w = TransformLength( nWidth );
		h = TransformLength( nHeight );
		c = int(TransformLength( nCornerSize * GFLOAT_2 ));
		int n = int(ceilf(TransformLength( m_nLineWidth )));
		int	i = umax( 1, n / 2 );

		HRGN	rgn = CreateRoundRectRgn( int(x-i), int(y-i), int(x+w+i), int(y+h+i), c, c );
		if ( rgn )
		{
			if ( BrushSelect() )
				PaintRgn( m_hdc, rgn );

			if ( ! m_tLineColor.IsNonColor()  &&  0 < m_nLineWidth )
			{
				CColor	oSave = m_tFillColor;

				FillColor( m_tLineColor );

				if ( BrushSelect() )
				{
					FrameRgn( m_hdc, rgn, m_pBrush->ToHBRUSH(), n, n );
				}
				FillColor( oSave );
			}

			DeleteObject( rgn );
			bResult = true;
		}

	}
#endif
	else
	{
		bResult = inherited::Rectangle( xPosition, yPosition,
										nWidth, nHeight,
										eStyle, nCornerSize );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * TextString -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::TextString
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		VDraw::EAlignments			eAlign,
		VDraw::EVerticalAlignments	eVertAlign,
		const char*	sString,
		long		nCount
		)
{
	if ( sString )
	{
		UINT	gdiAlign = TA_LEFT | TA_BASELINE;
		switch ( eAlign )
		{
		case A_LEFT:
			gdiAlign = TA_LEFT;
			break;
		case A_CENTER:
			gdiAlign = TA_CENTER;
			break;
		case A_RIGHT:
			gdiAlign = TA_RIGHT;
			break;
		}
		switch ( eVertAlign )
		{
		case V_BASELINE:
			gdiAlign |= TA_BASELINE;
			break;
		case V_ABSBOTTOM:
			gdiAlign |= TA_BOTTOM;
			break;
		case V_TOP:
			gdiAlign |= TA_TOP;
			break;
		case V_MIDDLE:
			gdiAlign |= TA_TOP;		// we fix this down below
			break;
		}
		UINT	nAlignOld = ::SetTextAlign( m_hdc, gdiAlign );

		GFLOAT	tx;
		GFLOAT	ty;

		if ( nCount < 0 )
			nCount = long(::strlen( sString ));

		FontSelect();
		TransformPoint( tx, ty, xPosition, yPosition );
		switch ( eVertAlign )
		{
		case V_BASELINE:
		case V_ABSBOTTOM:
		case V_TOP:
			// do nothing our baseline is already set
			break;
		case V_MIDDLE:
			ty -= (m_tTextMetric.tmAscent + m_tTextMetric.tmDescent) / 2;
			break;
		}

#if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR> wsString = WideStringFromString( sString );
#endif

		int			nBkMode = 0;
		COLORREF	nBkColor = ~0U;
		if ( ! m_tHaloColor.IsNonColor()
			&&	m_tFillColor.IsNonColor() )
		{
			nBkMode = ::SetBkMode( m_hdc, TRANSPARENT );
			COLORREF cPrevColor = ::SetTextColor( m_hdc, m_tHaloColor );
#if defined( OS_MSWIN_WCE )
			::ExtTextOut( m_hdc, int(tx+1), int(ty+1), 0, NULL, wsString, nCount, NULL );
#else
			::ExtTextOutA( m_hdc, int(tx+1), int(ty+1), 0, NULL, sString, nCount, NULL );
#endif
			//::TextOutA( m_hdc, int(tx+1), int(ty+1), sString, nCount );
			::SetTextColor( m_hdc, cPrevColor );
			if ( nBkMode )
				::SetBkMode( m_hdc, nBkMode );
			if ( -1 < nBkColor )
				::SetBkColor( m_hdc, nBkColor );
		}

		nBkMode = 0;
		nBkColor = ~0U;
		if ( m_tFillColor.IsNonColor() )
		{
			nBkMode = ::SetBkMode( m_hdc, TRANSPARENT );
		}
		else
		{
			nBkMode = ::SetBkMode( m_hdc, OPAQUE );
			nBkColor = ::SetBkColor( m_hdc, m_tFillColor );
		}
		COLORREF cPrevColor = ::SetTextColor( m_hdc, m_tLineColor );
#if defined( OS_MSWIN_WCE )
		::ExtTextOut( m_hdc, int(tx), int(ty), 0, NULL, wsString, nCount, NULL );
#else
		::ExtTextOutA( m_hdc, int(tx), int(ty), 0, NULL, sString, nCount, NULL );
#endif
		//::TextOutA( m_hdc, int(tx), int(ty), sString, nCount );
		::SetTextColor( m_hdc, cPrevColor );
		::SetTextAlign( m_hdc, nAlignOld );
		if ( nBkMode )
			::SetBkMode( m_hdc, nBkMode );
		if ( -1 < nBkColor )
			::SetBkColor( m_hdc, nBkColor );
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * Video -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Video
		(
		GFLOAT			,//xPosition,
		GFLOAT			,//yPosition,
		GFLOAT			,//nWidth,
		GFLOAT			,//nHeight,
		CVariantDataRef		,//sSource,
		VXDraw::EFitments	,//eFitment, // = F_Fill,
		VXDraw::EAlignments	,//eAlign, // = A_Center,
		VXDraw::EVerticalAlignments ,//eVertAlign, // = V_Middle,
		bool		//bMirror // = false
		)
{
	return false;
}



/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	CDrawWinDD::Image
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		const char*	sSource,
		VDraw::EFitments	eFitment, // = F_Fill,
		VDraw::EAlignments	eAlign, // = A_Center,
		VDraw::EVerticalAlignments eVertAlign // = V_Middle,
		)
{
	return inherited::Image( xPosition, yPosition, nWidth, nHeight, sSource, eFitment, eAlign, eVertAlign );
}


bool	CDrawWinDD::ImagePreloaded
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		IDraw::VImagePtr	pVoid,
		EFitments			eFitment,	// = F_FILL,
		EAlignments			eAlign,		// = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign	// = V_MIDDLE
		)
{
	bool		bResult = false;
	//LPPICTURE	pPicture;
#if !defined( OS_MSWIN_WCE )

	do_sequence
	{
		if ( ! pVoid )
			break;

		XOleImage*	pImage = static_cast<XOleImage*>( pVoid );


		TransformPoint( xPosition, yPosition, xPosition, yPosition );


		nWidth = TransformLength( nWidth );
		nHeight = TransformLength( nHeight );

		GFLOAT	nSrcWidth = GFLOAT(pImage->nWidth);
		GFLOAT	nSrcHeight = GFLOAT(pImage->nHeight);
		GFLOAT	nSrcRatio = nSrcHeight / nSrcWidth;

		GFLOAT	nVwRatio = nHeight / nWidth;

		GFLOAT	nNewWidth = nWidth;
		GFLOAT	nNewHeight = nHeight;
		GFLOAT	nScale;

		if ( eFitment != F_FILL )
		{
			switch ( eFitment )
			{
			case VDraw::F_ORIGINAL:
				{
					nNewWidth = nSrcWidth;
					nNewHeight = nSrcHeight;
					switch ( eAlign )
					{
					case VDraw::A_CENTER:
						xPosition += (nWidth - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						xPosition += (nWidth - nNewWidth);
						break;
					}
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						yPosition += (nHeight - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						yPosition += (nHeight - nNewHeight);
						break;
					}
				}
				break;

			case VDraw::F_SCALED:
				if ( nVwRatio < nSrcRatio )	// height bound
				{
					nNewHeight = nHeight;
					nScale = nHeight / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case VDraw::A_CENTER:
						xPosition += (nWidth - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						xPosition += (nWidth - nNewWidth);
						break;
					}
				}
				else
				{
					nNewWidth = nWidth;
					nScale = nWidth / nSrcWidth;
					nNewHeight = nScale * nSrcHeight;
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						yPosition += (nHeight - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						yPosition += (nHeight - nNewHeight);
						break;
					}
				}
				break;

			case VDraw::F_ZOOM:
				if ( nSrcRatio < nVwRatio )
				{
					nNewHeight = nHeight;
					nScale = nHeight / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case VDraw::A_CENTER:
						xPosition += (nWidth - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						xPosition += (nWidth - nNewWidth);
						break;
					}
				}
				else
				{
					nNewWidth = nWidth;
					nScale = nWidth / nSrcWidth;
					nNewHeight = nScale * nSrcHeight;
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						yPosition += (nHeight - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						yPosition += (nHeight - nNewHeight);
						break;
					}
				}
				break;
			default:
				break;
			}
		}


		HRESULT hr = pImage->pPicture->Render( m_hdc, (long)xPosition, (long)yPosition, 
										(long)nNewWidth, (long)nNewHeight, 
										0, pImage->nmH, pImage->nmW, -pImage->nmH, 0 );

		bResult = SUCCEEDED( hr );
	}

#endif // ! OS_MSWIN_WCE

	return bResult;
}

bool	CDrawWinDD::ImageLoadFile
		(
		const char*			sSource,
		IDraw::VImagePtr*	ppImage
		)
{
	bool		bResult = false;
	XOleImage*	pImage = 0;
	LPPICTURE	pPicture;

#if !defined( OS_MSWIN_WCE )

	do_sequence
	{
		HANDLE	hFile;
		hFile = CreateFileA( sSource, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
		if ( INVALID_HANDLE_VALUE == hFile )
			break;

		DWORD	dwFileSize = GetFileSize( hFile, NULL );
		if ( dwFileSize < 1 )
		{
			CloseHandle( hFile );
			break;
		}

		LPVOID	pData = NULL;
		HGLOBAL	hGlobal = GlobalAlloc( GMEM_MOVEABLE, dwFileSize );
		if ( ! hGlobal )
		{
			CloseHandle( hFile );
			break;
		}

		pData = GlobalLock( hGlobal );

		DWORD	dwBytesRead = 0;

		BOOL bRead = ReadFile( hFile, pData, dwFileSize, &dwBytesRead, NULL );
		GlobalUnlock( hGlobal );
		CloseHandle( hFile );
		if ( ! bRead )
			break;

		LPSTREAM	pStm = NULL;
		HRESULT		hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pStm );

		if ( !SUCCEEDED(hr)  ||  !pStm )
			break;

		hr = OleLoadPicture( pStm, dwFileSize, FALSE, IID_IPicture, (LPVOID*)&pPicture );
		pStm->Release();
		if ( !SUCCEEDED(hr)  ||  !pPicture )
			break;

		// get 'high-metric' size of picture
		long	nmW;
		long	nmH;

		pPicture->get_Width( &nmW );
		pPicture->get_Height( &nmH );

		SIZEL	szHM;
		SIZEL	szPX;

		szHM.cx = nmW;
		szHM.cy = nmH;

		::AtlHiMetricToPixel( &szHM, &szPX );

		pImage = new XOleImage;
		if ( ! pImage )
		{
			if ( pPicture )
				pPicture->Release();
			break;
		}

		pImage->nWidth = szPX.cx;
		pImage->nHeight = szPX.cy;
		pImage->nmW = nmW;
		pImage->nmH = nmH;
		pImage->pPicture = pPicture;

		bResult = true;


	}

#endif // ! OS_MSWIN_WCE

	*ppImage = (VImagePtr)pImage;

	return bResult;
}

bool	CDrawWinDD::ImageRelease
		(
		VImagePtr	pImage
		)
{
	bool	bResult = false;

	if ( pImage )
	{
		XOleImage*	pOleImage = static_cast<XOleImage*>( pImage );

		pOleImage->Destroy();
		bResult = true;
	}

	return bResult;
}




NAMESPACE_COMMON_END


#endif	// OS_MSWIN

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

