/*---------------------------------------------------------------------+\
|
|	CDrawWinGLES.h  --  brief description of what CDrawWinGLES.h is for
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
	20-Feb-2012			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawWinGLES_Common
#define _H_CDrawWinGLES_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDraw.h"

#include "UOSIncludes.h"
#if defined( OS_WIN32 )	// brackets entire file

#	include <EGL/egl.h>
#	include <GLES/gl.h>

#	ifndef OPENGLES
#		define OPENGLES
#	endif

#	include "eglThunk.h"

#	define	glOrtho	glOrthof
#	define	TDrawOpenGL	CDrawOpenGLESBase
#	include "TDrawOpenGL.h"

#	include "TDictionaryIndexed.h"
#	include "IDrawWin32.h"
#	include "CVariantData.h"
#	include "THash.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/


#define NEAR_Z        1000.0
#define FAR_Z        -1000.0


//These defines are carried over from the SM501 OpenGL implementation
#define Z_LEVEL_1 3


//#define	FONT_GLUT	1
//#define FONT_FTGL	1



/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CDrawWinGLES*			CDrawWinGLESPtr;
typedef class CDrawWinGLES&			CDrawWinGLESRef;
typedef const class CDrawWinGLES&	ConstCDrawWinGLESRef;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/


class CBitmapFont
{
public:
	CBitmapFont();
	CBitmapFont( const CBitmapFont& r );
	~CBitmapFont();

	bool	CreateFont( HDC& rDC, const char* sFontname, int nFontHeight );
	bool	DrawTextString
			(
			int				xPosition,
			int				yPosition,
			IDraw::EAlignments		eAlign,
			IDraw::EVerticalAlignments	eVertAlign,
			const CColor&	clr,
			const char*		sString,
			long			nCount = -1
			);

	bool	operator == ( const CBitmapFont& r ) const;
	unsigned long	GetHash() const;

private:
	CCharString	m_sFontname;
	int			m_nFontHeight;
	HDC			m_hDC;
	TEXTMETRIC	m_tTextMetric;
	GLuint		m_nFontListBase;
	ABC			m_aWidths[256];
};

template <>
inline
unsigned long
		THashValueFromKey<CBitmapFont>
		(
		const CBitmapFont&	key
		)
{
	return key.GetHash();
}




class CDrawWinGLES : public TDrawOpenGL,
				implements_ IDrawWin32
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawWinGLES );

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

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------


protected:
//	protected types  ----------------------------------------------------


//	protected functions  ------------------------------------------------

	void	FontInitialize( void );
	bool	FontSelect( void );
	bool	FontHaloSelect( void );
	void	FontDestroy( void );


//	protected data  -----------------------------------------------------

	HWND		m_hWnd;
	HDC			m_hDC;
	EGLDisplay	m_eglDisplay;
	EGLContext	m_eglContext;
	EGLSurface	m_eglSurface;

	RECT		m_tUpdateRect;
	CColor		m_clrNone;

	GLuint		m_nFboApplication;
	GLuint		m_nFboBackground;
	GLuint		m_nFboForeground;

	THashTable< CCharString, CBitmapFont* >	m_tFontTable;
	CBitmapFont*	m_pFont;

	ULibraryHdl	m_hEglDLL;
	ULibraryHdl	m_hGlesDLL;


private:
//	private types  ------------------------------------------------------

	typedef TDrawOpenGL	inherited;

//	private functions  --------------------------------------------------

	//GLint	GLintFromFloat( GFLOAT x );
	void	ResetPenBrush(void);

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


	virtual CMatrix3x3
			InitialMatrix( void );

	//	VDraw
public:

	virtual bool	SupportsContext( void );




	virtual bool	FontParams( const char* sFontName, GFLOAT fFontHeight );

	// --- Geometry graphics ---

	virtual bool	EndPolygon
					(
					void
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


};

NAMESPACE_COMMON_END
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








#endif	// GL_OPENGL


#endif /* _H_CDrawWinGLES */

