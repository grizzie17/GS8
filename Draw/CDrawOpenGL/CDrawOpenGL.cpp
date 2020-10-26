/*---------------------------------------------------------------------+\
|
|	CDrawOpenGL.cpp  --  draw implementation for OpenGL
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
	25-Jun-2013			J.Griswold
		added support for fontconfig that allows the system to find
		fonts instead of being hardcoded paths.
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
//#include "stdafx.h"
#include "UMachine.h"

#if defined( GL_OPENGL )	// brackets whole file

#include "CDrawOpenGL.h"
#include "VPluginFactory.h"
#include "LogFile.h"


#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <float.h>

#include <ft2build.h>
#include <FTGL/ftgl.h>
#include <fontconfig/fontconfig.h>

//#	include "SOIL.h"
//#	include "image_helper.h"
//#	include "stb_image_aug.h"

#	include "TDrawOpenGL-inl.h"
#	include "UFile.h"

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


#ifdef GL_OPENGL_SM501
//extern BitmapFontRec font9x15;
//extern BitmapFontRec font8x13;
//extern BitmapFontRec fontTimesRoman24;
//extern BitmapFontRec fontTimesRoman10;
//extern BitmapFontRec fontHelvetica10;
//extern BitmapFontRec fontHelvetica12;
//extern BitmapFontRec fontHelvetica18;
//
//#define GLUT_BITMAP_9_BY_15 (&font9x15)
//#define GLUT_BITMAP_8_BY_13 (&font8x13)
//#define GLUT_BITMAP_TIMES_ROMAN_24 (&fontTimesRoman24)
//#define GLUT_BITMAP_TIMES_ROMAN_10 (&fontTimesRoman10)
//#define GLUT_BITMAP_HELVETICA_10 (&fontHelvetica10)
//#define GLUT_BITMAP_HELVETICA_12 (&fontHelvetica12)
//#define GLUT_BITMAP_HELVETICA_18 (&fontHelvetica18)

//#define DEFAULT_ALPHA_VALUE 15 //valid values: 0,1,2,3

#endif //GL_OPENGL_SM501
#define DEFAULT_LINE_WIDTH 1


namespace Yogi { namespace Common {
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

PLUGIN_CREATE_FACTORY( CDrawOpenGL );


/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * CDrawOpenGL - constructor

\+---------------------------------------------------------------------*/
CDrawOpenGL::CDrawOpenGL
		(
		void
		)
		: inherited()
		, m_pFontConfig( 0 )
#ifdef FONT_FTGL
		, m_pxFont( 0 )
		, m_pxFontOld( 0 )
		, m_pxFontCur( 0 )
#endif
{
	FontInitialize();
	m_aVertexList.SetBlockSize(20);
	m_aVertexList.PointItem(90);
	m_aVertexList.Truncate();
}

CDrawOpenGL::CDrawOpenGL
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_pFontConfig( 0 )
#ifdef FONT_FTGL
		, m_pxFont( 0 )
		, m_pxFontOld( 0 )
		, m_pxFontCur( 0 )
#endif
{
	FontInitialize();
	m_aVertexList.SetBlockSize(20);
	m_aVertexList.PointItem(90);
	m_aVertexList.Truncate();
}

CDrawOpenGL::CDrawOpenGL
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_pFontConfig( 0 )
#ifdef FONT_FTGL
		, m_pxFont( 0 )
		, m_pxFontOld( 0 )
		, m_pxFontCur( 0 )
#endif
{
	FontInitialize();
	m_aVertexList.SetBlockSize(20);
	m_aVertexList.PointItem(90);
	m_aVertexList.Truncate();
}


