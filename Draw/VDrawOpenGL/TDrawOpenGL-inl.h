/*---------------------------------------------------------------------+\
|
|	TDrawOpenGL.cpp  --  draw implementation for OpenGL
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
		Kludge for 1024x768
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "TDrawOpenGL.h"

#include "UMachine.h"
#include "LogFile.h"



#	include <math.h>
#	include <float.h>

#	include "SOIL.h"

namespace Yogi { namespace Common {

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
#define DEFAULT_LINE_WIDTH 1

#define FONT_MAXNUMGLYPHS	255

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



/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/



/*---------------------------------------------------------------------+\

 * TDrawOpenGL - constructor

\+---------------------------------------------------------------------*/
TDrawOpenGL::TDrawOpenGL
		(
		void
		)
		: inherited()
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = Yogi::Core::CColor::ColorFromName( "background" );
}


TDrawOpenGL::TDrawOpenGL
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = Yogi::Core::CColor::ColorFromName( "background" );
}



TDrawOpenGL::TDrawOpenGL
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_aVertexList()
{
	FontInitialize();

	m_clrNone = Yogi::Core::CColor::ColorFromName( "background" );

}


/*---------------------------------------------------------------------+\

 * ~TDrawOpenGL - destructor

\+---------------------------------------------------------------------*/
TDrawOpenGL::~TDrawOpenGL
		(
		void
		)
{

}


/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * FontInitialize -

