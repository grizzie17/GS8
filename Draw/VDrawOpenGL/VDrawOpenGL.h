/*---------------------------------------------------------------------+\
|
|	VDrawOpenGL.h  --  brief description of what VDrawOpenGL.h is for
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
#ifndef _H_VDrawOpenGL_Common
#define _H_VDrawOpenGL_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDraw.h"

#include "UOSIncludes.h"
#if defined( OS_MSWIN )	// brackets entire file
//#include "fonts.h"
#include "TDictionaryIndexed.h"
#include "IDrawWin32.h"
#include "CVariantData.h"
#include "CColor.h"
#include "THash.h"

#	include <GL/gl.h>
#	include <GL/glu.h>

//#	include <ft2build.h>
//#	include <FTGL/ftgl.h>


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

typedef class VDrawOpenGL*			VDrawOpenGLPtr;
typedef class VDrawOpenGL&			VDrawOpenGLRef;
typedef const class VDrawOpenGL&	ConstVDrawOpenGLRef;
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
	GLuint		m_nFontListBase;
	HDC			m_hDC;
	TEXTMETRIC	m_tTextMetric;
	ABC			m_aWidths[256];
};

//template <>
inline
index_t
		THashValueFromKey //<CBitmapFont>
		(
		const CBitmapFont&	key
		)
{
	return key.GetHash();
}




class VDrawOpenGL : public VXDraw,
				implements_ IDrawWin32
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( VDrawOpenGL );

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

	typedef struct XVert
	{
		GLfloat	x;
		GLfloat y;
		GLfloat z;
	} XVert;



//	protected functions  ------------------------------------------------

	void	vddsBegin( int nMode );
	void	vddsEnd( void );
	void	vddsVertex( GFLOAT x, GFLOAT y );
	void	vddsVertexTransform( GFLOAT x, GFLOAT y );
	bool	SetFillParms();
	bool	SetLineParms();

	void	FontInitialize( void );
	bool	FontSelect( void );
	bool	FontHaloSelect( void );
	void	FontDestroy( void );


//	protected data  -----------------------------------------------------

	HWND	m_hWnd;
	HDC		m_hDC;
	HGLRC	m_hRC;

	RECT	m_tUpdateRect;
	CColor	m_clrNone;

	GLuint	m_nFboApplication;
	GLuint	m_nFboBackground;
	GLuint	m_nFboForeground;

	THashTable< CCharString, CBitmapFont* >	m_tFontTable;
	CBitmapFont*	m_pFont;

	TArray<XVert>	m_aVertexList;
	int				m_nGLMode;


private:
//	private types  ------------------------------------------------------

	typedef VXDraw	inherited;

//	private functions  --------------------------------------------------

	GLint	GLintFromFloat( GFLOAT x );
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
	virtual bool	LineColor( Yogi::Core::ConstCColorRef rColor );
	virtual bool	FillColor( Yogi::Core::ConstCColorRef rColor );
	virtual bool	HaloColor( Yogi::Core::ConstCColorRef rColor );

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

	virtual bool	BeginPolyline
					(
					void
					);

	virtual bool	EndPolyline
					(
					void
					);

	virtual bool	BeginPolygon
					(
					void
					);

	virtual bool	EndPolygon
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


protected:
	virtual void	MergeCropStack();
	virtual bool	PolypointNoTmx
					(
					GFLOAT	x,
					GFLOAT	y
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

inline
void	VDrawOpenGL::vddsBegin
		(
		int	nMode
		)
{
	m_nGLMode = nMode;
	m_aVertexList.Truncate();
}

inline
void	VDrawOpenGL::vddsEnd
		(
		void
		)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)m_aVertexList.PointArray() );
	glDrawArrays((GLenum)m_nGLMode, 0, (GLsizei)m_aVertexList.Length() );

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}

inline
void	VDrawOpenGL::vddsVertex
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	XVert*	p = m_aVertexList.AppendArray();
	if ( p )
	{
		p->x = x;
		p->y = y;
		p->z = 0.0f;
	}
}

inline
void	VDrawOpenGL::vddsVertexTransform
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
GLint	VDrawOpenGL::GLintFromFloat
		(
		GFLOAT	x
		)
{
	return GLint(x + (x < 0 ? -0.5 : 0.5 ));
}





}}



#endif	// GL_OPENGL


#endif /* _H_VDrawOpenGL */