/*---------------------------------------------------------------------+\

 * ~CDrawOpenGL - destructor

\+---------------------------------------------------------------------*/
CDrawOpenGL::~CDrawOpenGL
		(
		void
		)
{
	if ( m_pFontConfig )
		FcConfigDestroy( m_pFontConfig );
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * ActivateStyles -

\+---------------------------------------------------------------------*/
#if 0
const unsigned int	kBitsAll	= 0xFF;
const unsigned char a2bits[] = { 0x00, 0x66, 0x99, 0xFF };
#define DIVRND(x,y) (((((x)<<1)/(y))+1)>>1)
#define RGB2BSIDX(r,g,b) DIVRND(b,51)+DIVRND(g,51)*6+DIVRND(r,51)*36
inline unsigned int VDDSINDEX2( unsigned int x )
{
	if ( kBitsAll == x )
	{
		return sizeof(a2bits) - 1;
	}
	else
	{
		unsigned int y = x * sizeof(a2bits) / kBitsAll;
		if ( sizeof(a2bits) <= y )
			y = sizeof(a2bits) - 1;
		return y;
	}
}
inline unsigned int	VDDSEMULATE2( unsigned int x )
{
	return a2bits[ VDDSINDEX2( x ) ];
}
inline
unsigned int
		VDDSColor
		(
		const CColor& c
		)
{
	unsigned int	rv = VDDSEMULATE2( c.GetRed() );
	unsigned int	gv = VDDSEMULATE2( c.GetGreen() );
	unsigned int	bv = VDDSEMULATE2( c.GetBlue() );
	return RGB2BSIDX( rv, gv, bv );
}
bool	CDrawOpenGL::ActivateStyles
		(
		void
		)
{
	//COLORDATA	cl = VDDSColor(m_tLineColor);
	//COLORDATA	cf = VDDSColor(m_tFillColor);

	if ( m_tLineColor.IsNonColor()  &&  m_tFillColor.IsNonColor() )
		glColor3f(	(float)m_tLineColor.GetRed()/255.0,
					(float)m_tLineColor.GetGreen()/255.0,
					(float)m_tLineColor.GetBlue()/255.0);

		//glIndex( cl, NO_OPAQUE );
	else if ( ! m_tFillColor.IsNonColor() )
		glColor3f(	(float)m_tFillColor.GetRed()/255.0,
					(float)m_tFillColor.GetGreen()/255.0,
					(float)m_tFillColor.GetBlue()/255.0);
		//glIndex( cf, FULL_OPAQUE);
	else
		glColor3f(	(float)m_tLineColor.GetRed()/255.0,
					(float)m_tLineColor.GetGreen()/255.0,
					(float)m_tLineColor.GetBlue()/255.0);

		//glIndex( cl, FULL_OPAQUE );

	m_nLineWidth = (m_nLineWidth>0)?m_nLineWidth:DEFAULT_LINE_WIDTH;
	GFLOAT	fWidth = TransformLength( m_nLineWidth );
	glLineWidth( fWidth );
	return true;
}
#endif






/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * FontInitialize -

\+---------------------------------------------------------------------*/
void	CDrawOpenGL::FontInitialize()
{
#if 1
	if ( !FindFontByName( m_sFontName, sizeof( m_sFontName ), "sans-serif" ) )
		LOCAL_PRINT( "Unable to find 'sansserif' font" );

	if ( !FindFontByName( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "sansserif" ) )
		LOCAL_PRINT( "Unable to find 'sansserif' font" );

	if ( !FindFontByName( m_sFontSerif, sizeof( m_sFontSerif ), "serif" ) )
		LOCAL_PRINT( "Unable to find 'serif' font" );

	if ( !FindFontByName( m_sFontMonospace, sizeof( m_sFontMonospace ), "monospace" ) )
		LOCAL_PRINT( "Unable to find 'monospace' font" );
//#else
//	if ( FolderExists( "/usr/share/fonts/truetype/freefont" ) )
//	{
//		::strcpy_s( m_sFontName, sizeof( m_sFontName ), "/usr/share/fonts/truetype/freefont/FreeSans.ttf" );
//		::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "/usr/share/fonts/truetype/freefont/FreeSans.ttf" );
//		::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "/usr/share/fonts/truetype/freefont/FreeSerif.ttf" );
//		::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "/usr/share/fonts/truetype/freefont/FreeMono.ttf" );
//	}
//	else if ( FolderExists( "/usr/share/fonts/dejavu" ) )
//	{
//		::strcpy_s( m_sFontName, sizeof( m_sFontName ), "/usr/share/fonts/dejavu/DejaVuSans.ttf" );
//		::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "/usr/share/fonts/dejavu/DejaVuSans.ttf" );
//		::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "/usr/share/fonts/dejavu/DejaVuSerif.ttf" );
//		::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "/usr/share/fonts/dejavu/DejaVuSansMono.ttf" );
//	}
//	else if ( FolderExists( "/usr/share/fonts/dejavu-lgc" ) )
//	{
//		::strcpy_s( m_sFontName, sizeof( m_sFontName ), "/usr/share/fonts/dejavu-lgc/DejaVuLGCSans.ttf" );
//		::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "/usr/share/fonts/dejavu-lgc/DejaVuLGCSans.ttf" );
//		::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "/usr/share/fonts/dejavu-lgc/DejaVuLGCSerif.ttf" );
//		::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "/usr/share/fonts/dejavu-lgc/DejaVuLGCSansMono.ttf" );
//	}
#endif


	m_pxFont = 0;
	m_pxFontCur = 0;
	m_pxFontOld = 0;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * FindFontByName -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::FindFontByName
		(
		char*	sFile,
		size_t	nFile,
		const char* sName
		)
{
	bool	bResult = false;
	if ( ! m_pFontConfig )
	{
		if ( ! FcInit() )
			return false;
		m_pFontConfig = FcInitLoadConfigAndFonts();
	}

	// configure the search pattern,
	// assume "name" is a std::string with the desired font name in it
	FcPattern* pat = FcNameParse(static_cast<const FcChar8*>( (const unsigned char*)sName ));
	FcConfigSubstitute(m_pFontConfig, pat, FcMatchPattern);
	FcDefaultSubstitute(pat);

	FcResult	eResult;
	// find the font
	FcPattern* font = FcFontMatch(m_pFontConfig, pat, &eResult);
	if (font)
	{
		FcChar8* file = NULL;
		if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
		{
			// save the file to another std::string
			::strcpy_s( sFile, nFile, (const char*)file );
			bResult = true;
		}
		FcPatternDestroy(font);
	}

	FcPatternDestroy(pat);

	return bResult;
}

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/







/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::begin
		(
		void
		)
{
	bool		bResult = inherited::begin();
//	GLenum		err;
//	GLdouble	half_width  = (GLdouble) (m_nWindowWidth >> 1);
//	GLdouble	half_height = (GLdouble) (m_nWindowHeight >> 1);
//
//	glClearColor(	(GLfloat)(m_tBackgroundColor.GetRed()/255.0),
//					(GLfloat)(m_tBackgroundColor.GetGreen()/255.0),
//					(GLfloat)(m_tBackgroundColor.GetBlue()/255.0),
//					1.0f);
//	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//	glViewport( 0, 0, m_nWindowWidth, m_nWindowHeight );
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho( -half_width, half_width, -half_height, half_height, NEAR_Z, FAR_Z);
//
//	glMatrixMode( GL_MODELVIEW);
//
//	/* check for errors, really should be a while loop since errors can be stacked. */
//
//	if ((err = glGetError()) != GL_NO_ERROR)
//	{
//		LogPrint("Error during ReshapeCB : %d\n", err);
//	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::end
		(
		void
		)
{
	//glDisable( GL_TEXTURE_2D );
	glFlush();
	glutSwapBuffers();

	//clear the working buffer immediately following a buffer swap
	//glClear(GL_COLOR_BUFFER_BIT);

	return inherited::end();
}

/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	bool	bResult = inherited::FontParams( sFontName, fFontHeight );
	if ( bResult )
	{
		if ( m_sFontName[0] != '/' )
		{
			if ( ! FindFontByName( m_sFontName, sizeof(m_sFontName), sFontName ) )
				::strcpy_s( m_sFontName, sizeof(m_sFontName), m_sFontSansSerif );
		}
		ResetPenBrush();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * ResetPenBrush -

\+---------------------------------------------------------------------*/
void	CDrawOpenGL::ResetPenBrush
		(
		void
		)
{
// 	DestroyBrush();
// 	DestroyPen();
	DestroyFont();
}




/*---------------------------------------------------------------------+\

 * BeginPolygon -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::BeginPolygon
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
bool	CDrawOpenGL::EndPolygon
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

 * TextString -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::TextString
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		VDraw::EAlignments	eAlign,
		VDraw::EVerticalAlignments	eVertAlign,
		const char*		sString,
		long			nCount
		)
{

	/* Draw the string data */
	GFLOAT x, y;
	SelectFont();

	if ( nCount < 0 )
		nCount = strlen(sString);
	int iStrWidth = 0;
	//GFLOAT FontHeight;
//#ifdef FONT_GLUT
//	const char* pChar = sString;
//	const char*	pEnd = pChar + nCount;
//	BitmapFontPtr fontinfo = (BitmapFontPtr) m_hFontCur->FontRec;
//#ifdef GL_OPENGL_SM501
//	int c;
//	const BitmapCharRec *ch;
//#endif
//#endif

	TransformPoint(x, y, xPosition, yPosition);

#ifdef FONT_FTGL

	FTBBox	box;
	FTPoint	pt1;
	FTPoint	pt2;

	box = m_pxFont->BBox( sString, nCount );
	pt1 = box.Upper();
	pt2 = box.Lower();

	iStrWidth = int(fabsf(pt1.Xf() - pt2.Xf()));
	//FontHeight = m_pxFont->FaceSize();
	GFLOAT	nAsc = m_pxFont->Ascender();
	GFLOAT	nDesc = m_pxFont->Descender();
	//FontHeight = fabsf(pt2.Yf() - pt2.Yf());

//#else
//	FontHeight = m_hFontCur->FontHeight;
//
//#if ! defined( GL_OPENGL_SM501 )
//	//if using standard OpenGL, there is a glutBitmapWidth call than may be used
//	while(pChar < pEnd)
//	{
//		iStrWidth += glutBitmapWidth((void*)fontinfo, *pChar);
//		pChar++;
//	}
//
//#else
//
//	//add up the total string width in pixels by summing the advance of each character
//	while(pChar < pEnd)
//	{
//		c = *pChar;
//		ch = fontinfo->ch[c - fontinfo->first];
//		if (ch)
//		{
//			iStrWidth += ch->advance;
//		}
//		pChar++;
//	}
//#endif
#endif
	//calculate the horizontal offset
	switch ( eAlign )
	{
	case A_LEFT:
		break;
	case A_CENTER:
		x -= ((float)iStrWidth / 2.0);
		break;
	case A_RIGHT:
		x -= (float)iStrWidth;
		break;
	}



	switch ( eVertAlign )
	{//calculate the vertical offset
	case V_MIDDLE:
		y -= nAsc / 2.0;
		break;
	case V_CAPLINE:
	case V_TOP:
		y -= nAsc;
		break;
	case V_ABSBOTTOM:
		y -= nDesc;		// descender is negative
		break;
	case V_BASELINE:
		// nothing needed
		break;
	default:
		break;
	}

#ifdef FONT_FTGL
	//y += m_pxFont->Descender();
#endif


   glRasterPos3i( static_cast<GLint>(x), static_cast<GLint>(y),
					Z_LEVEL_1 );
#ifdef FONT_GLUT
	pChar = sString;
	while ( pChar < pEnd )
	{
		glutBitmapCharacter( m_hFontCur->FontRec, *pChar);
		++pChar;
	}
#else
	m_pxFont->Render( sString, nCount );
#endif

	return true;
}


/*---------------------------------------------------------------------+\

 * SelectFont -

\+---------------------------------------------------------------------*/
bool	CDrawOpenGL::SelectFont
		(
		void
		)
{
#ifdef FONT_FTGL
	if ( ! m_pxFont )
	{
		m_pxFont = new FTGLPixmapFont( m_sFontName );
		if ( ! m_pxFont )
			return false;
		if ( m_pxFont->Error())
		{
			delete m_pxFont;
			m_pxFont = 0;
			return false;
		}

		m_pxFont->FaceSize( (unsigned int)TransformLength(m_fFontHeight));
	}
//#else
//	if (m_hFontCur)
//	{
//		m_hFontOld = m_hFontCur;
//	}
//
//
//
//	if ( ! m_hFont )
//	{
//
//		m_hFont = BestFont();
//		if ( ! m_hFont )
//			return false;
//		m_hFontCur = m_hFont;
//	}
#endif
	SetLineParms();
	//ActivateStyles();
	return true;
}

/*---------------------------------------------------------------------+\

 * DestroyFont -

\+---------------------------------------------------------------------*/
void	CDrawOpenGL::DestroyFont
		(
		void
		)
{
#ifdef FONT_FTGL
	if ( m_pxFont )
	{
		delete m_pxFont;
		m_pxFont = 0;
	}
//#else
//	if ( m_hFont )
//	{
//		if ( m_hFontOld )
//		{
//			m_hFontCur = m_hFontOld;
//			m_hFontOld = NULL;
//		}
//		m_hFont = NULL;
//	}
//
#endif
}

//FontData*
//		CDrawOpenGL::BestFont
//		(
//		void
//		)
//{
//	CCharString     sDefaultFont = "sans-serif";
//	GFLOAT		fDefaultHeight = GFLOAT_10; //use smallest point size, match code will
//						//always increase the point size
//	GFLOAT		fCloseHeight = GFLOAT_0;
//
//	//look for the font by name
//	CCharString     sKey = m_sFontName;
//	sKey.Append(m_fFontHeight);
//
//	FontData**	pFont = m_pFonts.Find(sKey);
//
//	if(pFont)
//	{//found the font by name
//		return(*pFont);
//	}
//
//	//set the default font in case we can't find match below
//	//because font height smaller than all font heights
//	sKey.ClearString();
//	sKey = sDefaultFont;
//	sKey.Append(fDefaultHeight);
//	pFont = m_pFonts.Find(sKey);
//
//	FontData**	p = m_pFonts.PointArray();
//
//	if ( p )
//	{//didn't find font by name, look for default font type with closest point size
//		FontData**	pEnd = p + m_pFonts.Length();
//
//		while ( p < pEnd )
//		{
//			if ( *p )
//			{
//				FontData* pFd = *p;
//				CCharString sStr = pFd->FontType;
//
//				if((!sStr.Compare(sDefaultFont))  && (pFd->FontHeight <= m_fFontHeight))
//				{//possible font match candidate
//					if(pFd->FontHeight > fCloseHeight)
//					{//find the biggest point size closest to requested
//						fCloseHeight = pFd->FontHeight;
//						*pFont = pFd;
//					}
//				}
//
//			}
//			++p;
//		}
//	}
//	return(*pFont);
//}
//









/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
#if 1
bool	CDrawOpenGL::ImagePreloaded
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
		//ActivateStyles();

		//nTexture = SOIL_load_OGL_texture( sSource, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_POWER_OF_TWO
		//	|	SOIL_FLAG_MIPMAPS
		//	|	SOIL_FLAG_MULTIPLY_ALPHA
		//	|	SOIL_FLAG_COMPRESS_TO_DXT
		//	|	SOIL_FLAG_DDS_LOAD_DIRECT
		//	|	SOIL_FLAG_NTSC_SAFE_RGB
		//	//|	SOIL_FLAG_INVERT_Y
		//	);
		//if ( nTexture < 1 )
		//	break;

		glColor3f(	(float)1.0, (float)1.0, (float)1.0);

		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, pImage->nTexture );

		GFLOAT	x;
		GFLOAT	y;
		GFLOAT	w;
		GFLOAT	h;
		//GLfloat	tw;
		//GLfloat	th;
		//int		nMipLvl = 0;
		//glGetTexLevelParameterfv( GL_TEXTURE_2D, nMipLvl, GL_TEXTURE_WIDTH, &tw );
		//glGetTexLevelParameterfv( GL_TEXTURE_2D, nMipLvl, GL_TEXTURE_HEIGHT, &th );

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
#endif // 0



}}

#else

long	dummyCDrawOpenGL;	// dummy symbol to surpress 'no public symbols' message


#endif	// GL_OPENGL

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