\+---------------------------------------------------------------------*/
void	TDrawOpenGL::FontInitialize
		(
		void
		)
{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );
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

 * begin -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::begin
		(
		void
		)
{
	bool	bResult = inherited::begin();
	if ( bResult )
	{

		GLenum	err;
		GLfloat	half_width  = (GLfloat)m_nWindowWidth / 2.0f;
		GLfloat	half_height = (GLfloat)m_nWindowHeight / 2.0f;

		glViewport( 0, 0, m_nWindowWidth, m_nWindowHeight );
		glDisable( GL_SCISSOR_TEST );

		glClearColor(	(GLfloat)(m_tBackgroundColor.GetRed()/255.0f),
						(GLfloat)(m_tBackgroundColor.GetGreen()/255.0f),
						(GLfloat)(m_tBackgroundColor.GetBlue()/255.0f),
						(GLfloat)1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
		glDisable( GL_DEPTH_TEST );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho( -half_width, half_width, -half_height, half_height, NEAR_Z, FAR_Z);
		//glOrtho( 0, m_nWindowWidth, m_nWindowHeight, 0, NEAR_Z, FAR_Z );

		glMatrixMode( GL_MODELVIEW);
		glLoadIdentity();

		// check for errors, really should be a while loop since errors can be stacked.

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			Yogi::Core::LogPrint("%s: Error : %d\n", __FUNCTION__, err);
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
bool	TDrawOpenGL::end
		(
		void
		)
{
	//glDisable( GL_TEXTURE_2D );
	ResetPenBrush();

	PopCropRectangle();	// update rectangle
	glDisable( GL_SCISSOR_TEST );

	return inherited::end();
}


/*---------------------------------------------------------------------+\

 * InitialMatrix -

\+---------------------------------------------------------------------*/
CMatrix3x3
		TDrawOpenGL::InitialMatrix
		(
		void
		)
{
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
bool	TDrawOpenGL::Size
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
bool	TDrawOpenGL::BeginContext
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
bool	TDrawOpenGL::EndContext
		(
		void
		)
{
	PopCropRectangle();	// update rectangle
	glDisable( GL_SCISSOR_TEST );

	return inherited::EndContext();
}


/*---------------------------------------------------------------------+\

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::SupportsContext
		(
		void
		)
{
	return false;
	//return inherited::SupportsContext();
}


/*---------------------------------------------------------------------+\

 * PushCropRectangle -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::PushCropRectangle
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
			GLint	w = m_nWindowWidth / 2;
			GLint	h = m_nWindowHeight / 2;

			glEnable( GL_SCISSOR_TEST );
			glScissor( m_tCropCurrent.nLeft + w, m_tCropCurrent.nBottom + h,
				m_tCropCurrent.nRight-m_tCropCurrent.nLeft,
				m_tCropCurrent.nTop-m_tCropCurrent.nBottom );
			//DbgPrint( "PushCropRectangle: %ld, %ld, %ld, %ld\n",
			//	m_tCropCurrent.nLeft, m_tCropCurrent.nTop, m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
		}
		else
		{
			glDisable( GL_SCISSOR_TEST );
			//glScissor( 0, 0, 0, 0 );
			//DbgPrint( "PushCropRectangle: ---------\n" );
		}
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * PopCropRectangle -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::PopCropRectangle
		(
		void
		)
{
	bool	bResult = inherited::PopCropRectangle();

	if ( bResult )
	{
		if ( 0 < m_nCropStackTop)
		{
			GLint	w = m_nWindowWidth / 2;
			GLint	h = m_nWindowHeight / 2;

			glEnable( GL_SCISSOR_TEST );
			glScissor( m_tCropCurrent.nLeft + w, m_tCropCurrent.nBottom + h,
				m_tCropCurrent.nRight-m_tCropCurrent.nLeft,
				m_tCropCurrent.nTop-m_tCropCurrent.nBottom );
			//DbgPrint( "PopCropRectangle: %ld, %ld, %ld, %ld\n",
			//	m_tCropCurrent.nLeft, m_tCropCurrent.nTop, m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
		}
		else
		{
			glDisable( GL_SCISSOR_TEST );
			//glScissor( 0, 0, 0, 0 );
			//DbgPrint( "PopCropRectangle: ---------\n" );
		}
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * MergeCropStack -

\+---------------------------------------------------------------------*/
void	TDrawOpenGL::MergeCropStack
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

	}
	else
	{
		long	w = m_nWindowWidth / 2;
		long	h = m_nWindowHeight / 2;

		m_tCropCurrent.nLeft = -w;
		m_tCropCurrent.nTop = h;
		m_tCropCurrent.nRight = w;
		m_tCropCurrent.nBottom = -h;
	}
}



/*---------------------------------------------------------------------+\

 * SetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::SetUpdateRectangle
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
bool	TDrawOpenGL::GetUpdateRectangle
		(
		long*	pLeft,
		long*	pTop,
		long*	pRight,
		long*	pBottom
		)
{
	*pLeft = 0;
	*pTop = 0;
	*pRight = m_nWindowWidth;
	*pBottom = m_nWindowHeight;
	return true;
	//return inherited::GetUpdateRectangle( pLeft, pTop, pRight, pBottom );
}



/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::LineWidth
		(
		short nWidth
		)
{
	return inherited::LineWidth( nWidth );
}

/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::LineColor
		(
		Yogi::Core::ConstCColorRef rColor
		)
{
	return inherited::LineColor( rColor );
}

/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::FillColor
		(
		Yogi::Core::ConstCColorRef rColor
		)
{
	return inherited::FillColor( rColor );
}


/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::HaloColor
		(
		Yogi::Core::ConstCColorRef rColor
		)
{
	return inherited::HaloColor( rColor );
}




/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	bool	bResult = inherited::FontParams( sFontName, fFontHeight );
	return bResult;
}

/*---------------------------------------------------------------------+\

 * ResetPenBrush -

\+---------------------------------------------------------------------*/
void	TDrawOpenGL::ResetPenBrush
		(
		void
		)
{
//	DestroyBrush();
//	DestroyPen();
//	FontDestroy();
}


/*---------------------------------------------------------------------+\

 * Line -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::Line
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
bool	TDrawOpenGL::Arc
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
bool	TDrawOpenGL::Circle
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
bool	TDrawOpenGL::Ellipse
		(
		GFLOAT	,//xAxis,
		GFLOAT	,//yAxis,
		GFLOAT	,//nHeight,
		GFLOAT	//nWidth
		)
{

	Yogi::Core::LogPrint("TDrawOpenGL::Ellipse called but not implemented.");
	return true;
}

/*---------------------------------------------------------------------+\

 * Pie -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::Pie
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
bool 	TDrawOpenGL::SetFillParms()
{
	if(m_tFillColor.IsNonColor())
	{
		return false;
	}
	else
	{
		Yogi::Core::CColorPtr	pClr;
		if ( Yogi::Core::CColor::BackgroundColor() == m_tFillColor )
			pClr = &m_tBackgroundColor;
		else
			pClr = &m_tFillColor;

		glColor4f(	(GLfloat)(pClr->GetRed()/255.0),
					(GLfloat)(pClr->GetGreen()/255.0),
					(GLfloat)(pClr->GetBlue()/255.0),
					(GLfloat)1.0f );
		//glIndex(m_tFillColor, FULL_OPAQUE);
		glLineWidth( 0.1f );

		return true;
	}
}

/*---------------------------------------------------------------------+\

 * SetLineParms -

\+---------------------------------------------------------------------*/
bool 	TDrawOpenGL::SetLineParms()
{
	if(m_tLineColor.IsNonColor())
	{
		return false;
	}
	else
	{
		Yogi::Core::CColorPtr	pClr;
		if ( Yogi::Core::CColor::BackgroundColor() == m_tFillColor )
			pClr = &m_tBackgroundColor;
		else
			pClr = &m_tLineColor;

		glColor4f(	(GLfloat)(pClr->GetRed()/255.0),
					(GLfloat)(pClr->GetGreen()/255.0),
					(GLfloat)(pClr->GetBlue()/255.0),
					(GLfloat)1.0f);
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
bool	TDrawOpenGL::BeginPolygon
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
bool	TDrawOpenGL::EndPolygon
		(
		void
		)
{
    if(SetFillParms())
    {
		// override this function for correct implementation
		m_nGLMode = GL_LINE_LOOP;	//GL_POLYGON;
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
bool	TDrawOpenGL::BeginPolyline
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
bool	TDrawOpenGL::EndPolyline
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
bool	TDrawOpenGL::Polypoint
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
bool	TDrawOpenGL::PolypointNoTmx
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
bool	TDrawOpenGL::Rectangle
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
		vddsBegin( GL_TRIANGLE_FAN );
		vddsVertexTransform( xPosition, yPosition );
		vddsVertexTransform( xPosition + nWidth, yPosition );
		vddsVertexTransform( xPosition + nWidth, yPosition + nHeight );
		vddsVertexTransform( xPosition, yPosition + nHeight );

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

 * Image -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::Image
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
bool	TDrawOpenGL::ImagePreloaded
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
			case IDraw::F_ORIGINAL:
				{
					nNewWidth = nSrcWidth;
					nNewHeight = nSrcHeight;
					switch ( eAlign )
					{
					case IDraw::A_CENTER:
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case IDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case IDraw::A_RIGHT:
						x += (w - nNewWidth);
						break;
					}
					switch ( eVertAlign )
					{
					case IDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case IDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case IDraw::V_ABSBOTTOM:
					default:
						y -= (h - nNewHeight);
						break;
					}
				}
				break;

			case IDraw::F_SCALED:
				if ( nVwRatio < nSrcRatio )	// height bound
				{
					nNewHeight = h;
					nScale = h / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case IDraw::A_CENTER:
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case IDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case IDraw::A_RIGHT:
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
					case IDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case IDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case IDraw::V_ABSBOTTOM:
					default:
						y -= (h - nNewHeight);
						break;
					}
				}
				break;

			case IDraw::F_ZOOM:
				if ( nSrcRatio < nVwRatio )
				{
					nNewHeight = h;
					nScale = h / nSrcHeight;
					nNewWidth = nScale * nSrcWidth;
					switch ( eAlign )
					{
					case IDraw::A_CENTER:
						x += (w - nNewWidth) / GFLOAT_2;
						break;
					case IDraw::A_LEFT:
						// do nothing we already have the right coordinates
						break;
					case IDraw::A_RIGHT:
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
					case IDraw::V_TOP:
						// do nothing we already have the right coordinates
						break;
					case IDraw::V_MIDDLE:
						y -= (h - nNewHeight) / GFLOAT_2;
						break;
					case IDraw::V_ABSBOTTOM:
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


		glEnable( GL_TEXTURE_2D );

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

#if 1
		GLfloat	aTex[8]
		= {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		GLfloat aVtx[8]
		= {
			x, y,
			x+nNewWidth, y,
			x+nNewWidth, y-nNewHeight,
			x, y-nNewHeight
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer( 2, GL_FLOAT, 0, aVtx );
		glBindTexture( GL_TEXTURE_2D, pImage->nTexture );
		glTexCoordPointer( 2, GL_FLOAT, 0, aTex );

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4 );

#else

		glBindTexture( GL_TEXTURE_2D, pImage->nTexture );
		glBegin( GL_TRIANGLE_FAN );
		glTexCoord2d( 0.0f, 0.0f );	glVertex2d( x, y );
		glTexCoord2d( 1.0f, 0.0f );	glVertex2d( x+nNewWidth, y );
		glTexCoord2d( 1.0f, 1.0f );	glVertex2d( x+nNewWidth, y-nNewHeight );
		glTexCoord2d( 0.0f, 1.0f ); glVertex2d( x, y-nNewHeight );
		glEnd();

#endif

		glDisable( GL_TEXTURE_2D );


		bResult = true;
	}


	return bResult;
}



/*---------------------------------------------------------------------+\

 * ImageLoadFile -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::ImageLoadFile
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

 * ImageRelease -

\+---------------------------------------------------------------------*/
bool	TDrawOpenGL::ImageRelease
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
bool	TDrawOpenGL::Video
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
	bool				bResult = false;
	Yogi::Core::CColor	c;

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


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
