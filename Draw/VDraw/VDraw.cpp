/*---------------------------------------------------------------------+\
|
|	VDraw.cpp  --  brief description of what VDraw.cpp is for
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
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	11-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Bug fix, force line parameters to zero
	23-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix implementation of Size
    22-Dec-2009         R.Hosea			(Reviewed by: M.Rose)
        Added Size() to set matrix size for draw object
	14-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix background color to be "background"
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Support the concept of drawing context for foreground and background
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Support for generic font names 'sans-serif', 'serif' and 'monospace'
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <math.h>
#include <limits.h>

#include "VDraw.h"

NAMESPACE_COMMON_BEGIN

/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


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

 * VDraw - constructor

\+---------------------------------------------------------------------*/
VXDraw::VXDraw
		(
		void
		)
		: inherited(),
		m_pTmx( 0 ),
		m_nWindowWidth( 0 ),
		m_nWindowHeight( 0 ),
		m_eDrawContext( CTX_UNDEFINED ),
		m_aCropStack(),
		m_nCropStackTop( 0 ),
		m_eDayMode( D_NORMAL ),
		m_nLineWidth( 1 ),
		m_tLineColor(),
		m_tFillColor(),
		m_tHaloColor(),
		m_tBackgroundColor(),
		m_eNightColor( C_NORMAL ),
		m_fFontHeight( 10.0 ),
		m_tPointList()

{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );
	m_tPointList.SetBlockSize( 16 );
	m_tFillColor.SetNonColor( true );
	m_tBackgroundColor = CColor::ColorFromName( "background" );
}


VXDraw::VXDraw
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner ),
		m_pTmx( 0 ),
		m_nWindowWidth( 0 ),
		m_nWindowHeight( 0 ),
		m_eDrawContext( CTX_UNDEFINED ),
		m_aCropStack(),
		m_nCropStackTop( 0 ),
		m_eDayMode( D_NORMAL ),
		m_nLineWidth( 1 ),
		m_tLineColor(),
		m_tFillColor(),
		m_tHaloColor(),
		m_tBackgroundColor(),
		m_eNightColor( C_NORMAL ),
		m_fFontHeight( 10.0 ),
		m_tPointList()

{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );
	m_tPointList.SetBlockSize( 16 );
	m_tFillColor.SetNonColor( true );
	m_tBackgroundColor = CColor::ColorFromName( "background" );
}


VXDraw::VXDraw
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner ),
		m_pTmx( 0 ),
		m_nWindowWidth( 0 ),
		m_nWindowHeight( 0 ),
		m_eDrawContext( CTX_UNDEFINED ),
		m_aCropStack(),
		m_nCropStackTop( 0 ),
		m_eDayMode( D_NORMAL ),
		m_nLineWidth( 1 ),
		m_tLineColor(),
		m_tFillColor(),
		m_tHaloColor(),
		m_tBackgroundColor(),
		m_eNightColor( C_NORMAL ),
		m_fFontHeight( 10.0 ),
		m_tPointList()

{
	::strcpy_s( m_sFontName, sizeof( m_sFontName ), "Arial" );
	::strcpy_s( m_sFontSansSerif, sizeof( m_sFontSansSerif ), "Arial" );
	::strcpy_s( m_sFontSerif, sizeof( m_sFontSerif ), "Times New Roman" );
	::strcpy_s( m_sFontMonospace, sizeof( m_sFontMonospace ), "Courier New" );
	m_tPointList.SetBlockSize( 16 );
	m_tFillColor.SetNonColor( true );
	m_tBackgroundColor = CColor::ColorFromName( "background" );
}


/*---------------------------------------------------------------------+\

 * ~VDraw - destructor

\+---------------------------------------------------------------------*/
VXDraw::~VXDraw
		(
		void
		)
{
}





/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * begin -

\+---------------------------------------------------------------------*/
bool	VXDraw::begin
		(
		void
		)
{
	bool		bResult = false;
	CMatrix3x3	mtx = InitialMatrix();

	m_pTmx->SetInitialMatrix( mtx );

	bResult = m_pTmx->begin();

	m_nLineWidth = 0;
	m_tLineColor.SetNonColor( true );
	m_tFillColor.SetNonColor( true );
	m_tHaloColor.SetNonColor( true );

	m_nCropStackTop = 0;

	return bResult;
}


