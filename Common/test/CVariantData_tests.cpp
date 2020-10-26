
#define __FILE_BASENAME__ CVariantData

#include "CVariantData.h"

#include "EqualsFloat.h"
#include "iggy.h"


// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi;
using namespace Yogi::Core;
using namespace Yogi::Common;

TEST( CVariantDataTests, it_can_hold_float_data )
{
    CVariantData v( 1.0 );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_FLOAT ) );
}

TEST( CVariantDataTests, it_can_hold_integer_data )
{
    CVariantData v( 1L );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_INTEGER ) );
}

TEST( CVariantDataTests, it_can_hold_character_string_data )
{
    CVariantData v( "string" );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_STRING ) );
}

TEST( CVariantDataTests, it_can_hold_boolean_data )
{
    CVariantData v( true );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_BOOL ) );
}

TEST( CVariantDataTests, it_can_hold_color_data )
{
    CColor       c( 255, 127, 63 );
    CVariantData v( c );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_COLOR ) );
}

TEST( CVariantDataTests, it_can_hold_datetime_data )
{
    CDateTime    d( "20010911T100301" );
    CVariantData v( d );

    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_DATETIME ) );
}

TEST( CVariantDataTests, it_can_change_type )
{
    CVariantData v;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_UNDEFINED ) );

    v = 1.0f;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_FLOAT ) );

    v = 1L;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_INTEGER ) );

    v = "string";
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_STRING ) );

    CDateTime d( 2000, 1, 1, 13, 0, 0 );
    v = d;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_DATETIME ) );

    CColor c( "green" );
    v = c;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_COLOR ) );

    v = true;
    ASSERT_EQ( v.GetType(), Equals( CVariantData::T_BOOL ) );
}

TEST( CVariantDataTests, it_can_compare_equality )
{
    CVariantData v( 1.0f );

    ASSERT_TRUE( v == 1.0f );
    ASSERT_TRUE( v == "1.0" );

    v = "string";
    ASSERT_TRUE( v == "string" );

    CColor c( "blue" );
    v = c;
    ASSERT_TRUE( v == "blue" );

    v = true;
    ASSERT_TRUE( v == true );

    CDateTime d( 2000, 1, 1, 13, 0, 0 );
    v = d;
    ASSERT_TRUE( v == d );

    // compare with 'undefined' which should act like zero or null
    CVariantData u;

    v = "";
    ASSERT_TRUE( v == u );
    ASSERT_TRUE( u == v );
    ASSERT_TRUE( u == "" );

    v = 0L;
    ASSERT_TRUE( v == u );
    ASSERT_TRUE( u == v );

    v = 0.0f;
    ASSERT_TRUE( v == u );
    ASSERT_TRUE( u == v );
}

TEST( CVariantDataTests, it_can_compare_lessthan )
{
    CVariantData v1( 1.0f );
    CVariantData v2( 2.0f );

    ASSERT_TRUE( v1 < v2 );

    CVariantData u;  // undefined

    ASSERT_TRUE( u < v1 );

    v1 = false;
    v2 = true;
    ASSERT_TRUE( v1 < v2 );
    ASSERT_TRUE( u < v2 );

    v1 = "abc";
    v2 = "def";
    ASSERT_TRUE( v1 < v2 );
    ASSERT_TRUE( u < v2 );
    ASSERT_TRUE( v2 < v1 );
    ASSERT_TRUE( v1 < u );
}

TEST( CVariantDataTests, it_can_convert_types )
{
    CVariantData v( 1.0f );

    CCharString s = v.GetValueCCharString();

    ASSERT_TRUE( s == "1.000000" );
}

TEST( CVariantDataTests, it_deals_correctly_with_units )
{
    CVariantData    v( 32.0 );
    CUnitsOfMeasure uF( "fahrenheit" );
    CUnitsOfMeasure uC( "centigrade" );

    ASSERT_GT( uF.GetUnits(), 0 );
    ASSERT_GT( uC.GetUnits(), 0 );

    v.SetUnits( uF );

    GFLOAT f = v.GetValueFloatAsUnits( uC );
    ASSERT_FLOAT_EQ( f, 0.0 );
}
