/*---------------------------------------------------------------------+\
|
|	CDrawWinGL.h  --  brief description of what CDrawWinGL.h is for
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
	15-Feb-2012			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CDrawWinGL_Common
#define _H_CDrawWinGL_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDraw.h"

#include "UOSIncludes.h"
#if defined( OS_MSWIN )	// brackets entire file

#include "TDictionaryIndexed.h"
#include "IDrawWin32.h"
#include "CVariantData.h"
#include "THash.h"

#	include <GL/gl.h>
#	include <GL/glu.h>


namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define NEAR_Z        1000.0
#define FAR_Z        -1000.0

//These defines are carried over from the SM501 OpenGL implementation
#define Z_LEVEL_1 3

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef class CDrawWinGL*			CDrawWinGLPtr;
typedef class CDrawWinGL&			CDrawWinGLRef;
typedef const class CDrawWinGL&	ConstCDrawWinGLRef;

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
index_t	THashValueFromKey<CBitmapFont>
		(
		const CBitmapFont&	key
		)
{
	return key.GetHash();
}




class CDrawWinGL : public VXDraw,
				implements_ IDrawWin32
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( CDrawWinGL );

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

	struct XTexImage : public XImage
	{
		XTexImage() : XImage(), nmW(0), nmH(0), nTexture( 0 ) {};

		long		nmW;
		long		nmH;
		GLuint		nTexture;

	protected:
		virtual ~XTexImage() {};
	};



//	protected functions  ------------------------------------------------

	bool	ActivateStyles( void );
	void	vddsBegin( GLenum nMode );
	void	vddsEnd( void );
	void	vddsVertex( GFLOAT x, GFLOAT y );
	void	vddsVertexTransform( GFLOAT x, GFLOAT y );
	bool	SetFillParms();
	bool	SetLineParms();

	void	FontInitialize( void );
	bool	FontSelect( void );
	bool	FontHaloSelect( void );
	void	FontDestroy( void );

	bool	PieBase(
                GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle,
		GLenum mode
		);

	bool	CircleBase
		(
		GFLOAT	cx,
		GFLOAT	cy,
		GFLOAT	r,
		GLenum mode
		);

	bool	EndPolygonBase
		(
		GLenum mode
		);

//	protected data  -----------------------------------------------------

	HWND	m_hWnd;
	HDC		m_hDC;
	HGLRC	m_hRC;

	RECT	m_tUpdateRect;
	CColor		m_clrNone;

	GLuint	m_nFboApplication;
	GLuint	m_nFboBackground;
	GLuint	m_nFboForeground;

	THashTable< CCharString, CBitmapFont* >	m_tFontTable;

	CBitmapFont*	m_pFont;

	//HFONT		m_hFont;
	//HFONT		m_hFontHalo;
	//TEXTMETRIC	m_tTextMetric;
	//HGDIOBJ		m_hFontOld;
	//GLuint		m_nFontListBase;
	//GLYPHMETRICSFLOAT	m_aGlyphMetrics[256];
	//ABC			m_aWidths[256];

private:
//	private types  ------------------------------------------------------

	typedef VXDraw	inherited;

//	private functions  --------------------------------------------------

	GLint	GLintFromFloat( GFLOAT x );
	void	ResetPenBrush(void);

//	private data  -------------------------------------------------------


//#define COLOR_LUT_LENGTH (256)
//#define COLOR_LUT_NCOLORS (3)
//	int m_clut[COLOR_LUT_LENGTH][COLOR_LUT_NCOLORS];


//============================== Overrides ==============================
	//	VSupports
protected:

	virtual
	void*	FindInternalInterface
			(
			ConstIXIDRef	rIID
			);

	//	VDrawTmx
public:
	virtual bool	begin( void );
	virtual bool	end( void );


	virtual CMatrix3x3
			InitialMatrix( void );

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

	virtual bool	HorizontalLine
					(
					GFLOAT	xPos,
					GFLOAT	yPos,
					GFLOAT	nWidth
					);

	virtual bool	VerticalLine
					(
					GFLOAT	xPos,
					GFLOAT	yPos,
					GFLOAT	nWidth
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

protected:
	virtual void	MergeCropStack();

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
void	CDrawWinGL::vddsBegin
		(
		GLenum	nMode
		)
{
	glBegin( nMode );
}

inline
void	CDrawWinGL::vddsEnd
		(
		void
		)
{
	glEnd();
}

inline
void	CDrawWinGL::vddsVertex
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	glVertex3i(GLintFromFloat(x), GLintFromFloat(y), Z_LEVEL_1);
}

inline
void	CDrawWinGL::vddsVertexTransform
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	GFLOAT	tx;
	GFLOAT	ty;

	TransformPoint( tx, ty, x, y );
	vddsVertex( tx, ty );
}

inline
GLint	CDrawWinGL::GLintFromFloat
		(
		GFLOAT	x
		)
{
	return GLint(x + (x < 0 ? -0.5 : 0.5 ));
}





}}



#endif	// GL_OPENGL


#endif /* _H_CDrawWinGL */