/*---------------------------------------------------------------------+\

 * end -

\+---------------------------------------------------------------------*/
bool	VXDraw::end
		(
		void
		)
{
	m_nLineWidth = 0;
	m_tLineColor.SetNonColor( true );
	m_tFillColor.SetNonColor( true );

	m_nCropStackTop = 0;
	//PopCropRectangle();

	m_pTmx->end();
	return true;
}


/*---------------------------------------------------------------------+\

 * push -

\+---------------------------------------------------------------------*/
bool	VXDraw::push
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		GFLOAT	xShift,
		GFLOAT	yShift,
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	rotation,
		GFLOAT	scale
		)
{
	return m_pTmx->push( xPosition, yPosition, xShift, yShift, xAxis, yAxis, rotation, scale );
}

/*---------------------------------------------------------------------+\

 * pop -

\+---------------------------------------------------------------------*/
bool	VXDraw::pop
		(
		void
		)
{
	return m_pTmx->pop();
}


/*---------------------------------------------------------------------+\

 * margin -

\+---------------------------------------------------------------------*/
bool	VXDraw::margin
		(
		int	nLeft,
		int	nTop,
		int	nRight,
		int	nBottom
		)
{
	if ( m_pTmx )
		return m_pTmx->margin( nLeft, nTop, nRight, nBottom );
	else
		return false;
}



