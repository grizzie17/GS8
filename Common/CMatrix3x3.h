/*==================================================================*//**
*
*	@file	CMatrix3x3.h
*	@brief	3 x 3 matrix to calculate 2d transformations
*
*	@note
		In general the matrix can be represented as:

		A B U
		C D V
		X Y W

		A, B, C & D manipulate scale, rotation, and skew.
		Change A & D to adjust scale.
		Change C & B to affect skew.
		Change X & Y to affect translation (shift by values)
		U, V & W should probably left alone, because that can get strange.
*
*//*===================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	07-Dec-2011			J.Griswold
		Add support for planar perspective
	20-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add Set and Get functions
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	14-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CMatrix3x3
#define _H_CMatrix3x3
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
typedef class CMatrix3x3*       CMatrix3x3Ptr;
typedef class CMatrix3x3&       CMatrix3x3Ref;
typedef const class CMatrix3x3& ConstCMatrix3x3Ref;
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

class COMMON_CLASS CMatrix3x3
{
    //	class lifecycle  ----------------------------------------------------
public:
    CMatrix3x3();                        // construct identity matrix
    CMatrix3x3( ConstCMatrix3x3Ref r );  // copy constructor
    CMatrix3x3( GFLOAT m11, GFLOAT m12, GFLOAT m13, GFLOAT m21, GFLOAT m22,
            GFLOAT m23, GFLOAT m31, GFLOAT m32, GFLOAT m33 );
    CMatrix3x3( GFLOAT sX, GFLOAT sY, GFLOAT sZ );
    CMatrix3x3( GFLOAT m11, GFLOAT m12,  // 0.0,
            GFLOAT m21, GFLOAT m22,      // 0.0,
            GFLOAT ofX, GFLOAT ofY );    // 1.0
    virtual ~CMatrix3x3();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    CMatrix3x3Ref
    operator=( ConstCMatrix3x3Ref r );  // assignment

    void
    Set( ConstCMatrix3x3Ref r );
    void
    Set( GFLOAT m11, GFLOAT m12, GFLOAT m13, GFLOAT m21, GFLOAT m22, GFLOAT m23,
            GFLOAT m31, GFLOAT m32, GFLOAT m33 );
    void
    Get( GFLOAT* m11, GFLOAT* m12, GFLOAT* m13, GFLOAT* m21, GFLOAT* m22,
            GFLOAT* m23, GFLOAT* m31, GFLOAT* m32, GFLOAT* m33 ) const;

    bool
    Equals( ConstCMatrix3x3Ref r ) const;
    bool
    IsIdentity( void ) const;
    bool
    IsAffine( void ) const;
    bool
    operator==( ConstCMatrix3x3Ref r ) const;
    bool
    operator!=( ConstCMatrix3x3Ref r ) const;
    CMatrix3x3
    ScalarMultiply( GFLOAT fScale );
    CMatrix3x3
    Add( ConstCMatrix3x3Ref r );
    CMatrix3x3
    Transpose( void );
    CMatrix3x3
    Normalize( void );
    GFLOAT
    Determinant( void ) const;
    GFLOAT
    Reciprocal( void );
    void
    SelfInvert( void );
    CMatrix3x3Ref
    SelfMultiply( ConstCMatrix3x3Ref r );
    void
    SelfRotate( GFLOAT fAngle );
    void
    SelfRotateAt( GFLOAT fAngle, GFLOAT xCenter, GFLOAT yCenter );
    void
    SelfScale( GFLOAT xScale, GFLOAT yScale );
    void
    SelfScaleAt( GFLOAT xScale, GFLOAT yScale, GFLOAT xCenter, GFLOAT yCenter );
    void
    SelfTranslate( GFLOAT xOffset, GFLOAT yOffset );

    void
    Transform( GFLOAT& xOut, GFLOAT& yOut, GFLOAT xIn, GFLOAT yIn );

    CMatrix3x3Ref
    operator*=( ConstCMatrix3x3Ref r );

    static CMatrix3x3
    _Identity( void );
    static CMatrix3x3
    _Scale( GFLOAT fScale );
    static CMatrix3x3
    _Scale( GFLOAT xScale, GFLOAT yScale );
    static CMatrix3x3
    _ReflectX( void );  // reflect about X axis
    static CMatrix3x3
    _ReflectY( void );  // reflect about Y axis
    static CMatrix3x3
    _Translate( GFLOAT x, GFLOAT y );
    static CMatrix3x3
    _Skew( GFLOAT x, GFLOAT y );
    static CMatrix3x3
    _Rotate( GFLOAT fRadians );
    static CMatrix3x3
    _QuadFromSquare( GFLOAT x1, GFLOAT y1, GFLOAT x2, GFLOAT y2, GFLOAT x3,
            GFLOAT y3, GFLOAT x4, GFLOAT y4 );
    static CMatrix3x3
    _SquareFromQuad( GFLOAT x1, GFLOAT y1, GFLOAT x2, GFLOAT y2, GFLOAT x3,
            GFLOAT y3, GFLOAT x4, GFLOAT y4 );
    static CMatrix3x3
    _QuadFromQuad( GFLOAT sx1, GFLOAT sy1, GFLOAT sx2, GFLOAT sy2, GFLOAT sx3,
            GFLOAT sy3, GFLOAT sx4, GFLOAT sy4, GFLOAT dx1, GFLOAT dy1,
            GFLOAT dx2, GFLOAT dy2, GFLOAT dx3, GFLOAT dy3, GFLOAT dx4,
            GFLOAT dy4 );

    static const CMatrix3x3 kIdentity;

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

    GFLOAT m_11;
    GFLOAT m_12;
    GFLOAT m_13;
    GFLOAT m_21;
    GFLOAT m_22;
    GFLOAT m_23;
    GFLOAT m_31;
    GFLOAT m_32;
    GFLOAT m_33;

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
CMatrix3x3
operator*( ConstCMatrix3x3Ref A, ConstCMatrix3x3Ref B );


/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


inline bool
CMatrix3x3::operator==( ConstCMatrix3x3Ref r ) const
{
    return Equals( r );
}

inline bool
CMatrix3x3::operator!=( ConstCMatrix3x3Ref r ) const
{
    return ! Equals( r );
}

inline CMatrix3x3Ref
CMatrix3x3::operator*=( ConstCMatrix3x3Ref r )
{
    return SelfMultiply( r );
}


}}  // namespace Yogi::Common


#endif /* _H_CMatrix3x3 */
