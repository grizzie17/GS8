/*---------------------------------------------------------------------+\
|
|	VDrawOpenGL.cpp  --  draw implementation for OpenGL
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
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	08-Oct-2009			R.Hosea		(Reviewed by: M.Rose)
		Kluge for 1024x768
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VDrawOpenGL.h"
#include "VPluginFactory.h"

#include "UMachine.h"

#if defined( OS_MSWIN )	// brackets whole file


#	include <math.h>
#	include <float.h>

//#include <ft2build.h>
//#include <FTGL/ftgl.h>

#	include "SOIL.h"
//#	include "image_helper.h"
//#	include "stb_image_aug.h"
#	include "LogFile.h"


/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#define DEFAULT_LINE_WIDTH 1

#define FONT_MAXNUMGLYPHS	255

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
namespace Yogi { namespace Common {

/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
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

PLUGIN_CREATE_FACTORY( VDrawOpenGL );


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/

CBitmapFont::CBitmapFont
		(
		void
		)
		: m_sFontname()
		, m_nFontHeight( 0 )
		, m_nFontListBase( 0 )
		, m_hDC( 0 )
{
	::memset( m_aWidths, 0, sizeof(m_aWidths) );
}

CBitmapFont::CBitmapFont
		(
		const CBitmapFont&	r
		)
		: m_sFontname( r.m_sFontname )
		, m_nFontHeight( r.m_nFontHeight )
		, m_nFontListBase( r.m_nFontListBase )
		, m_hDC( r.m_hDC )
{
	::memcpy_s( m_aWidths, sizeof(m_aWidths), r.m_aWidths, sizeof(r.m_aWidths) );
	::memcpy_s( &m_tTextMetric, sizeof(m_tTextMetric), &r.m_tTextMetric, sizeof(r.m_tTextMetric) );
}

CBitmapFont::~CBitmapFont
		(
		void
		)
{
	if ( m_nFontListBase )
		glDeleteLists( m_nFontListBase, 256 );
	m_nFontListBase = 0;
}

bool	CBitmapFont::CreateFont
		(
		HDC&		rDC,
		const char*	sFontname,
		int			nFontHeight
		)
{
	bool	bResult = false;

	if ( rDC  &&  sFontname )
	{
		m_hDC = rDC;
		m_sFontname = sFontname;
		m_nFontHeight = nFontHeight;

		LOGFONTA	lf = {0};
		lf.lfHeight = nFontHeight;
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = ANSI_CHARSET;
		lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lf.lfQuality = DEFAULT_QUALITY;
		lf.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
		m_sFontname.CopyTo( lf.lfFaceName, sizeof(lf.lfFaceName) );

		HANDLE	hFont = ::CreateFontIndirectA( &lf );
		if ( hFont )
		{
			HANDLE	hFontOld = ::SelectObject( m_hDC, hFont );
			if ( hFontOld )
			{
				m_nFontListBase = glGenLists( 256 );
				if ( m_nFontListBase )
				{
					BOOL	bf = wglUseFontBitmaps( m_hDC, 0, 255, m_nFontListBase );
					if ( bf )
					{
						::GetTextMetrics( m_hDC, &m_tTextMetric );
						GetCharABCWidths( m_hDC, 0, 255, m_aWidths );
						bResult = true;
					}
					::SelectObject( m_hDC, hFontOld );
				}
			}
		}
	}

	return bResult;
}


bool	CBitmapFont::DrawTextString
		(
		int				xPosition,
		int				yPosition,
		IDraw::EAlignments	eAlign,
		IDraw::EVerticalAlignments	eVertAlign,
		const CColor&	clr,
		const char*		sString,
		long			nCount	// = -1
		)
{
	if ( sString )
	{
		if ( nCount < 0 )
			nCount = long(::strlen( sString ));


		long	nWidth = 0;	// pixels
		for ( long i = 0; i < nCount; ++i )
		{
			int c = sString[i];
			nWidth += m_aWidths[c].abcA + m_aWidths[c].abcB + m_aWidths[c].abcC;
		}

		switch ( eAlign )
		{
		case IDraw::A_LEFT:
			// do nothing
			break;
		case IDraw::A_CENTER:
			xPosition -= nWidth / 2;
			break;
		case IDraw::A_RIGHT:
			xPosition -= nWidth;
			break;
		}
		switch ( eVertAlign )
		{
		case IDraw::V_BASELINE:
			break;
		case IDraw::V_ABSBOTTOM:
			yPosition += m_tTextMetric.tmDescent;
			break;
		case IDraw::V_CAPLINE:
		case IDraw::V_TOP:
			yPosition -= m_tTextMetric.tmAscent;
			break;
		case IDraw::V_MIDDLE:
			yPosition -= m_tTextMetric.tmHeight / 2;
			break;
		}


		//int			nBkMode = 0;
		//COLORREF	nBkColor = ~0U;

		//nBkMode = 0;
		//nBkColor = ~0U;
		//GFLOAT	fHeight = TransformLength( m_fFontHeight );
		glColor3f(	(GLfloat)(clr.GetRed()/255.0),
					(GLfloat)(clr.GetGreen()/255.0),
					(GLfloat)(clr.GetBlue()/255.0));
		GLboolean bTexture2d = glIsEnabled( GL_TEXTURE_2D );
		if ( bTexture2d )
			glDisable( GL_TEXTURE_2D );
		GLboolean bDepth = glIsEnabled( GL_DEPTH_TEST );
		if ( bDepth )
			glDisable( GL_DEPTH_TEST );
		GLboolean bDMask;
		glGetBooleanv( GL_DEPTH_WRITEMASK, &bDMask );
		if ( bDMask )
			glDepthMask( GL_FALSE );
		glPushMatrix();
		glRasterPos2i( xPosition, yPosition );
		//glTranslatef( tx, ty, 0.0 );
		//glScalef( fHeight, fHeight, fHeight );
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_nFontListBase);
		GLsizei len = GLsizei(nCount);
		glCallLists( len, GL_UNSIGNED_BYTE, sString );
		glPopAttrib();
		glPopMatrix();
		if ( bDMask )
			glDepthMask( GL_TRUE );
		if ( bDepth )
			glEnable( GL_DEPTH_TEST );
		if ( bTexture2d )
			glEnable( GL_TEXTURE_2D );
		//::ExtTextOutA( m_hdc, int(tx), int(ty), 0, NULL, sString, nCount, NULL );
	}
	return true;
}


bool	CBitmapFont::operator ==
		(
		const CBitmapFont& r
		) const
{
	if ( r.m_nFontHeight != m_nFontHeight )
		return false;
	if ( r.m_sFontname != m_sFontname )
		return false;
	return true;
}

unsigned long
		CBitmapFont::GetHash
		(
		void
		) const
{
	unsigned long	uHash = m_sFontname.Hash();
	uHash <<= 6;
	uHash |= m_nFontHeight;

	return uHash;
}





/*---------------------------------------------------------------------+\

 * VDrawOpenGL - constructor

\+---------------------------------------------------------------------*/
VDrawOpenGL::VDrawOpenGL
		(
		void
		)
		: inherited()
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_hRC( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );
}

