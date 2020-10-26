#define __FILE_BASENAME__ CMatrix3x3

#include "CMatrix3x3.h"


#include "EqualsFloat.h"

#include "iggy.h"


// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi::Common;

TEST( CMatrix3x3Test, default_init_should_be_identity )
{
    CMatrix3x3 m;

    GFLOAT m1, m2, m3, m4, m5, m6, m7, m8, m9;

    m.Get( &m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9 );

    ASSERT_FLOAT_EQ( m1, ( 1.0f ) );
    ASSERT_FLOAT_EQ( m5, ( 1.0f ) );
    ASSERT_FLOAT_EQ( m9, ( 1.0f ) );

    ASSERT_FLOAT_EQ( m2, ( 0.0f ) );
    ASSERT_FLOAT_EQ( m3, ( 0.0f ) );
    ASSERT_FLOAT_EQ( m4, ( 0.0f ) );
    ASSERT_FLOAT_EQ( m6, ( 0.0f ) );
    ASSERT_FLOAT_EQ( m7, ( 0.0f ) );
    ASSERT_FLOAT_EQ( m8, ( 0.0f ) );
}

TEST( CMatrix3x3Test, it_can_tell_if_its_identity )
{
    CMatrix3x3 m;

    ASSERT_TRUE( m.IsIdentity() );
}

TEST( CMatrix3x3Test, it_should_be_able_to_compare_equality )
{
    CMatrix3x3 m1( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f, 3.0f, 1.0f );

    CMatrix3x3 m2( m1 );

    ASSERT_TRUE( m1 == m2 );

    m2.SelfRotate( 3.14f * 0.25f );

    ASSERT_TRUE( m1 != m2 );
}

TEST( CMatrix3x3Test, it_can_apply_translation )
{
    CMatrix3x3 m1;
    CMatrix3x3 m2( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f, 3.0f, 1.0f );

    m1.SelfTranslate( 5.0f, 3.0f );

    ASSERT_TRUE( m1 == m2 );
}

TEST( CMatrix3x3Test, it_can_apply_rotation )
{
    CMatrix3x3 m1;

    const float r = 3.14f * 0.25f;  // 45 degrees
    float       fSin = sinf( r );
    float       fCos = cosf( r );
    CMatrix3x3  m2( fCos, -fSin, 0.0f, fSin, fCos, 0.0f, 0.0f, 0.0f, 1.0f );

    m1.SelfRotate( r );

    ASSERT_TRUE( m1 == m2 );
}

TEST( CMatrix3x3Test, it_can_tell_if_its_affine )
{
    CMatrix3x3 m;

    m *= CMatrix3x3::_Rotate( 3.14f * 0.5f );
    m *= CMatrix3x3::_Translate( 5.0f, 3.0f );

    ASSERT_TRUE( m.IsAffine() );

    m = m.Transpose();

    ASSERT_FALSE( m.IsAffine() );
}

TEST( CMatrix3x3Test, it_should_allow_assignment )
{
    CMatrix3x3 m1( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f, 3.0f, 1.0f );

    CMatrix3x3 m2;

    m2 = m1;

    ASSERT_TRUE( m2 == m1 );
}

TEST( CMatrix3x3Test, it_should_apply_scale )
{
    CMatrix3x3 m1;

    m1.SelfScale( 2.0f, 2.0f );

    CMatrix3x3 m2( 2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f );

    ASSERT_TRUE( m1 == m2 );
}

TEST( CMatrix3x3Test, it_can_perform_transformations_on_points )
{
    CMatrix3x3 m1( 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 5.0f, 3.0f, 1.0f );
    GFLOAT     x = 0.0f;
    GFLOAT     y = 0.0f;

    GFLOAT x1;
    GFLOAT y1;

    m1.Transform( x1, y1, x, y );

    ASSERT_FLOAT_EQ( x1, ( 5.0f ) );
    ASSERT_FLOAT_EQ( y1, ( 3.0f ) );
}
