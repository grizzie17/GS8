/*---------------------------------------------------------------------+\
|
|	CDrawWinGLES.cpp  --  draw implementation for OpenGL
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
	20-Feb-2012			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDrawWinGLES.h"
#include "VPluginFactory.h"

#include "LogFile.h"
#include "UPlatform.h"

#if defined( OS_MSWIN )	// brackets whole file

#	include <math.h>
#	include <float.h>

#	include "UFile.h"

#	include "TDrawOpenGL-inl.h"


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
NAMESPACE_COMMON_BEGIN

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

PLUGIN_CREATE_FACTORY( CDrawWinGLES );



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
	//if ( m_nFontListBase )
	//	glDeleteLists( m_nFontListBase, 256 );
	m_nFontListBase = 0;
}

bool	CBitmapFont::CreateFont
		(
		HDC&		,//rDC,
		const char*	,//sFontname,
		int			//nFontHeight
		)
{
	bool	bResult = false;

	//if ( rDC  &&  sFontname )
	//{
	//	m_hDC = rDC;
	//	m_sFontname = sFontname;
	//	m_nFontHeight = nFontHeight;

	//	LOGFONTA	lf = {0};
	//	lf.lfHeight = nFontHeight;
	//	lf.lfWeight = FW_NORMAL;
	//	lf.lfCharSet = ANSI_CHARSET;
	//	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	//	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	//	lf.lfQuality = DEFAULT_QUALITY;
	//	lf.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
	//	m_sFontname.CopyTo( lf.lfFaceName, sizeof(lf.lfFaceName) );

	//	HANDLE	hFont = ::CreateFontIndirectA( &lf );
	//	if ( hFont )
	//	{
	//		HANDLE	hFontOld = ::SelectObject( m_hDC, hFont );
	//		if ( hFontOld )
	//		{
	//			m_nFontListBase = glGenLists( 256 );
	//			if ( m_nFontListBase )
	//			{
	//				BOOL	bf = wglUseFontBitmaps( m_hDC, 0, 255, m_nFontListBase );
	//				if ( bf )
	//				{
	//					::GetTextMetrics( m_hDC, &m_tTextMetric );
	//					GetCharABCWidths( m_hDC, 0, 255, m_aWidths );
	//					bResult = true;
	//				}
	//				::SelectObject( m_hDC, hFontOld );
	//			}
	//		}
	//	}
	//}

	return bResult;
}


bool	CBitmapFont::DrawTextString
		(
		int				,//xPosition,
		int				,//yPosition,
		IDraw::EAlignments	,//eAlign,
		IDraw::EVerticalAlignments	,//eVertAlign,
		const CColor&	,//clr,
		const char*		,//sString,
		long			//nCount	// = -1
		)
{
	//if ( sString )
	//{
	//	if ( nCount < 0 )
	//		nCount = long(::strlen( sString ));


	//	long	nWidth = 0;	// pixels
	//	for ( long i = 0; i < nCount; ++i )
	//	{
	//		int c = sString[i];
	//		nWidth += m_aWidths[c].abcA + m_aWidths[c].abcB + m_aWidths[c].abcC;
	//	}

	//	switch ( eAlign )
	//	{
	//	case IDraw::A_LEFT:
	//		// do nothing
	//		break;
	//	case IDraw::A_CENTER:
	//		xPosition -= nWidth / 2;
	//		break;
	//	case IDraw::A_RIGHT:
	//		xPosition -= nWidth;
	//		break;
	//	}
	//	switch ( eVertAlign )
	//	{
	//	case IDraw::V_BASELINE:
	//		break;
	//	case IDraw::V_ABSBOTTOM:
	//		yPosition += m_tTextMetric.tmDescent;
	//		break;
	//	case IDraw::V_TOP:
	//		yPosition -= m_tTextMetric.tmAscent;
	//		break;
	//	case IDraw::V_MIDDLE:
	//		yPosition -= m_tTextMetric.tmHeight / 2;
	//		break;
	//	}


	//	int			nBkMode = 0;
	//	COLORREF	nBkColor = ~0U;

	//	nBkMode = 0;
	//	nBkColor = ~0U;
	//	//GFLOAT	fHeight = TransformLength( m_fFontHeight );
	//	glColor3f(	(GLfloat)(clr.GetRed()/255.0),
	//				(GLfloat)(clr.GetGreen()/255.0),
	//				(GLfloat)(clr.GetBlue()/255.0));
	//	GLboolean bTexture2d = glIsEnabled( GL_TEXTURE_2D );
	//	if ( bTexture2d )
	//		glDisable( GL_TEXTURE_2D );
	//	GLboolean bDepth = glIsEnabled( GL_DEPTH_TEST );
	//	if ( bDepth )
	//		glDisable( GL_DEPTH_TEST );
	//	GLboolean bDMask;
	//	glGetBooleanv( GL_DEPTH_WRITEMASK, &bDMask );
	//	if ( bDMask )
	//		glDepthMask( GL_FALSE );
	//	glPushMatrix();
	//	glRasterPos2i( xPosition, yPosition );
	//	//glTranslatef( tx, ty, 0.0 );
	//	//glScalef( fHeight, fHeight, fHeight );
	//	glPushAttrib(GL_LIST_BIT);
	//	glListBase(m_nFontListBase);
	//	GLsizei len = GLsizei(nCount);
	//	glCallLists( len, GL_UNSIGNED_BYTE, sString );
	//	glPopAttrib();
	//	glPopMatrix();
	//	if ( bDMask )
	//		glDepthMask( GL_TRUE );
	//	if ( bDepth )
	//		glEnable( GL_DEPTH_TEST );
	//	if ( bTexture2d )
	//		glEnable( GL_TEXTURE_2D );
	//	//::ExtTextOutA( m_hdc, int(tx), int(ty), 0, NULL, sString, nCount, NULL );
	//}
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

 * CDrawWinGLES - constructor

\+---------------------------------------------------------------------*/
CDrawWinGLES::CDrawWinGLES
		(
		void
		)
		: inherited()
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_eglDisplay( 0 )
		, m_eglContext( 0 )
		, m_eglSurface( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );
}