VDrawOpenGL::VDrawOpenGL
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_hRC( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );
}


VDrawOpenGL::VDrawOpenGL
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_hRC( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );

}


/*---------------------------------------------------------------------+\

 * ~VDrawOpenGL - destructor

\+---------------------------------------------------------------------*/
VDrawOpenGL::~VDrawOpenGL
		(
		void
		)
{
	THashTableEnumerator<CCharString, CBitmapFont*>	e = m_tFontTable.GetEnumerator();

	while ( e.MoveNext() )
	{
		CBitmapFont*const*	pp = e.Current();
		if ( pp )
		{
			CBitmapFont*	p = *pp;
			if ( p )
				delete p;
		}
	}

	if ( m_hRC )
		wglDeleteContext(m_hRC);

}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * SetHDC -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::SetHDC
		(
		HWND	hWindow,
		HDC		hDC,
		LPRECT	//pRect
		)
{
	m_hWnd = hWindow;
	m_hDC = hDC;

	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;

	ppfd = &pfd;

	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	//ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_RGBA;
	ppfd->cColorBits = 24;
	ppfd->cDepthBits = 16;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;
	ppfd->iLayerType = PFD_MAIN_PLANE;

	pixelformat = ChoosePixelFormat(m_hDC, ppfd);
	if ( pixelformat )
		SetPixelFormat(m_hDC, pixelformat, ppfd);
	if ( ! m_hRC )
		m_hRC = wglCreateContext(m_hDC);
	//wglMakeCurrent(m_hDC, m_hRC);

	//glClearColor(0, 0, 0, 0.5);
	//glClearDepth(1.0);

	m_aVertexList.SetBlockSize(20);
	m_aVertexList.PointItem(90);
	m_aVertexList.Truncate();

}

