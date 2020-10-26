/*---------------------------------------------------------------------+\
|
|	CMatrix3x3d.h  --  3 x 3 matrix to calculate 2d transformations
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:

		In general the matrix can be represented as:

		A B U
		C D V
		X Y W

		A, B, C & D manipulate scale, rotation, and skew.
		Change A & D to adjust scale.
		Change C & B to affect skew.
		Change X & Y to affect translation (shift by values)
		U, V & W should probably left alone, because that can get strange.


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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	14-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMatrix3x3d
#define _H_CMatrix3x3d
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UDeclCommon.h"
#include "UFloat.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
typedef class CMatrix3x3d*       CMatrix3x3dPtr;
typedef class CMatrix3x3d&       CMatrix3x3dRef;
typedef const class CMatrix3x3d& ConstCMatrix3x3dRef;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class COMMON_CLASS CMatrix3x3d
{
    //	class lifecycle  ----------------------------------------------------
public:
    CMatrix3x3d();                         // construct identity matrix
    CMatrix3x3d( ConstCMatrix3x3dRef r );  // copy constructor
    CMatrix3x3d( double m11, double m12, double m13, double m21, double m22,
            double m23, double m31, double m32, double m33 );
    CMatrix3x3d( double sX, double sY, double sZ );
    CMatrix3x3d( double m11, double m12,  // 0.0,
            double m21, double m22,       // 0.0,
            double ofX, double ofY );     // 1.0
    virtual ~CMatrix3x3d();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    CMatrix3x3dRef
    operator=( ConstCMatrix3x3dRef r );  // assignment

    void
    Set( ConstCMatrix3x3dRef r );
    void
    Set( double m11, double m12, double m13, double m21, double m22, double m23,
            double m31, double m32, double m33 );
    void
    Get( double* m11, double* m12, double* m13, double* m21, double* m22,
            double* m23, double* m31, double* m32, double* m33 ) const;

    bool
    Equals( ConstCMatrix3x3dRef r ) const;
    bool
    operator==( ConstCMatrix3x3dRef r ) const;
    void
    Invert( void );
    CMatrix3x3dRef
    Multiply( ConstCMatrix3x3dRef r );
    CMatrix3x3d
    ScalarMultiply( double fScale );
    CMatrix3x3d
    Add( ConstCMatrix3x3dRef r );
    CMatrix3x3d
    Transpose( void );
    void
    Rotate( double fAngle );
    void
    RotateAt( double fAngle, double xCenter, double yCenter );
    void
    Scale( double xScale, double yScale );
    void
    ScaleAt( double xScale, double yScale, double xCenter, double yCenter );
    void
    Translate( double xOffset, double yOffset );

    void
    Transform( double& xOut, double& yOut, double xIn, double yIn );

    CMatrix3x3dRef
    operator*=( ConstCMatrix3x3dRef r );

    static CMatrix3x3d
    _Identity( void );
    static CMatrix3x3d
    _Scale( double fScale );
    static CMatrix3x3d
    _Scale( double xScale, double yScale );
    static CMatrix3x3d
    _ReflectX( void );  // reflect about X axis
    static CMatrix3x3d
    _ReflectY( void );  // reflect about Y axis
    static CMatrix3x3d
    _Translate( double x, double y );
    static CMatrix3x3d
    _Rotate( double fRadians );

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

    // clang-format off
	double m_11; double m_12; double m_13;
	double m_21; double m_22; double m_23;
	double m_31; double m_32; double m_33;
    // clang-format on

private:
    //	private functions  --------------------------------------------------

    //	private data  -------------------------------------------------------

    //============================== Overrides ==============================
    // -- delete this section if this is a root class --
    //	root
    //	BaseClass-1
    //	BaseClass
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
CMatrix3x3d
operator*( ConstCMatrix3x3dRef A, ConstCMatrix3x3dRef B );


/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


inline bool
CMatrix3x3d::operator==( ConstCMatrix3x3dRef r ) const
{
    return Equals( r );
}

inline CMatrix3x3dRef
CMatrix3x3d::operator*=( ConstCMatrix3x3dRef r )
{
    return Multiply( r );
}


}}  // namespace Yogi::Common


#endif /* _H_CMatrix3x3d */