CDrawWinGLES::CDrawWinGLES
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_eglDisplay( 0 )
		, m_eglContext( 0 )
		, m_eglSurface( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );
}


CDrawWinGLES::CDrawWinGLES
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_hWnd( 0 )
		, m_hDC( 0 )
		, m_eglDisplay( 0 )
		, m_eglContext( 0 )
		, m_eglSurface( 0 )
		, m_tFontTable()
		, m_pFont( 0 )
{
	FontInitialize();

	m_clrNone = CColor::ColorFromName( "background" );

}


/*---------------------------------------------------------------------+\

 * ~CDrawWinGLES - destructor

\+---------------------------------------------------------------------*/
CDrawWinGLES::~CDrawWinGLES
		(
		void
		)
{
	THashTableEnumerator<CCharString, CBitmapFont*>	e = m_tFontTable.GetEnumerator();

	while ( e.MoveNext() )
	{
		CBitmapFont**	pp = e.Current();
		if ( pp )
		{
			CBitmapFont*	p = *pp;
			if ( p )
				delete p;
		}
	}

	if ( m_eglDisplay )
	{
		eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(m_eglDisplay, m_eglContext);
		eglDestroySurface(m_eglDisplay, m_eglSurface);
		eglTerminate(m_eglDisplay);
	}


}