/*---------------------------------------------------------------------+\

 * SupportsContext -

\+---------------------------------------------------------------------*/
bool	VXDraw::SupportsContext
		(
		void
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * PushCropRectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::PushCropRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	bool		bResult = false;
	XCropRect*	p = m_aCropStack.PointItem( m_nCropStackTop );
	if ( p )
	{
		GFLOAT	fx;
		GFLOAT	fy;

		TransformPoint( fx, fy, GFLOAT(nLeft), GFLOAT(nTop) );
		p->nLeft = long(fx);
		p->nTop = long(fy);
		TransformPoint( fx, fy, GFLOAT(nRight), GFLOAT(nBottom) );
		p->nRight = long(fx);
		p->nBottom = long(fy);
		bResult = true;
		++m_nCropStackTop;

		MergeCropStack();
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * PopCropRectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::PopCropRectangle
		(
		void
		)
{
	bool	bResult = false;

	if ( 0 < m_nCropStackTop )
	{
		--m_nCropStackTop;
		bResult = true;
	}
	MergeCropStack();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * MergeCropStack -

\+---------------------------------------------------------------------*/
void	VXDraw::MergeCropStack
		(
		void
		)
{
	XCropRect*	p = m_aCropStack.PointArray();
	if ( p  &&  0 < m_nCropStackTop )
	{
		XCropRect*	pEnd = p + m_nCropStackTop;

		m_tCropCurrent.nLeft = 0;
		m_tCropCurrent.nTop = 0;
		m_tCropCurrent.nRight = m_nWindowWidth;
		m_tCropCurrent.nBottom = m_nWindowHeight;
		//m_tCropCurrent = *p;	// initialize to bottom of stack;

		while ( p < pEnd )
		{
			if ( m_tCropCurrent.nLeft < p->nLeft )
				m_tCropCurrent.nLeft = p->nLeft;
			if ( m_tCropCurrent.nTop < p->nTop )
				m_tCropCurrent.nTop = p->nTop;
			if ( p->nRight < m_tCropCurrent.nRight )
				m_tCropCurrent.nRight = p->nRight;
			if ( p->nBottom < m_tCropCurrent.nBottom )
				m_tCropCurrent.nBottom = p->nBottom;
			++p;
		}
	}
	else
	{
		m_tCropCurrent.nLeft = 0;
		m_tCropCurrent.nTop = 0;
		m_tCropCurrent.nRight = m_nWindowWidth;
		m_tCropCurrent.nBottom = m_nWindowHeight;
	}
	//DbgPrint( "MergeCropStack: %ld, %ld, %ld, %ld\n",
	//	m_tCropCurrent.nLeft, m_tCropCurrent.nTop,
	//	m_tCropCurrent.nRight, m_tCropCurrent.nBottom );
}


/*---------------------------------------------------------------------+\

 * RefreshRectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::RefreshRectangle
		(
		void
		)
{
	// should be overridden
	return false;
}




/*---------------------------------------------------------------------+\

 * SetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::SetUpdateRectangle
		(
		long	nLeft,
		long	nTop,
		long	nRight,
		long	nBottom
		)
{
	if ( nLeft < nRight )
	{
		const long	zero = 0;

		m_nUpdateLeft = umax(nLeft, zero);
		m_nUpdateTop = umax(nTop, zero);
		m_nUpdateRight = umin(nRight, m_nWindowWidth);
		m_nUpdateBottom = umin(nBottom, m_nWindowHeight);
	}
	else
	{
		m_nUpdateLeft = 0;
		m_nUpdateTop = 0;
		m_nUpdateRight = m_nWindowWidth;
		m_nUpdateBottom = m_nWindowHeight;
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * GetUpdateRectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::GetUpdateRectangle
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

 * Size - Sets matrix size

\+---------------------------------------------------------------------*/
bool	VXDraw::Size
		(
		long	nWidth,
		long	nHeight
		)
{
	bool	bResult = false;

	if ( nWidth != m_nWindowWidth )
		bResult = true;
	m_nWindowWidth = nWidth;

	if ( nHeight != m_nWindowHeight )
		bResult = true;
	m_nWindowHeight = nHeight;

	return bResult;
}




/*---------------------------------------------------------------------+\

 * BeginContext -

\+---------------------------------------------------------------------*/
bool	VXDraw::BeginContext
		(
		EDrawContexts ctx
		)
{
	m_eDrawContext = ctx;
	return true;
}



/*---------------------------------------------------------------------+\

 * EndContext -

\+---------------------------------------------------------------------*/
bool	VXDraw::EndContext
		(
		void
		)
{
	m_eDrawContext = CTX_UNDEFINED;
	return true;
}


/*---------------------------------------------------------------------+\

 * CurrentContext -

\+---------------------------------------------------------------------*/
VXDraw::EDrawContexts
		VXDraw::CurrentContext
		(
		void
		)
{
	return m_eDrawContext;
}

/*---------------------------------------------------------------------+\

 * DayMode -

\+---------------------------------------------------------------------*/
bool	VXDraw::DayMode
		(
		EDayModes eMode
		)
{
	m_eDayMode = eMode;
	return true;
}


/*---------------------------------------------------------------------+\

 * LineWidth -

\+---------------------------------------------------------------------*/
bool	VXDraw::LineWidth
		(
		short	nWidth
		)
{
	if ( m_nLineWidth != nWidth )
	{
		m_nLineWidth = nWidth;
		return true;
	}
	else
	{
		return false;
	}
}

/*---------------------------------------------------------------------+\

 * LineColor -

\+---------------------------------------------------------------------*/
bool	VXDraw::LineColor
		(
		CColorRef	rColor
		)
{
	if ( m_tLineColor != rColor )
	{
		m_tLineColor = rColor;
		return true;
	}
	else
	{
		return false;
	}
}

/*---------------------------------------------------------------------+\

 * FillColor -

\+---------------------------------------------------------------------*/
bool	VXDraw::FillColor
		(
		CColorRef	rColor
		)
{
	if ( m_tFillColor != rColor )
	{
		m_tFillColor = rColor;
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * HaloColor -

\+---------------------------------------------------------------------*/
bool	VXDraw::HaloColor
		(
		CColorRef	rColor
		)
{
	if ( m_tHaloColor != rColor )
	{
		m_tHaloColor = rColor;
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * BackgroundColor -

\+---------------------------------------------------------------------*/
bool	VXDraw::BackgroundColor
		(
		ConstCColorRef	rColor
		)
{
	if ( m_tBackgroundColor != rColor )
	{
		m_tBackgroundColor = rColor;
		m_nUpdateLeft = 0;
		m_nUpdateTop = 0;
		m_nUpdateRight = m_nWindowWidth;
		m_nUpdateBottom = m_nWindowHeight;
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * NightColor -

\+---------------------------------------------------------------------*/
bool	VXDraw::NightColor
		(
		ENightColorModes eMode
		)
{
	m_eNightColor = eMode;
	return true;
}


/*---------------------------------------------------------------------+\

 * FontParams -

\+---------------------------------------------------------------------*/
bool	VXDraw::FontParams
		(
		const char*	sFontName,
		GFLOAT		fFontHeight
		)
{
	bool	bResult = false;
	if ( m_fFontHeight != fFontHeight )
	{
		m_fFontHeight = fFontHeight;
		bResult = true;
	}
	do	// sequence
	{
		if ( 0 == ::_stricmp( sFontName, "sans-serif" )
			||	0 == ::_stricmp( sFontName, "sansserif" ) )
		{
			if ( 0 != ::strcmp( m_sFontName, m_sFontSansSerif ) )
			{
				::strcpy_s( m_sFontName, sizeof( m_sFontName ), m_sFontSansSerif );
				bResult = true;
			}
			break;
		}

		if ( 0 == ::_stricmp( sFontName, "serif" ) )
		{
			if ( 0 != ::strcmp( m_sFontName, m_sFontSerif ) )
			{
				::strcpy_s( m_sFontName, sizeof( m_sFontName ), m_sFontSerif );
				bResult = true;
			}
			break;
		}

		if ( 0 == ::_stricmp( sFontName, "monospace" ) )
		{
			if ( 0 != ::strcmp( m_sFontName, m_sFontMonospace ) )
			{
				::strcpy_s( m_sFontName, sizeof( m_sFontName ), m_sFontMonospace );
				bResult = true;
			}
			break;
		}

		if ( 0 != ::_stricmp( sFontName, m_sFontName ) )
		{
			::strcpy_s( m_sFontName, sizeof(m_sFontName), sFontName );
			bResult = true;
		}
	} sequence; // end sequence

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Line -

\+---------------------------------------------------------------------*/
bool	VXDraw::Line
		(
		GFLOAT	,//xStart,
		GFLOAT	,//yStart,
		GFLOAT	,//xEnd,
		GFLOAT	//yEnd
		)
{
	return false;
}



/*---------------------------------------------------------------------+\

 * Arc -

\+---------------------------------------------------------------------*/
bool	VXDraw::Arc
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	bool	bResult = false;
	bResult = BeginPolyline();
	if ( bResult )
	{
		bResult = ArcStrokeAsPolyline( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
		if ( bResult )
			bResult = EndPolyline();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * ArcStrokeAsPolyline -

\+---------------------------------------------------------------------*/
bool	VXDraw::ArcStrokeAsPolyline
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	fStartAngle = normalizeAngle( fStartAngle );
	fEndAngle = normalizeAngle( fEndAngle );
	if ( ::fabsf(fStartAngle - fEndAngle) < GFLOAT_EPSILON )
	{
		return CircleStrokeAsPolygon( xAxis, yAxis, nRadius );
	}
	else
	{
		GFLOAT	cx;
		GFLOAT	cy;
		GFLOAT	tx;
		GFLOAT	ty;
		GFLOAT	r;

		TransformPoint( cx, cy, GFLOAT_1, GFLOAT_0 );
		TransformPoint( tx, ty, GFLOAT_0, GFLOAT_0 );

		tx = cx - tx;
		ty = cy - ty;

		if ( ::fabsf(tx) < GFLOAT_EPSILON )
		{
			if ( ty < GFLOAT_0 )
				r = kPI * 1.5f;
			else
				r = GFLOAT_PI_2;
		}
		else
		{
			r = atanf( ty / tx );

			//CCASON
			//TODO: The r calculation(s) don't yield full 360-degree results
			r*=2;	//this is a kluge to achieve full 360-degree angle calculations
		}
		GFLOAT	start_angle = fStartAngle + r;
		GFLOAT	end_angle = fEndAngle + r;
		GFLOAT	arc_angle;
		if ( end_angle < start_angle )
			end_angle += GFLOAT_2PI;
		arc_angle = end_angle - start_angle;
		start_angle = normalizeAngle( start_angle );

		TransformPoint( cx, cy, xAxis, yAxis );
		r = TransformLength( nRadius );


		int		num_segments = 36;
		int		nSeg = SegmentsFromCircleRadius( r );
		nSeg = int(nSeg * arc_angle / GFLOAT_2PI + 0.5f);
		if ( nSeg < 3 )
			nSeg = 3;
		else if ( 180 < nSeg )
			nSeg = 180;
		num_segments = nSeg;

		GFLOAT	theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
		GFLOAT	tangetial_factor = tanf(theta);
		GFLOAT	radial_factor = cosf(theta);

		GFLOAT x = r * cosf(start_angle);	//we now start at the start angle
		GFLOAT y = r * sinf(start_angle);

		//BeginPolyline();
		for(int ii = 0; ii < num_segments; ii++)
		{
			PolypointNoTmx( x + cx, y + cy );

			tx = -y;
			ty = x;

			x += tx * tangetial_factor;
			y += ty * tangetial_factor;

			x *= radial_factor;
			y *= radial_factor;
		}
		//EndPolyline();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * Circle -

\+---------------------------------------------------------------------*/
bool	VXDraw::Circle
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius
		)
{
	bool	bResult = BeginPolygon();
	if ( bResult )
	{
		bResult = CircleStrokeAsPolygon( xAxis, yAxis, nRadius );
		if ( bResult )
		{
			bResult = EndPolygon();
		}
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * CircleStrokeAsPolygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::CircleStrokeAsPolygon
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius
		)
{
	GFLOAT	cx;
	GFLOAT	cy;
	GFLOAT	r;

	TransformPoint( cx, cy, xAxis, yAxis );
	r = TransformLength( nRadius );


	int		num_segments = 32;

	int		nSeg = SegmentsFromCircleRadius( r );
	if ( nSeg < 5 )
		nSeg = 5;
	else if ( 180 < nSeg )
		nSeg = 180;
	num_segments = nSeg;


	GFLOAT	theta = GFLOAT_2PI / GFLOAT(num_segments);
	GFLOAT	c = cosf(theta);	//precalculate the sine and cosine
	GFLOAT	s = sinf(theta);
	GFLOAT	t;

	GFLOAT	x = r;	//we start at angle = 0
	GFLOAT	y = 0;

	GFLOAT	x1 = x + cx;
	GFLOAT	y1 = y + cy;

	//vddsBegin(mode);
	for(int ii = 0; ii < num_segments; ii++)
	{
		PolypointNoTmx( x + cx, y + cy);
		//vddsVertex(x + cx, y + cy);	//output vertex

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	PolypointNoTmx( x1, y1 );
	//vddsEnd();

	return true;
}

/*---------------------------------------------------------------------+\

 * Ellipse -

\+---------------------------------------------------------------------*/
bool	VXDraw::Ellipse
		(
		GFLOAT	,//xAxis,
		GFLOAT	,//yAxis,
		GFLOAT	,//nHeight,
		GFLOAT	//nWidth
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * Pie -

\+---------------------------------------------------------------------*/
bool	VXDraw::Pie
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	bool	bResult = false;
	bResult = BeginPolygon();
	if ( bResult )
	{
		bResult = PieStrokeAsPolygon( xAxis, yAxis, nRadius, fStartAngle, fEndAngle );
		if ( bResult )
			bResult = EndPolygon();
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * PieStrokeAsPolygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::PieStrokeAsPolygon
		(
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	nRadius,
		GFLOAT	fStartAngle,
		GFLOAT	fEndAngle
		)
{
	fStartAngle = normalizeAngle( fStartAngle );
	fEndAngle = normalizeAngle( fEndAngle );

	if ( ::fabsf(fStartAngle - fEndAngle) < GFLOAT_EPSILON )
	{
		return CircleStrokeAsPolygon( xAxis, yAxis, nRadius );
	}
	else
	{

		GFLOAT r, cx, cy, tx, ty;

		//rotation transform
		TransformPoint( cx, cy, GFLOAT_1, GFLOAT_0 );
		TransformPoint( tx, ty, GFLOAT_0, GFLOAT_0 );

		tx = cx - tx;
		ty = cy - ty;

		if ( ::fabsf(tx) < GFLOAT_EPSILON )
		{
			if ( ty < GFLOAT_0 )
				r = kPI * 1.5f;
			else
				r = GFLOAT_PI_2;
		}
		else
		{
			r = atanf( ty / tx );

			//CCASON
			//TODO: The r calculation(s) don't yield full 360-degree results
			r*=2;	//this is a kluge to achieve full 360-degree angle calculations
		}

		GFLOAT	start_angle = fStartAngle + r;
		GFLOAT	end_angle = fEndAngle + r;

		//end rotation transform

		//scale transform
		r = TransformLength( nRadius );
		//translation transform
		TransformPoint( cx, cy, xAxis, yAxis );

		GFLOAT	arc_angle;

		if ( end_angle < start_angle )
			end_angle += kPI * 2;
		arc_angle = end_angle - start_angle;
		start_angle = normalizeAngle( start_angle );

		int		num_segments = 36;
		int		nSeg = SegmentsFromCircleRadius( r );
		nSeg = int(nSeg * arc_angle / GFLOAT_2PI + 0.5f);
		if ( nSeg < 3 )
			nSeg = 3;
		else if ( 180 < nSeg )
			nSeg = 180;
		num_segments = nSeg;

		GFLOAT	theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
		GFLOAT	tangetial_factor = tanf(theta);
		GFLOAT	radial_factor = cosf(theta);

		GFLOAT x = r * cosf(start_angle);	//we now start at the start angle
		GFLOAT y = r * sinf(start_angle);

		//BeginPolygon();
		PolypointNoTmx( cx, cy );
		for(int ii = 0; ii < num_segments; ii++)
		{
			PolypointNoTmx(x + cx, y + cy);

			tx = -y;
			ty = x;

			x += tx * tangetial_factor;
			y += ty * tangetial_factor;

			x *= radial_factor;
			y *= radial_factor;
		}
		//PolypointNoTmx( cx, cy );
		//EndPolygon();

		return true;

	}
}




/*---------------------------------------------------------------------+\

 * BeginPolygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::BeginPolygon
		(
		void
		)
{
	m_tPointList.Truncate();
	return true;
}


/*---------------------------------------------------------------------+\

 * EndPolygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::EndPolygon
		(
		void
		)
{
	return false;
}




/*---------------------------------------------------------------------+\

 * Polygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::Polygon
		(
		long		nNumPoints,
		FPointPtr	pPointList
		)
{
	bool		bResult = true;
	FPointPtr	p = pPointList;
	FPointPtr	pEnd = p + nNumPoints;

	bResult = BeginPolygon();
	if ( bResult )
	{
		while ( p < pEnd )
		{
			Polypoint( p->x, p->y );
			++p;
		}
		bResult = EndPolygon();
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * Polyline -

\+---------------------------------------------------------------------*/
bool	VXDraw::Polyline
		(
		long		nNumPoints,
		FPointPtr	pPointList
		)
{
	bool		bResult = true;
	FPointPtr	p = pPointList;
	FPointPtr	pEnd = p + nNumPoints;

	bResult = BeginPolyline();
	if ( bResult )
	{
		while ( p < pEnd )
		{
			Polypoint( p->x, p->y );
			++p;
		}
		bResult = EndPolyline();
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Rectangle -

\+---------------------------------------------------------------------*/
bool	VXDraw::Rectangle
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		CORNERSTYLE	eCornerStyle,	//= C_SQUARE,
		GFLOAT		nCornerSize		//= 0.0f
		)
{
	bool	bResult = BeginPolygon();
	if ( bResult )
	{
		bResult = RectangleStrokeAsPolygon( xPosition, yPosition, nWidth, nHeight, eCornerStyle, nCornerSize );
		if ( bResult )
			bResult = EndPolygon();
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * RectangleStrokeAsPolygon -

\+---------------------------------------------------------------------*/
bool	VXDraw::RectangleStrokeAsPolygon
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		CORNERSTYLE	eCornerStyle,	//= C_SQUARE,
		GFLOAT		nCornerSize		//= 0.0f
		)
{
	bool	bResult = true;
	GFLOAT	x = xPosition;
	GFLOAT	y = yPosition;
	GFLOAT	w = nWidth;
	GFLOAT	h = nHeight;
	GFLOAT	c = nCornerSize;

	if ( C_SQUARE == eCornerStyle  ||  c < GFLOAT_EPSILON )
	{
		Polypoint( x, y );
		Polypoint( x + w, y );
		Polypoint( x + w, y + h );
		Polypoint( x, y + h );
		Polypoint( x, y );
	}
	else if ( C_BEVEL == eCornerStyle )
	{
		GFLOAT	m = umin( h, w );
		if ( m < c * 2 )
			c = m / 2;
		Polypoint( x + c, y );
		Polypoint( x + w - c, y );
		Polypoint( x + w, y + c );
		Polypoint( x + w, y + h - c );
		Polypoint( x + w - c, y + h );
		Polypoint( x + c, y + h );
		Polypoint( x, y + h - c );
		Polypoint( x, y + c );
		Polypoint( x + c, y );
	}
	else if ( C_RABBET == eCornerStyle )
	{
		GFLOAT	m = umin( h, w );
		if ( m < c * 2 )
			c = m / 2;

		GFLOAT	xc = x + c;
		GFLOAT	xw = x + w;
		GFLOAT	xwc = xw - c;
		GFLOAT	yc = y + c;
		GFLOAT	yh = y + h;
		GFLOAT	yhc = yh - c;

		Polypoint( x, yc );
		Polypoint( xc, yc );
		Polypoint( xc, y );

		Polypoint( xwc, y );
		Polypoint( xwc, yc );
		Polypoint( xw, yc );

		Polypoint( xw, yhc );
		Polypoint( xwc, yhc );
		Polypoint( xwc, yh );

		Polypoint( xc, yh );
		Polypoint( xc, yhc );
		Polypoint( x, yhc );

		Polypoint( x, yc );
	}
	else if ( C_ROUND == eCornerStyle )
	{
		GFLOAT	m = umin( h, w );
		if ( m < c * 2 )
			c = m / 2;

		GFLOAT	xc = x + c;
		GFLOAT	xw = x + w;
		GFLOAT	xwc = xw - c;
		GFLOAT	yc = y + c;
		GFLOAT	yh = y + h;
		GFLOAT	yhc = yh - c;

		Polypoint( x, yc );
		ArcStrokeAsPolyline( xc, yhc, c, GFLOAT_PI, GFLOAT_PI * 3.0f / 2.0f );
		ArcStrokeAsPolyline( xwc, yhc, c, GFLOAT_PI * 3.0f / 2.0f, GFLOAT_PI * 2.0f );
		ArcStrokeAsPolyline( xwc, yc, c, GFLOAT_0, GFLOAT_PI / 2.0f );
		ArcStrokeAsPolyline( xc, yc, c, GFLOAT_PI / 2.0f, GFLOAT_PI );
	}
	else if ( C_COVE == eCornerStyle )
	{
		GFLOAT	m = umin( h, w );
		if ( m < c * 2 )
			c = m / 2;

		GFLOAT	xw = x + w;
		GFLOAT	yh = y + h;

		Polypoint( x + c, y );
		ArcStrokeAsPolyline( xw, y, c, GFLOAT_PI, GFLOAT_PI * 3.0f / 2.0f );
		ArcStrokeAsPolyline( xw, yh, c, GFLOAT_PI / 2.0f, GFLOAT_PI );
		ArcStrokeAsPolyline( x, yh, c, GFLOAT_0, GFLOAT_PI / 2.0f );
		ArcStrokeAsPolyline( x, y, c, GFLOAT_PI * 3.0f / 2.0f, GFLOAT_2PI );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * TextString -

\+---------------------------------------------------------------------*/
bool	VXDraw::TextString
		(
		GFLOAT			,//xPosition,
		GFLOAT			,//yPosition,
		IDraw::EAlignments		,//eAlign,
		IDraw::EVerticalAlignments	,//eVertAlign,
		const char*		,//sString,
		long			//nCount = -1
		)
{
	return false;
}





/*---------------------------------------------------------------------+\

 * Video -

\+---------------------------------------------------------------------*/
bool	VXDraw::Video
		(
		GFLOAT			,//xPosition,
		GFLOAT			,//yPosition,
		GFLOAT			,//nWidth,
		GFLOAT			,//nHeight,
		CVariantDataRef		,//sSource,
		IDraw::EFitments	,//eFitment, // = F_Fill,
		IDraw::EAlignments	,//eAlign, // = A_Center,
		IDraw::EVerticalAlignments ,//eVertAlign, // = V_Middle,
		bool		//bMirror // = false
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VXDraw::Image
		(
		GFLOAT		xPosition,
		GFLOAT		yPosition,
		GFLOAT		nWidth,
		GFLOAT		nHeight,
		const char*	sSource,
		IDraw::EFitments	eFitment, // = F_Fill,
		IDraw::EAlignments	eAlign, // = A_Center,
		IDraw::EVerticalAlignments eVertAlign // = V_Middle,
		)
{
	bool		bResult = false;

	do_sequence
	{
		VImagePtr	pImage = 0;
		bResult = ImageLoadFile( sSource, &pImage );
		if ( ! bResult )
			break;

		bResult = ImagePreloaded( xPosition, yPosition, nWidth, nHeight, pImage,
								eFitment, eAlign, eVertAlign );

		pImage->Destroy();

		//ImageRelease( (void*)pImage );
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VXDraw::ImagePreloaded
		(
		GFLOAT		,//xPosition,
		GFLOAT		,//yPosition,
		GFLOAT		,//nWidth,
		GFLOAT		,//nHeight,
		VImagePtr	,//pImage,
		IDraw::EFitments	,//eFitment = F_FILL,
		IDraw::EAlignments	,//eAlign = A_CENTER,		// used for F_FitAspect & F_FillAspect
		IDraw::EVerticalAlignments	//eVertAlign = V_MIDDLE
		)
{
	return false;
}

/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VXDraw::ImageLoadFile
		(
		const char*	,//sSource,
		VImagePtr*	ppImage
		)
{
	if ( ppImage )
		*ppImage = 0;
	return false;
}

/*---------------------------------------------------------------------+\

 * Image -

\+---------------------------------------------------------------------*/
bool	VXDraw::ImageRelease
		(
		VImagePtr		pVImage
		)
{
	if ( pVImage )
	{
		XImagePtr	pImage = static_cast<XImagePtr>( pVImage );

		pImage->Destroy();
	}
	return true;
}


/*---------------------------------------------------------------------+\

 * BeginPolyline -

\+---------------------------------------------------------------------*/
bool	VXDraw::BeginPolyline
		(
		void
		)
{
	m_tPointList.Truncate();
	return true;
}

bool	VXDraw::EndPolyline
		(
		void
		)
{
	return false;
}



/*---------------------------------------------------------------------+\

 * Polypoint -

\+---------------------------------------------------------------------*/
bool	VXDraw::Polypoint
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	VDRAWPOINT*	p = m_tPointList.AppendArray();
	if ( p )
	{
		GFLOAT	fX;
		GFLOAT	fY;

		TransformPoint( fX, fY, x, y );

		p->x = VDRAWCAST_VALUE( fX );
		p->y = VDRAWCAST_VALUE( fY );
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * PolypointNoTmx -

\+---------------------------------------------------------------------*/
bool	VXDraw::PolypointNoTmx
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	VDRAWPOINT*	p = m_tPointList.AppendArray();
	if ( p )
	{
		p->x = VDRAWCAST_VALUE( x );
		p->y = VDRAWCAST_VALUE( y );
		return true;
	}
	else
	{
		return false;
	}
}




/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/





/*---------------------------------------------------------------------+\

 * InitialMatrix -

\+---------------------------------------------------------------------*/
CMatrix3x3
		VXDraw::InitialMatrix
		(
		void
		)
{
	return CMatrix3x3();
}



/*---------------------------------------------------------------------+\

 * SegmentsFromCircleRadius -

\+---------------------------------------------------------------------*/
int		VXDraw::SegmentsFromCircleRadius
		(
		GFLOAT r
		)
{
	int	nSegments = 5;

	if ( GFLOAT_1 < r )
	{
		const GFLOAT	kChordTolerance = GFLOAT(0.25f);

		GFLOAT	fSegmentHeight = r - kChordTolerance;
		GFLOAT	fCentralAngle = GFLOAT_2 * atanf(sqrtf( r * r - fSegmentHeight * fSegmentHeight ) / fSegmentHeight );

		if ( fCentralAngle < GFLOAT_EPSILON )
			nSegments = 5;
		else
			nSegments = int(ceilf( GFLOAT_2PI / fCentralAngle ));
	}
	return nSegments;
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
void*	VXDraw::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDraw )
			pI = INTERFACE_THIS( IDrawPtr );
		else
			pI = 0;
	}

	return pI;
}

#if 0 //def _DEBUG
/*---------------------------------------------------------------------+\

 * InternalAddRef -

\+---------------------------------------------------------------------*/
NRefCount
		VXDraw::InternalAddRef
		(
		void
		)
{
	NRefCount	n = inherited::InternalAddRef();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, m_nRefCount );
	return n;
}

/*---------------------------------------------------------------------+\

 * InternalRelease -

\+---------------------------------------------------------------------*/
NRefCount
		VXDraw::InternalRelease
		(
		void
		)
{
	NRefCount	n = inherited::InternalRelease();
	LOCAL_PRINT( "%s: refcount=%d\n", __FUNCTION__, n );
	return n;
}


/*---------------------------------------------------------------------+\

 * FinalRelease -

\+---------------------------------------------------------------------*/
void	VXDraw::FinalRelease
		(
		void
		)
{
	LOCAL_PRINT( "%s\n", __FUNCTION__ );
	inherited::FinalRelease();
}

#endif // _DEBUG

/*---------------------------------------------------------------------+\
|	IPluginLoadConfiguration
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * Load - Load parameters from XML

\+---------------------------------------------------------------------*/
bool	VXDraw::Load
		(
		VPluginConfigurationPtr	pConfig,
		VPluginLibraryPtr		pLib
		)
{
	bool bResult = inherited::Load( pConfig, pLib );

	if ( bResult )
	{
		m_pTmx = QI_THIS_( IDrawTmx2 );
		if ( ! m_pTmx )
			bResult = false;

	}

	return bResult;
}


//	oO0Q qpg  {[()]} l1 :;,. <> *




NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

