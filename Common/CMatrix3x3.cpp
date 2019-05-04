/*---------------------------------------------------------------------+\
|
|	CMatrix3x3.cpp  --  3 x 3 matrix to calculate 2d transformations
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
	20-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add Set and Get functions
	10-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Move to "Common" folder with "Xxx::Common::" namespace
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	14-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UMath.h"

#include "CMatrix3x3.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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
const CMatrix3x3	CMatrix3x3::kIdentity;
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

 * CMatrix3x3 - constructor

\+---------------------------------------------------------------------*/
CMatrix3x3::CMatrix3x3
		(
		void
		)
		: m_11( GFLOAT_1 ), m_12( GFLOAT_0 ), m_13( GFLOAT_0 )
		, m_21( GFLOAT_0 ), m_22( GFLOAT_1 ), m_23( GFLOAT_0 )
		, m_31( GFLOAT_0 ), m_32( GFLOAT_0 ), m_33( GFLOAT_1 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3 - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3::CMatrix3x3
		(
		ConstCMatrix3x3Ref	r
		)
		: m_11( r.m_11 ), m_12( r.m_12 ), m_13( r.m_13 )
		, m_21( r.m_21 ), m_22( r.m_22 ), m_23( r.m_23 )
		, m_31( r.m_31 ), m_32( r.m_32 ), m_33( r.m_33 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3 - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3::CMatrix3x3
		(
		GFLOAT m11, GFLOAT m12, GFLOAT m13,
		GFLOAT m21, GFLOAT m22, GFLOAT m23,
		GFLOAT m31, GFLOAT m32, GFLOAT m33
		)
		: m_11( m11 ), m_12( m12 ), m_13( m13 )
		, m_21( m21 ), m_22( m22 ), m_23( m23 )
		, m_31( m31 ), m_32( m32 ), m_33( m33 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3 - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3::CMatrix3x3
		(
		GFLOAT m11, GFLOAT m12,
		GFLOAT m21, GFLOAT m22,
		GFLOAT ofX, GFLOAT ofY
		)
		: m_11( m11 ), m_12( m12 ), m_13( 0.0f )
		, m_21( m21 ), m_22( m22 ), m_23( 0.0f )
		, m_31( ofX ), m_32( ofY ), m_33( 1.0f )
{
}

/*---------------------------------------------------------------------+\

 * ~CMatrix3x3 - destructor

\+---------------------------------------------------------------------*/
CMatrix3x3::~CMatrix3x3
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CMatrix3x3Ref
		CMatrix3x3::operator=
		(
		ConstCMatrix3x3Ref	r
		)
{
	Set( r );
	return *this;
}


/*----------------------------------------------------------------------+\

 * Set - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3::Set
		(
		ConstCMatrix3x3Ref	r
		)
{
	m_11 = r.m_11;	m_12 = r.m_12;	m_13 = r.m_13;
	m_21 = r.m_21;	m_22 = r.m_22;	m_23 = r.m_23;
	m_31 = r.m_31;	m_32 = r.m_32;	m_33 = r.m_33;
}


/*----------------------------------------------------------------------+\

 * Set - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3::Set
		(
		GFLOAT m11, GFLOAT m12, GFLOAT m13,
		GFLOAT m21, GFLOAT m22, GFLOAT m23,
		GFLOAT m31, GFLOAT m32, GFLOAT m33
		)
{
	m_11 = m11;	m_12 = m12;	m_13 = m13;
	m_21 = m21;	m_22 = m22;	m_23 = m23;
	m_31 = m31;	m_32 = m32;	m_33 = m33;
}

/*----------------------------------------------------------------------+\

 * Get - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3::Get
		(
		GFLOAT* m11, GFLOAT* m12, GFLOAT* m13,
		GFLOAT* m21, GFLOAT* m22, GFLOAT* m23,
		GFLOAT* m31, GFLOAT* m32, GFLOAT* m33
		) const
{
	*m11 = m_11;	*m12 = m_12;	*m13 = m_13;
	*m21 = m_21;	*m22 = m_22;	*m23 = m_23;
	*m31 = m_31;	*m32 = m_32;	*m33 = m_33;
}

/*---------------------------------------------------------------------+\

 * Equals -

\+---------------------------------------------------------------------*/
bool	CMatrix3x3::Equals
		(
		ConstCMatrix3x3Ref r
		) const
{
	if ( m_11 != r.m_11 )
		return false;
	if ( m_12 != r.m_12 )
		return false;
	if ( m_13 != r.m_13 )
		return false;

	if ( m_21 != r.m_21 )
		return false;
	if ( m_22 != r.m_22 )
		return false;
	if ( m_23 != r.m_23 )
		return false;

	if ( m_31 != r.m_31 )
		return false;
	if ( m_32 != r.m_32 )
		return false;
	if ( m_33 != r.m_33 )
		return false;

	return true;
}



/*---------------------------------------------------------------------+\

 * IsIdentity -

\+---------------------------------------------------------------------*/
bool	CMatrix3x3::IsIdentity
		(
		void
		) const
{
	return Equals( CMatrix3x3::kIdentity );
}


/*---------------------------------------------------------------------+\

 * IsAffine -

\+---------------------------------------------------------------------*/
bool	CMatrix3x3::IsAffine
		(
		void
		) const
{
	bool	bResult = false;

	if ( GFLOAT_0 == m_13
		&&	GFLOAT_0 == m_23
		&&	(GFLOAT_0 == m_33  ||  GFLOAT_1 == m_33 ) )
		bResult = true;

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Invert -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfInvert
		(
		void
		)
{
	GFLOAT d0 = m_22  * m_33 - m_23  * m_32;
	GFLOAT d1 = m_13  * m_32 - m_12  * m_33;
	GFLOAT d2 = m_12  * m_23 - m_13  * m_22;
	GFLOAT d  = m_11  * d0 + m_21 * d1 + m_31 * d2;
	if(d == GFLOAT_0)
	{
		*this = _Identity();
	}
	else
	{
		d = GFLOAT_1 / d;
		CMatrix3x3 a = *this;
		m_11 = d * d0;
		m_12 = d * d1;
		m_13 = d * d2;
		m_21 = d * (a.m_23 * a.m_31 - a.m_21 * a.m_33);
		m_22 = d * (a.m_11 * a.m_33 - a.m_13 * a.m_31);
		m_23 = d * (a.m_13 * a.m_21 - a.m_13 * a.m_23);
		m_31 = d * (a.m_21 * a.m_32 - a.m_22 * a.m_31);
		m_32 = d * (a.m_12 * a.m_31 - a.m_11 * a.m_32);
		m_33 = d * (a.m_11 * a.m_22 - a.m_12 * a.m_21);
	}
}


/*---------------------------------------------------------------------+\

 * Multiply -

\+---------------------------------------------------------------------*/
CMatrix3x3Ref
		CMatrix3x3::SelfMultiply
		(
		ConstCMatrix3x3Ref r
		)
{
	CMatrix3x3	out(
				m_11*r.m_11 + m_12*r.m_21 + m_13*r.m_31,
				m_11*r.m_12 + m_12*r.m_22 + m_13*r.m_32,
				m_11*r.m_13 + m_12*r.m_23 + m_13*r.m_33,

				m_21*r.m_11 + m_22*r.m_21 + m_23*r.m_31,
				m_21*r.m_12 + m_22*r.m_22 + m_23*r.m_32,
				m_21*r.m_13 + m_22*r.m_23 + m_23*r.m_33,

				m_31*r.m_11 + m_32*r.m_21 + m_33*r.m_31,
				m_31*r.m_12 + m_32*r.m_22 + m_33*r.m_32,
				m_31*r.m_13 + m_32*r.m_23 + m_33*r.m_33
				);
	*this = out;
	return *this;
}


/*---------------------------------------------------------------------+\

 * ScalarMultiply -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::ScalarMultiply
		(
		GFLOAT	fScale
		)
{
	CMatrix3x3	out(
				m_11*fScale,	m_12*fScale,	m_13*fScale,
				m_21*fScale,	m_22*fScale,	m_23*fScale,
				m_31*fScale,	m_32*fScale,	m_33*fScale
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * Transpose -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::Transpose
		(
		void
		)
{
	CMatrix3x3	out(
				m_11,	m_21,	m_31,
				m_12,	m_22,	m_32,
				m_13,	m_23,	m_33
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * Normalize -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::Normalize
		(
		void
		)
{
	if ( m_33 != GFLOAT_0 )
	{
		GFLOAT	fInv = GFLOAT_1 / m_33;
		CMatrix3x3	out(
			m_11 * fInv,	m_21 * fInv,	m_31 * fInv,
			m_12 * fInv,	m_22 * fInv,	m_32 * fInv,
			m_13 * fInv,	m_23 * fInv,	m_33 * fInv
			);
		return out;
	}
	else
	{
		return *this;
	}
}


/*---------------------------------------------------------------------+\

 * Determinant -

\+---------------------------------------------------------------------*/
GFLOAT	CMatrix3x3::Determinant
		(
		void
		) const
{
	return	m_11 * ( m_22 * m_33 - m_32 * m_23 )
		+	m_21 * ( m_32 * m_13 - m_12 * m_33 )
		+	m_31 * ( m_12 * m_23 - m_22 * m_13 );
}

/*---------------------------------------------------------------------+\

 * Reciprocal -

\+---------------------------------------------------------------------*/
GFLOAT	CMatrix3x3::Reciprocal
		(
		void
		)
{
	GFLOAT	v = Determinant();
	if ( GFLOAT_0 != v )
		return GFLOAT_1 / v;
	else
		return 0;
}


/*---------------------------------------------------------------------+\

 * Add -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::Add
		(
		ConstCMatrix3x3Ref r
		)
{
	CMatrix3x3	out(
				m_11 + r.m_11,	m_12 + r.m_12,	m_13 + r.m_13,
				m_21 + r.m_21,	m_22 + r.m_22,	m_23 + r.m_23,
				m_31 + r.m_31,	m_32 + r.m_32,	m_33 + r.m_33
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * SelfRotate -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfRotate
		(
		GFLOAT	fAngle
		)
{
	*this *= _Rotate( fAngle );
}


/*---------------------------------------------------------------------+\

 * RotateAt -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfRotateAt
		(
		GFLOAT,	// fAngle,
		GFLOAT,	// xCenter,
		GFLOAT	// yCenter
		)
{
}


/*---------------------------------------------------------------------+\

 * Scale -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfScale
		(
		GFLOAT	xScale,
		GFLOAT	yScale
		)
{
	*this *= _Scale( xScale, yScale );
}

/*---------------------------------------------------------------------+\

 * ScaleAt -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfScaleAt
		(
		GFLOAT, //xScale,
		GFLOAT, //yScale,
		GFLOAT, //xCenter,
		GFLOAT //yCenter
		)
{
}


/*---------------------------------------------------------------------+\

 * Translate -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::SelfTranslate
		(
		GFLOAT xOffset,
		GFLOAT yOffset
		)
{
	m_31 += xOffset;
	m_32 += yOffset;
}




/*---------------------------------------------------------------------+\

 * Transform -

\+---------------------------------------------------------------------*/
void	CMatrix3x3::Transform
		(
		GFLOAT &xOut,
		GFLOAT &yOut,
		GFLOAT xIn,
		GFLOAT yIn
		)
{
	GFLOAT	x = m_11*xIn + m_21*yIn + m_31;
	GFLOAT	y = m_12*xIn + m_22*yIn + m_32;
	GFLOAT	w = m_13*xIn + m_23*yIn + m_33;

	if ( GFLOAT_0 == w  ||  GFLOAT_1 == w )
	{
		xOut = x;
		yOut = y;
	}
	else
	{
		xOut = x / w;
		yOut = y / w;
	}
}




/*---------------------------------------------------------------------+\

 * _Identity -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Identity
		(
		void
		)
{
	CMatrix3x3	out
				(
				GFLOAT_1,	GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_1,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _ReflectX -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_ReflectX
		(
		void
		)
{
	CMatrix3x3	out
				(
				GFLOAT_1,	GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_NEG1,GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _ReflectY -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_ReflectY
		(
		void
		)
{
	CMatrix3x3	out
				(
				GFLOAT_NEG1,GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_1,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * _Scale -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Scale
		(
		GFLOAT fScale
		)
{
	CMatrix3x3	out
				(
				fScale,		GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	fScale,		GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _Scale -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Scale
		(
		GFLOAT xScale,
		GFLOAT yScale
		)
{
	CMatrix3x3	out
				(
				xScale,		GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	yScale,		GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _Skew -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Skew
		(
		GFLOAT xSkew,
		GFLOAT ySkew
		)
{
	CMatrix3x3	out
				(
				GFLOAT_1,	ySkew,		GFLOAT_0,
				xSkew,		GFLOAT_1,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _Translate -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Translate
		(
		GFLOAT x,
		GFLOAT y
		)
{
	CMatrix3x3	out
				(
				GFLOAT_1,	GFLOAT_0,	GFLOAT_0,
				GFLOAT_0,	GFLOAT_1,	GFLOAT_0,
				x,			y,			GFLOAT_1
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * _Rotate -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_Rotate
		(
		GFLOAT fRadians
		)
{
	GFLOAT	fSin = sinf( fRadians );
	GFLOAT	fCos = cosf( fRadians );
	CMatrix3x3	out
				(
				fCos,		-fSin,		GFLOAT_0,
				fSin,		fCos,		GFLOAT_0,
				GFLOAT_0,	GFLOAT_0,	GFLOAT_1
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * _QuadFromSquare -

\+---------------------------------------------------------------------*/
CMatrix3x3
CMatrix3x3::_QuadFromSquare
		(
		GFLOAT	x1,	GFLOAT	y1,
		GFLOAT	x2,	GFLOAT	y2,
		GFLOAT	x3,	GFLOAT	y3,
		GFLOAT	x4,	GFLOAT	y4
		)
{
	CMatrix3x3	out;

	GFLOAT	dx = x1 - x2 + x3 - x4;
	GFLOAT	dy = y1 - y2 + y3 - y4;

	out.m_33 = GFLOAT_1;

	if ( GFLOAT_0 == dx  &&  GFLOAT_0 == dy )
	{
		out.m_11 = x2 - x1;
		out.m_12 = y2 - y1;
		out.m_13 = GFLOAT_0;

		out.m_21 = x3 - x2;
		out.m_22 = y3 - y2;
		out.m_23 = GFLOAT_0;

		out.m_31 = x1;
		out.m_32 = y1;
		out.m_33 = GFLOAT_1;
	}
	else
	{
		GFLOAT	dx1 = x2 - x3;
		GFLOAT	dy1 = y2 - y3;
		GFLOAT	dx2 = x4 - x3;
		GFLOAT	dy2 = y4 - y3;
		GFLOAT	den = dx1 * dy2 - dx2 * dy1;

		if ( GFLOAT_0 == den )
		{
			out = _Identity();
		}
		else
		{
			GFLOAT	u = (dx * dy2 - dy * dx2) / den;
			GFLOAT	v = (dy * dx1 - dx * dy1) / den;
			out.m_11 = x2 - x1 + u * x2;
			out.m_12 = y2 - y1 + u * y2;
			out.m_13 = u;

			out.m_21 = x4 - x1 + v * x4;
			out.m_22 = y4 - y1 + v * y4;
			out.m_23 = v;

			out.m_31 = x1;
			out.m_32 = y2;
			out.m_33 = GFLOAT_1;
		}
	}
	return out;
}

/*---------------------------------------------------------------------+\

 * _SquareFromQuad -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_SquareFromQuad
		(
		GFLOAT	x1,	GFLOAT	y1,
		GFLOAT	x2,	GFLOAT	y2,
		GFLOAT	x3,	GFLOAT	y3,
		GFLOAT	x4,	GFLOAT	y4
		)
{
	CMatrix3x3	out = _QuadFromSquare( x1, y1, x2, y2,
										x3, y3, x4, y4 );
	if ( out != _Identity() )
		out.SelfInvert();
	return out;
}

/*---------------------------------------------------------------------+\

 * _QuadFromQuad -

\+---------------------------------------------------------------------*/
CMatrix3x3
		CMatrix3x3::_QuadFromQuad
		(
		GFLOAT sx1, GFLOAT sy1,
		GFLOAT sx2, GFLOAT sy2,
		GFLOAT sx3, GFLOAT sy3,
		GFLOAT sx4, GFLOAT sy4,
		GFLOAT dx1, GFLOAT dy1,
		GFLOAT dx2, GFLOAT dy2,
		GFLOAT dx3, GFLOAT dy3,
		GFLOAT dx4, GFLOAT dy4
		)
{
	CMatrix3x3	out = _SquareFromQuad( sx1, sy1, sx2, sy2,
									sx3, sy3, sx4, sy4 );
	if ( out != _Identity() )
	{
		CMatrix3x3	p;
		p = _QuadFromSquare( dx1, dy1, dx2, dy2,
							dx3, dy3, dx4, dy4 );
		if ( p != _Identity() )
			out *= p;
	}
	return out;
}



/*---------------------------------------------------------------------+\

 * operator* -

\+---------------------------------------------------------------------*/
CMatrix3x3
		operator*
		(
		ConstCMatrix3x3Ref A,
		ConstCMatrix3x3Ref B
		)
{
	return CMatrix3x3(A) *= B;
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


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

