/*---------------------------------------------------------------------+\
|
|	CMatrix3x3d.cpp  --  3 x 3 matrix to calculate 2d transformations
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
#include <math.h>

#include "CMatrix3x3d.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_COMMON_BEGIN

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

 * CMatrix3x3d - constructor

\+---------------------------------------------------------------------*/
CMatrix3x3d::CMatrix3x3d
		(
		void
		)
		: m_11( 1.0 ), m_12( 0.0 ), m_13( 0.0 )
		, m_21( 0.0 ), m_22( 1.0 ), m_23( 0.0 )
		, m_31( 0.0 ), m_32( 0.0 ), m_33( 1.0 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3d - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3d::CMatrix3x3d
		(
		ConstCMatrix3x3dRef	r
		)
		: m_11( r.m_11 ), m_12( r.m_12 ), m_13( r.m_13 )
		, m_21( r.m_21 ), m_22( r.m_22 ), m_23( r.m_23 )
		, m_31( r.m_31 ), m_32( r.m_32 ), m_33( r.m_33 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3d - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3d::CMatrix3x3d
		(
		double m11, double m12, double m13,
		double m21, double m22, double m23,
		double m31, double m32, double m33
		)
		: m_11( m11 ), m_12( m12 ), m_13( m13 )
		, m_21( m21 ), m_22( m22 ), m_23( m23 )
		, m_31( m31 ), m_32( m32 ), m_33( m33 )
{
}

/*---------------------------------------------------------------------+\

 * CMatrix3x3d - copy constructor

\+---------------------------------------------------------------------*/
CMatrix3x3d::CMatrix3x3d
		(
		double m11, double m12,
		double m21, double m22,
		double ofX, double ofY
		)
		: m_11( m11 ), m_12( m12 ), m_13( 0.0 )
		, m_21( m21 ), m_22( m22 ), m_23( 0.0 )
		, m_31( ofX ), m_32( ofY ), m_33( 1.0 )
{
}

/*---------------------------------------------------------------------+\

 * ~CMatrix3x3d - destructor

\+---------------------------------------------------------------------*/
CMatrix3x3d::~CMatrix3x3d
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
CMatrix3x3dRef
		CMatrix3x3d::operator=
		(
		ConstCMatrix3x3dRef	r
		)
{
	Set( r );
	return *this;
}


/*----------------------------------------------------------------------+\

 * Set - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Set
		(
		ConstCMatrix3x3dRef	r
		)
{
	m_11 = r.m_11;	m_12 = r.m_12;	m_13 = r.m_13;
	m_21 = r.m_21;	m_22 = r.m_22;	m_23 = r.m_23;
	m_31 = r.m_31;	m_32 = r.m_32;	m_33 = r.m_33;
}


/*----------------------------------------------------------------------+\

 * Set - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Set
		(
		double m11, double m12, double m13,
		double m21, double m22, double m23,
		double m31, double m32, double m33
		)
{
	m_11 = m11;	m_12 = m12;	m_13 = m13;
	m_21 = m21;	m_22 = m22;	m_23 = m23;
	m_31 = m31;	m_32 = m32;	m_33 = m33;
}

/*----------------------------------------------------------------------+\

 * Get - assignment values

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Get
		(
		double* m11, double* m12, double* m13,
		double* m21, double* m22, double* m23,
		double* m31, double* m32, double* m33
		) const
{
	*m11 = m_11;	*m12 = m_12;	*m13 = m_13;
	*m21 = m_21;	*m22 = m_22;	*m23 = m_23;
	*m31 = m_31;	*m32 = m_32;	*m33 = m_33;
}

/*---------------------------------------------------------------------+\

 * Equals -

\+---------------------------------------------------------------------*/
bool	CMatrix3x3d::Equals
		(
		ConstCMatrix3x3dRef r
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

 * Invert -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Invert
		(
		void
		)
{
}


/*---------------------------------------------------------------------+\

 * Multiply -

\+---------------------------------------------------------------------*/
CMatrix3x3dRef
		CMatrix3x3d::Multiply
		(
		ConstCMatrix3x3dRef r
		)
{
	CMatrix3x3d	out(
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
CMatrix3x3d
		CMatrix3x3d::ScalarMultiply
		(
		double	fScale
		)
{
	CMatrix3x3d	out(
				m_11*fScale,	m_12*fScale,	m_13*fScale,
				m_21*fScale,	m_22*fScale,	m_23*fScale,
				m_31*fScale,	m_32*fScale,	m_33*fScale
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * Transpose -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::Transpose
		(
		void
		)
{
	CMatrix3x3d	out(
				m_11,	m_21,	m_31,
				m_12,	m_22,	m_32,
				m_13,	m_23,	m_33
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * Add -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::Add
		(
		ConstCMatrix3x3dRef r
		)
{
	CMatrix3x3d	out(
				m_11 + r.m_11,	m_12 + r.m_12,	m_13 + r.m_13,
				m_21 + r.m_21,	m_22 + r.m_22,	m_23 + r.m_23,
				m_31 + r.m_31,	m_32 + r.m_32,	m_33 + r.m_33
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * Rotate -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Rotate
		(
		double	fAngle
		)
{
	double		fSin = ::sin( fAngle );
	double		fCos = ::cos( fAngle );
	CMatrix3x3d	tRot(
					fCos,	-fSin,
					fSin,	fCos,
					0,		0
					);
}


/*---------------------------------------------------------------------+\

 * RotateAt -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::RotateAt
		(
		double,	// fAngle,
		double,	// xCenter,
		double	// yCenter
		)
{
}


/*---------------------------------------------------------------------+\

 * Scale -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Scale
		(
		double,	// xScale,
		double	// yScale
		)
{
}

/*---------------------------------------------------------------------+\

 * ScaleAt -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::ScaleAt
		(
		double, //xScale,
		double, //yScale,
		double, //xCenter,
		double //yCenter
		)
{
}


/*---------------------------------------------------------------------+\

 * Translate -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Translate
		(
		double xOffset,
		double yOffset
		)
{
	m_31 += xOffset;
	m_32 += yOffset;
}



/*---------------------------------------------------------------------+\

 * Transform -

\+---------------------------------------------------------------------*/
void	CMatrix3x3d::Transform
		(
		double &xOut,
		double &yOut,
		double xIn,
		double yIn
		)
{
	double	x = m_11*xIn + m_21*yIn + m_31;
	double	y = m_12*xIn + m_22*yIn + m_32;
	double	w = m_13*xIn + m_23*yIn + m_33;

	xOut = x * w;
	yOut = y * w;
}




/*---------------------------------------------------------------------+\

 * _Identity -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_Identity
		(
		void
		)
{
	CMatrix3x3d	out
				(
				1.0,	0.0,	0.0,
				0.0,	1.0,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _ReflectX -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_ReflectX
		(
		void
		)
{
	CMatrix3x3d	out
				(
				1.0,	0.0,	0.0,
				0.0,	-1.0,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _ReflectY -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_ReflectY
		(
		void
		)
{
	CMatrix3x3d	out
				(
				-1.0,	0.0,	0.0,
				0.0,	1.0,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * _Scale -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_Scale
		(
		double fScale
		)
{
	CMatrix3x3d	out
				(
				fScale,	0.0,	0.0,
				0.0,	fScale,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _Scale -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_Scale
		(
		double xScale,
		double yScale
		)
{
	CMatrix3x3d	out
				(
				xScale,	0.0,	0.0,
				0.0,	yScale,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}

/*---------------------------------------------------------------------+\

 * _Translate -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_Translate
		(
		double x,
		double y
		)
{
	CMatrix3x3d	out
				(
				1.0,	0.0,	0.0,
				0.0,	1.0,	0.0,
				x,		y,		1.0
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * _Rotate -

\+---------------------------------------------------------------------*/
CMatrix3x3d
		CMatrix3x3d::_Rotate
		(
		double fRadians
		)
{
	double	fSin = ::sin( fRadians );
	double	fCos = ::cos( fRadians );
	CMatrix3x3d	out
				(
				fCos,	-fSin,	0.0,
				fSin,	fCos,	0.0,
				0.0,	0.0,	1.0
				);
	return out;
}


/*---------------------------------------------------------------------+\

 * operator* -

\+---------------------------------------------------------------------*/
CMatrix3x3d	operator*
		(
		ConstCMatrix3x3dRef A,
		ConstCMatrix3x3dRef B
		)
{
	return CMatrix3x3d(A) *= B;
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


NAMESPACE_COMMON_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