/*---------------------------------------------------------------------+\

 * UpdateRect -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::UpdateRect
		(
		LPRECT	pRect
		)
{
	m_tUpdateRect = *pRect;
}



/*---------------------------------------------------------------------+\

 * FontInitialize -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::FontInitialize
		(
		void
		)
{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );
}



/*---------------------------------------------------------------------+\

 * FontSelect -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::FontSelect
		(
		void
		)
{
	bool	bResult = true;

	if ( ! m_pFont )
	{
		bResult = false;

		CBitmapFont*const*	ppFont;
		CCharString		sKey;
		long			nHeight = long(TransformLength( m_fFontHeight ) + GFLOAT_1_2);

		sKey.Format( "%d:%s", nHeight, m_sFontName );

		ppFont = m_tFontTable.Find( sKey );
		if ( ppFont )
		{
			m_pFont = *ppFont;
			bResult = true;
		}
		else
		{
			CBitmapFont*	pf = new CBitmapFont;
			if ( pf )
			{
				if ( pf->CreateFont( m_hDC, m_sFontName, nHeight ) )
				{
					if ( m_tFontTable.Add( sKey, pf ) )
					{
						ppFont = m_tFontTable.Find( sKey );
						if ( ppFont )
						{
							LOCAL_PRINT( "Font Created: %s : %d\n", m_sFontName, nHeight );
							m_pFont = *ppFont;
							bResult = true;
						}
					}
				}
				if ( ! bResult )
					delete pf;
			}
		}
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * FontDestroy -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::FontDestroy
		(
		void
		)
{
	if ( m_pFont )
		m_pFont = 0;
}



/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

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
void*	VDrawOpenGL::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDrawWin32 )
			pI = INTERFACE_THIS( IDrawWin32Ptr );
		else
			pI = 0;
	}

	return pI;
}



/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::begin
		(
		void
		)
{
	bool	bResult = inherited::begin();
	if ( bResult )
	{

		wglMakeCurrent(m_hDC, m_hRC);
		glClearColor(	(GLfloat)(m_tBackgroundColor.GetRed()/255.0),
						(GLfloat)(m_tBackgroundColor.GetGreen()/255.0),
						(GLfloat)(m_tBackgroundColor.GetBlue()/255.0),
						1.0f);
		glDisable( GL_DEPTH_TEST );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		GLenum		err;
		GLdouble	half_width  = (GLdouble)m_nWindowWidth / 2.0;
		GLdouble	half_height = (GLdouble)m_nWindowHeight / 2.0;

		glViewport( 0, 0, m_nWindowWidth, m_nWindowHeight );
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho( -half_width, half_width, -half_height, half_height, NEAR_Z, FAR_Z);
		//glOrtho( 0, m_nWindowWidth, m_nWindowHeight, 0, NEAR_Z, FAR_Z );

		glMatrixMode( GL_MODELVIEW);
		glLoadIdentity();

		// check for errors, really should be a while loop since errors can be stacked.

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			LogPrint("%s: Error : %d\n", __FUNCTION__, err);
			bResult = false;
		}
	}

	//m_hRC = wglCreateContext(m_hDC);

	// Set location in front of camera
	//glMatrixMode( GL_MODELVIEW );
	//glTranslated(0, 0, -10);

	return bResult;
}

/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::end
		(
		void
		)
{
	//glDisable( GL_TEXTURE_2D );
	ResetPenBrush();

	glDisable( GL_SCISSOR_TEST );
	glScissor( 0, 0, 0, 0 );

	glFlush();
	SwapBuffers( m_hDC );

	//clear the working buffer immediately following a buffer swap
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	wglMakeCurrent(NULL, NULL);


	return inherited::end();
}


/*---------------------------------------------------------------------+\

 * InitialMatrix -

\+---------------------------------------------------------------------*/
CMatrix3x3  VDrawOpenGL::InitialMatrix( void )
{
	// TODO: fix the fetch of window size
//	int nWindowWidth = 800;

//	int nWindowHeight = nWindowWidth * 3 / 4;
	CMatrix3x3	mInitial;  // this will initialize with the identity matrix
	CMatrix3x3	mOriginOffset = CMatrix3x3::_Translate( GFLOAT(-m_nWindowWidth/2), GFLOAT(m_nWindowHeight/2) );

	CMatrix3x3	mMirrorX = CMatrix3x3::_ReflectX();

	mInitial *= mMirrorX;
	mInitial *= mOriginOffset;

	//mInitial = CMatrix3x3::_Identity();

	return mInitial;
}




