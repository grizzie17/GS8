/*---------------------------------------------------------------------+\
|
|	TDrawOpenGL.h  --  brief description of what VDrawOpenGL.h is for
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
#ifndef _H_TDrawOpenGL
#define _H_TDrawOpenGL
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "VDraw.h"

#include "UOSIncludes.h"

//#include "fonts.h"
#include "TDictionaryIndexed.h"
#include "CVariantData.h"
#include "THash.h"

//#if defined( OPENGLES )
//#	include <GLES/gl.h>
//#	include <EGL/egl.h>
//#	pragma message( "building OpenGL ES")
//#else
//#	include <GL/gl.h>
//#	include <GL/glu.h>
//#	pragma message( "building OpenGL")
//#endif

//	GL includes must be included by Template instantiation file


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

/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/





class TDrawOpenGL : public VXDraw
{
//	class lifecycle  ----------------------------------------------------

	COM_LIFECYCLE( TDrawOpenGL );

public:
//	supported interfaces  -----------------------------------------------


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

	virtual void	FontInitialize( void );
	//bool	FontSelect( void );
	//bool	FontHaloSelect( void );
	//void	FontDestroy( void );

	GLint	GLintFromFloat( GFLOAT x );
	void	ResetPenBrush(void);

//	protected data  -----------------------------------------------------

	//HWND	m_hWnd;
	//HDC		m_hDC;
	//HGLRC	m_hRC;

	//RECT	m_tUpdateRect;
	CColor	m_clrNone;

	GLuint	m_nFboApplication;
	GLuint	m_nFboBackground;
	GLuint	m_nFboForeground;

	//THashTable< CCharString, CBitmapFont* >	m_tFontTable;
	//CBitmapFont*	m_pFont;

	TArray<XVert>	m_aVertexList;
	int				m_nGLMode;



private:
//	private types  ------------------------------------------------------

	typedef VXDraw	inherited;

//	private functions  --------------------------------------------------


//	private data  -------------------------------------------------------




//============================== Overrides ==============================

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

	//virtual bool	TextString
	//				(
	//				GFLOAT			xPosition,
	//				GFLOAT			yPosition,
	//				EAlignments		eAlign,
	//				EVerticalAlignments	eVertAlign,
	//				const char*		sString,
	//				long			nCount = -1
	//				);

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
void	TDrawOpenGL::vddsBegin
		(
		int	nMode
		)
{
	m_nGLMode = nMode;
	m_aVertexList.Truncate();
}

inline
void	TDrawOpenGL::vddsEnd
		(
		void
		)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, (GLvoid*)m_aVertexList.PointArray() );
	glDrawArrays(m_nGLMode, 0, (GLsizei)m_aVertexList.Length() );

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}

inline
void	TDrawOpenGL::vddsVertex
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
void	TDrawOpenGL::vddsVertexTransform
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
GLint	TDrawOpenGL::GLintFromFloat
		(
		GFLOAT	x
		)
{
	return GLint(x + (x < 0 ? -0.5 : 0.5 ));
}





NAMESPACE_COMMON_END


#endif // _H_TDrawOpenGL