/*=====================================================================+\
||	 Interface functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * SetHDC -

\+---------------------------------------------------------------------*/
void	CDrawWinGLES::SetHDC
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

	m_eglDisplay = eglGetDisplay( m_hDC );
	if ( ! eglInitialize( m_eglDisplay, NULL, NULL ) )
	{
		LogPrint( "Unable to initialize EGL\n" );
	}

	EGLConfig	m_eglConfig[1];
	EGLint		nConfigs;
	EGLint		aEGLAttributes[] 
	= {
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
			EGL_NONE
	};
	EGLint		aEGLContextAttributes[] 
	= {
			EGL_CONTEXT_CLIENT_VERSION, 1,
			EGL_NONE
	};


	eglChooseConfig( m_eglDisplay, aEGLAttributes, m_eglConfig, 1, &nConfigs );

	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig[0], EGL_NO_CONTEXT, aEGLContextAttributes);
	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig[0], (NativeWindowType)m_hWnd, 0);

}

/*---------------------------------------------------------------------+\

 * UpdateRect -

\+---------------------------------------------------------------------*/
void	CDrawWinGLES::UpdateRect
		(
		LPRECT	pRect
		)
{
	m_tUpdateRect = *pRect;
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * FontInitialize -

\+---------------------------------------------------------------------*/
void	CDrawWinGLES::FontInitialize
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
//BEGIN_OVERRUN_WARNING
bool	CDrawWinGLES::FontSelect
		(
		void
		)
{
	bool	bResult = true;

	if ( ! m_pFont )
	{
		bResult = false;

		CBitmapFont**	ppFont;
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
//END_OVERRUN_WARNING

/*---------------------------------------------------------------------+\

 * FontDestroy -

\+---------------------------------------------------------------------*/
void	CDrawWinGLES::FontDestroy
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
void*	CDrawWinGLES::FindInternalInterface
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

 * Load - fetch configuration parameters

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool	bResult = inherited::Load( pConfig, pLib );
	if ( bResult )
	{
		eglThunk();
		//CCharString	sAppFolder = GetApplicationFolder();
		//char		sPath[512];

		//PathBuild( sPath, sizeof(sPath), sAppFolder, "libGLESv1_CM.dll" );
		//m_hGlesDLL = DLLOpen( sPath );
		//if ( ! m_hGlesDLL )
		//{
		//	char*	s = DLLErrorString();
		//	LogPrint( "Problem loading libGLESv1_CM.dll - %s\n", s );
		//}

		//PathBuild( sPath, sizeof(sPath), sAppFolder, "libEGL.dll" );
		//m_hEglDLL = DLLOpen( sPath );
		//if ( ! m_hEglDLL )
		//{
		//	char*	s = DLLErrorString();
		//	LogPrint( "Problem loading libEGL.dll - %s\n", s );
		//}
	}
	return bResult;
}




/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::begin
		(
		void
		)
{
	bool	bResult = false;

	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);

	bResult = inherited::begin();


	return bResult;
}

/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::end
		(
		void
		)
{
	//glDisable( GL_TEXTURE_2D );
	ResetPenBrush();


	eglSwapBuffers( m_eglDisplay, m_eglSurface );

	//clear the working buffer immediately following a buffer swap
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);


	return inherited::end();
}


/*---------------------------------------------------------------------+\

 * InitialMatrix -

\+---------------------------------------------------------------------*/
CMatrix3x3  CDrawWinGLES::InitialMatrix( void )
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

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::SupportsContext
		(
		void
		)
{
	return inherited::SupportsContext();
}



/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::FontParams
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
void	CDrawWinGLES::ResetPenBrush
		(
		void
		)
{
//	DestroyBrush();
//	DestroyPen();
	FontDestroy();
}




/*---------------------------------------------------------------------+\

 * EndPolygon -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::EndPolygon
		(
		void
		)
{
	if(SetFillParms())
	{
		m_nGLMode = GL_TRIANGLE_STRIP;		// NEEDS_WORK: completely reimplement polygon stuff
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

 * TextString -

\+---------------------------------------------------------------------*/
bool	CDrawWinGLES::TextString
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

















NAMESPACE_COMMON_END







#else

long	dummyCDrawWinGLES;	// dummy symbol to suppress 'no public symbols' message


#endif	// OS_MSWIN

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