/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Size
		(
		long	nWidth,
		long	nHeight
		)
{
	bool	bResult = false;

	bResult = inherited::Size( nWidth, nHeight );
	//if ( bResult )
	//{
	//	if ( m_hRC )
	//	{
	//		if ( 0 < nWidth  &&  0 < nHeight )
	//		{
	//			GLenum		err;
	//			GLdouble	half_width  = (GLdouble) (nWidth >> 1);
	//			GLdouble	half_height = (GLdouble) (nHeight >> 1);

	//			glViewport( 0, 0, nWidth, nHeight );
	//			glMatrixMode(GL_PROJECTION);
	//			glLoadIdentity();
	//			glOrtho( -half_width, half_width, -half_height, half_height, NEAR_Z, FAR_Z);

	//			glMatrixMode( GL_MODELVIEW);

	//			// check for errors, really should be a while loop since errors can be stacked.

	//			if ((err = glGetError()) != GL_NO_ERROR)
	//			{
	//				LogPrint("Error during ReshapeCB : %d\n", err);
	//				bResult = false;
	//			}
	//		}
	//	}
	//}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * BeginContext -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::BeginContext
		(
		IDraw::EDrawContexts ctx
		)
{
	bool	bResult = inherited::BeginContext( ctx );

	if ( bResult )
	{
		m_nCropStackTop = 0;
		PushCropRectangle( m_nUpdateLeft, m_nUpdateTop, m_nUpdateRight, m_nUpdateBottom );
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * EndContext -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::EndContext
		(
		void
		)
{
	PopCropRectangle();	// update rectangle

	return inherited::EndContext();
}


/*---------------------------------------------------------------------+\

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::SupportsContext
		(
		void
		)
{
	return true;
	//return inherited::SupportsContext();
}


/*---------------------------------------------------------------------+\

 * PushCropRectangle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::PushCropRectangle
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
		if ( 0 < m_nCropStackTop)
		{
			glEnable( GL_SCISSOR_TEST );
			glScissor( m_tCropCurrent.nLeft, m_tCropCurrent.nBottom,
						m_tCropCurrent.nRight-m_tCropCurrent.nLeft,
						m_tCropCurrent.nTop-m_tCropCurrent.nBottom );
			DbgPrint( "PushCropRectangle: %ld, %ld, %ld, %ld\n",
						nLeft, nTop, nRight, nBottom );
		}
		else
		{
			glDisable( GL_SCISSOR_TEST );
			glScissor( 0, 0, 0, 0 );
			DbgPrint( "PushCropRectangle: ---------\n" );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * PopCropRectangle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::PopCropRectangle
		(
		void
		)
{
	bool	bResult = inherited::PopCropRectangle();

	if ( bResult )
	{
		if ( 0 < m_nCropStackTop)
		{
			glEnable( GL_SCISSOR_TEST );
			glScissor( m_tCropCurrent.nLeft, m_tCropCurrent.nBottom,
						m_tCropCurrent.nRight-m_tCropCurrent.nLeft,
						m_tCropCurrent.nTop-m_tCropCurrent.nBottom );
			DbgPrint( "PopCropRectangle: %ld, %ld, %ld, %ld\n",
					m_tCropCurrent.nLeft, m_tCropCurrent.nTop, m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
		}
		else
		{
			glDisable( GL_SCISSOR_TEST );
			glScissor( 0, 0, 0, 0 );
			DbgPrint( "PopCropRectangle: ---------\n" );
		}
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * MergeCropStack -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::MergeCropStack
		(
		void
		)
{
	XCropRect*	p = m_aCropStack.PointArray();
	if ( p  &&  0 < m_nCropStackTop )
	{
		XCropRect*	pEnd = p + m_nCropStackTop;

		m_tCropCurrent = *p;	// initialize to bottom of stack;

		while ( p < pEnd )
		{
			if ( m_tCropCurrent.nLeft < p->nLeft )
				m_tCropCurrent.nLeft = p->nLeft;
			if ( p->nTop < m_tCropCurrent.nTop )
				m_tCropCurrent.nTop = p->nTop;
			if ( p->nRight < m_tCropCurrent.nRight )
				m_tCropCurrent.nRight = p->nRight;
			if (  m_tCropCurrent.nBottom < p->nBottom )
				m_tCropCurrent.nBottom = p->nBottom;
			++p;
		}

		//long	w = m_nWindowWidth / 2;
		//long	h = m_nWindowHeight / 2;

		//m_tCropCurrent.nLeft += w;
		//m_tCropCurrent.nBottom += h;
		//m_tCropCurrent.nRight += w;
		//m_tCropCurrent.nTop += h;
	}
	else
	{
		m_tCropCurrent.nLeft = 0;
		m_tCropCurrent.nTop = m_nWindowHeight;
		m_tCropCurrent.nRight = m_nWindowWidth;
		m_tCropCurrent.nBottom = 0;
	}
}



/*---------------------------------------------------------------------+\

 * SetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::SetUpdateRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	return inherited::SetUpdateRectangle( nLeft, nTop, nRight, nBottom );
}


/*---------------------------------------------------------------------+\

 * GetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::GetUpdateRectangle
		(
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		)
{
	return inherited::GetUpdateRectangle( pLeft, pTop, pRight, pBottom );
}



/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::LineWidth
		(
		short nWidth
		)
{
	return inherited::LineWidth( nWidth );
}

/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::LineColor
		(
		ConstCColorRef rColor
		)
{
	return inherited::LineColor( rColor );
}

/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::FillColor
		(
		ConstCColorRef rColor
		)
{
	return inherited::FillColor( rColor );
}


/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::HaloColor
		(
		ConstCColorRef rColor
		)
{
	return inherited::HaloColor( rColor );
}




/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	bool	bResult = inherited::FontParams( sFontName, fFontHeight );
	if ( bResult )
	{
		FontDestroy();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * ResetPenBrush -

\+---------------------------------------------------------------------*/
void	VDrawOpenGL::ResetPenBrush
		(
		void
		)
{
//	DestroyBrush();
//	DestroyPen();
	FontDestroy();
}


/*---------------------------------------------------------------------+\

 * Line -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Line
		(
		GFLOAT	xStart,
		GFLOAT	yStart,
		GFLOAT	xEnd,
		GFLOAT	yEnd
		)
{
	bool	bResult = true;

	SetLineParms();

	vddsBegin( GL_LINE_STRIP );

	vddsVertexTransform( xStart, yStart );
	vddsVertexTransform( xEnd, yEnd );

	vddsEnd();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Arc -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Arc
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	bool	bResult = BeginPolyline();
	if ( bResult )
	{
		bResult = ArcStrokeAsPolyline( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
		if ( bResult )
			bResult = EndPolyline();
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Circle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Circle
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	fRadius
		)
{
	bool	bResult = BeginPolygon();
	if ( bResult )
	{
		bResult = CircleStrokeAsPolygon( xAxis, yAxis, fRadius );
		if ( bResult )
		{
			if(SetFillParms())
			{
				m_nGLMode = GL_TRIANGLE_FAN;
				vddsEnd();
			}
			if(SetLineParms())
			{
				m_nGLMode = GL_LINE_LOOP;
				vddsEnd();
			}
		}
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * Ellipse -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Ellipse
		(
		GFLOAT	,//xAxis,
		GFLOAT	,//yAxis,
		GFLOAT	,//nHeight,
		GFLOAT	//nWidth
		)
{

	LogPrint("VDrawOpenGL::Ellipse called but not implemented.");
	return true;
}

/*---------------------------------------------------------------------+\

 * Pie -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Pie
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	bool	bResult = BeginPolygon();
	if ( bResult )
	{
		bResult = PieStrokeAsPolygon( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
		if ( bResult )
		{
			if(SetFillParms())
			{
				m_nGLMode = GL_TRIANGLE_FAN;
				vddsEnd();
			}
			if(SetLineParms())
			{
				m_nGLMode = GL_LINE_LOOP;
				vddsEnd();
			}
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * SetFillParms -

\+---------------------------------------------------------------------*/
bool 	VDrawOpenGL::SetFillParms()
{
	if(m_tFillColor.IsNonColor())
	{
		return false;
	}
	else
	{
		CColorPtr	pClr;
		if ( CColor::BackgroundColor() == m_tFillColor )
			pClr = &m_tBackgroundColor;
		else
			pClr = &m_tFillColor;

		glColor3f(	(GLfloat)(pClr->GetRed()/255.0),
					(GLfloat)(pClr->GetGreen()/255.0),
					(GLfloat)(pClr->GetBlue()/255.0));
		//glIndex(m_tFillColor, FULL_OPAQUE);
		glLineWidth( 0.1f );

		return true;
	}
}

/*---------------------------------------------------------------------+\

 * SetLineParms -

\+---------------------------------------------------------------------*/
bool 	VDrawOpenGL::SetLineParms()
{
	if(m_tLineColor.IsNonColor())
	{
		return false;
	}
	else
	{
		CColorPtr	pClr;
		if ( CColor::BackgroundColor() == m_tFillColor )
			pClr = &m_tBackgroundColor;
		else
			pClr = &m_tLineColor;

		glColor3f(	(GLfloat)(pClr->GetRed()/255.0),
					(GLfloat)(pClr->GetGreen()/255.0),
					(GLfloat)(pClr->GetBlue()/255.0));
		//glIndex( m_tLineColor, FULL_OPAQUE);

		m_nLineWidth = (0 < m_nLineWidth)?m_nLineWidth:DEFAULT_LINE_WIDTH;
		float	fWidth = TransformLength( m_nLineWidth );
		glLineWidth( fWidth );
		return true;
	}
}



/*---------------------------------------------------------------------+\

 * BeginPolygon -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::BeginPolygon
		(
		void
		)
{
	m_aVertexList.Truncate();
	//m_tPointList.Truncate();
	return true;
}


/*---------------------------------------------------------------------+\

 * EndPolygon -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::EndPolygon
		(
		void
		)
{
    if(SetFillParms())
    {
		m_nGLMode = GL_POLYGON;
		vddsEnd();
    }
    if(SetLineParms())
    {
		m_nGLMode = GL_LINE_LOOP;
		vddsEnd();
    }
    return true;
}



/*---------------------------------------------------------------------+\

 * BeginPolyline -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::BeginPolyline
		(
		void
		)
{
	vddsBegin( GL_LINE_STRIP );
	//m_tPointList.Truncate();
	return true;
}

/*---------------------------------------------------------------------+\

 * EndPolyline -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::EndPolyline
		(
		void
		)
{
	SetLineParms();
	vddsEnd();
	return true;
}


/*---------------------------------------------------------------------+\

 * Polypoint -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Polypoint
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	vddsVertexTransform( x, y );
	return true;
}


/*---------------------------------------------------------------------+\

 * PolypointNoTmx -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::PolypointNoTmx
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	vddsVertex( x, y );
	return true;
}





/*---------------------------------------------------------------------+\

 * Rectangle -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Rectangle
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
	if ( C_SQUARE == eStyle )
	{
		vddsBegin( GL_QUADS );
		vddsVertexTransform( xPosition, yPosition );
		vddsVertexTransform( xPosition + nWidth, yPosition );
		vddsVertexTransform( xPosition + nWidth, yPosition + nHeight );
		vddsVertexTransform( xPosition, yPosition + nHeight );

		if(SetFillParms())
		{
			m_nGLMode = GL_QUADS;
			vddsEnd();
		}
		if(SetLineParms())
		{
			m_nGLMode = GL_LINE_LOOP;
			vddsEnd();
		}
		bResult = true;
	}
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
bool	VDrawOpenGL::TextString
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		VDraw::EAlignments	eAlign,
		VDraw::EVerticalAlignments	eVertAlign,
		const char*		sString,
		long			nCount
		)
{
	if ( sString )
	{
		if ( FontSelect() )
		{
			GFLOAT	tx;
			GFLOAT	ty;

			TransformPoint( tx, ty, xPosition, yPosition );

			if ( ! m_tHaloColor.IsNonColor()  &&  m_tFillColor.IsNonColor() )
			{
				m_pFont->DrawTextString( int(tx+1), int(ty-1), eAlign, eVertAlign, m_tHaloColor, sString, nCount );
			}

			m_pFont->DrawTextString( int(tx), int(ty), eAlign, eVertAlign, m_tLineColor, sString, nCount );
		}

	}

	return true;
}








/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Image
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


/*---------------------------------------------------------------------+\

 * ImagePreloaded -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::ImagePreloaded
		(
		GFLOAT				xPosition,
		GFLOAT				yPosition,
		GFLOAT				nWidth,
		GFLOAT				nHeight,
		IDraw::VImagePtr	pVImage,
		EFitments			eFitment,	// = F_FILL,
		EAlignments			eAlign,		// = A_CENTER,		// used for F_FitAspect & F_FillAspect
		EVerticalAlignments	eVertAlign	// = V_MIDDLE
		)
{
	bool		bResult = false;
	//LPPICTURE	pPicture;

	//GLuint		nTexture;

	do_sequence
	{
		if ( ! pVImage )
			break;

		XTexImage*	pImage = static_cast<XTexImage*>(pVImage);

		glColor3f(	(float)1.0, (float)1.0, (float)1.0);

		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, pImage->nTexture );

		GFLOAT	x;
		GFLOAT	y;
		GFLOAT	w;
		GFLOAT	h;

		TransformPoint( x, y, xPosition, yPosition );
		w = TransformLength( nWidth );
		h = TransformLength( nHeight );


		GFLOAT	nSrcWidth = GFLOAT(pImage->nWidth);
		GFLOAT	nSrcHeight = GFLOAT(pImage->nHeight);
		GFLOAT	nSrcRatio = nSrcHeight / nSrcWidth;

		GFLOAT	nVwRatio = h / w;

		GFLOAT	nNewWidth = w;
		GFLOAT	nNewHeight = h;
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
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						x += (w - nNewWidth);
						break;
					}
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						y -= (h - nNewHeight);
						break;
					}
				}
				break;

			case VDraw::F_SCALED:
				if ( nVwRatio < nSrcRatio )	// height bound
				{
					nNewHeight = h;
					nScale = h / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case VDraw::A_CENTER:
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						x += (w - nNewWidth);
						break;
					}
				}
				else
				{
					nNewWidth = w;
					nScale = w / nSrcWidth;
					nNewHeight = nScale * nSrcHeight;
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						y -= (h - nNewHeight);
						break;
					}
				}
				break;

			case VDraw::F_ZOOM:
				if ( nSrcRatio < nVwRatio )
				{
					nNewHeight = h;
					nScale = h / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case VDraw::A_CENTER:
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case VDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case VDraw::A_RIGHT:
						x += (w - nNewWidth);
						break;
					}
				}
				else
				{
					nNewWidth = w;
					nScale = w / nSrcWidth;
					nNewHeight = nScale * nSrcHeight;
					switch ( eVertAlign )
					{
					case VDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case VDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case VDraw::V_ABSBOTTOM:
					default:
						y -= (h - nNewHeight);
						break;
					}
				}
				break;
			default:
				break;
			}
		}



		glBegin( GL_QUADS );
		glTexCoord2d( 0.0f, 0.0f );	glVertex2d( x, y );
		glTexCoord2d( 1.0f, 0.0f );	glVertex2d( x+nNewWidth, y );
		glTexCoord2d( 1.0f, 1.0f );	glVertex2d( x+nNewWidth, y-nNewHeight );
		glTexCoord2d( 0.0f, 1.0f ); glVertex2d( x, y-nNewHeight );
		glEnd();

		glDisable( GL_TEXTURE_2D );


		bResult = true;
	}


	return bResult;
}

/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::ImageLoadFile
		(
		const char*			sSource,
		IDraw::VImagePtr*	ppImage
		)
{
	bool		bResult = false;
	XTexImage*	pImage = 0;

	do_sequence
	{
		int		w;
		int		h;
		int		ch;

		unsigned char*	pImgData = SOIL_load_image( sSource, &w, &h, &ch, SOIL_LOAD_AUTO );
		if ( ! pImgData )
			break;

		GLuint	uTex = SOIL_create_OGL_texture( pImgData, w, h, ch, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS );

		//glGenTextures( 1, &uTex );
		glBindTexture( GL_TEXTURE_2D, uTex );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

		//GLuint	uClrMode = (4 == ch) ? GL_RGBA : GL_RGB;
		//glTexImage2D( GL_TEXTURE_2D, 0, uClrMode, w, h, 0, uClrMode, GL_UNSIGNED_BYTE, pImgData );

		pImage = new XTexImage;
		if ( ! pImage )
			break;

		pImage->nWidth = w;
		pImage->nHeight = h;

		// TODO: calculate the texture size and put into the nmW and nmH members
		//pImage->nmW = nmW;
		//pImage->nmH = nmH;
		pImage->nTexture = uTex;

		SOIL_free_image_data( pImgData );

		bResult = true;

	}

	*ppImage = (VImagePtr)pImage;

	return bResult;
}

/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::ImageRelease
		(
		IDraw::VImagePtr	pVImage
		)
{
	bool	bResult = false;

	if ( pVImage )
	{
		XTexImage*	pTexImage = static_cast<XTexImage*>( pVImage );

		pTexImage->Destroy();
		bResult = true;
	}

	return bResult;
}




/*---------------------------------------------------------------------+\

 * Video -

\+---------------------------------------------------------------------*/
bool	VDrawOpenGL::Video
		(
		GFLOAT			xPosition,
		GFLOAT			yPosition,
		GFLOAT			nWidth,
		GFLOAT			nHeight,
		CVariantDataRef		,//sSource,
		VXDraw::EFitments	,//eFitment, // = F_Fill,
		VXDraw::EAlignments	,//eAlign, // = A_Center,
		VXDraw::EVerticalAlignments ,//eVertAlign, // = V_Middle,
		bool		//bMirror // = false
		)
{
	bool		bResult = false;
	CColor		c;

	c.SetNonColor( true );
	FillColor( c );
	HaloColor( c );

	c.SetRGB( 0, 64, 0 );

	LineColor( c );
	LineWidth( 2 );

	bResult = Rectangle( xPosition, yPosition, nWidth, nHeight );

	return bResult;
}







}}

#else

long	dummyVDrawOpenGL;	// dummy symbol to suppress 'no public symbols' message


#endif	// OS_MSWIN

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
