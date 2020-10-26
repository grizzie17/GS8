//#include "stdafx.h"

#include "gtest/gtest.h"

// #include "iggy.h"

#include <string.h>

#include "CCharString.h"


using namespace Yogi::Core;

TEST( CCharStringTest, it_should_load_pointer_and_count )
{
    const char sample[] = "This is a sample string";

    CCharString str( sample );

    // make sure that we are comparing the pointer not the string
    ASSERT_NE( (void*)str.Pointer(), (void*)sample );
    ASSERT_EQ( str.Length(), ( strlen( sample ) ) );
}

TEST( CCharStringTest, it_should_be_able_to_identify_equality )
{
    const char sample1[] = "sample";
    const char sample2[] = "sample";

    CCharString t1( sample1 );
    CCharString t2( sample2 );

    ASSERT_TRUE( t1 == t2 );
    ASSERT_TRUE( t1 == sample2 );
    ASSERT_TRUE( sample1 == t1 );
}

TEST( CCharStringTest, it_should_identify_the_comparitive_operators )
{
    const char s1[] = "abc";
    const char s2[] = "def";

    CCharString t1( s1 );
    CCharString t2( s2 );

    ASSERT_TRUE( t1 < t2 );
    ASSERT_TRUE( t1 < s2 );
    ASSERT_TRUE( s1 < t2 );

    ASSERT_TRUE( t1 <= t2 );
    ASSERT_TRUE( t1 <= s2 );
    ASSERT_TRUE( s1 <= t2 );

    ASSERT_TRUE( t2 > t1 );
    ASSERT_TRUE( t2 > s1 );
    ASSERT_TRUE( s2 > t1 );

    ASSERT_TRUE( t2 >= t1 );
    ASSERT_TRUE( t2 >= s1 );
    ASSERT_TRUE( s2 >= t1 );

    ASSERT_TRUE( t2 != t1 );
    ASSERT_TRUE( t2 != s1 );
    ASSERT_TRUE( s2 != t1 );
}

TEST( CCharStringTest, it_should_compare_ignoring_case )
{
    const char  s1[] = "sample";
    CCharString t1( "SAMPLE" );

    ASSERT_EQ( t1.CompareIgnoreCase( s1 ), 0 );
}

TEST( CCharStringTest, it_should_allow_appending_strings )
{
    CCharString t1( "Sample" );
    t1.Append( "String" );

    ASSERT_STREQ( t1.Pointer(), ( "SampleString" ) );
}

TEST( CCharStringTest, it_should_allow_appending_strings_via_operator )
{
    CCharString t1( "Sample" );
    t1 += "String";

    ASSERT_STREQ( t1.Pointer(), ( "SampleString" ) );
}

TEST( CCharStringTest, allow_loading_using_formatted_strings )
{
    CCharString t1;
    t1.Format( "Data = %ld", 123 );

    ASSERT_STREQ( t1.Pointer(), ( "Data = 123" ) );
}

TEST( CCharStringTest, allow_appending_strings_using_formatted_strings )
{
    CCharString t1( "Data:" );
    t1.AppendFormat( " %ld", 123 );

    ASSERT_STREQ( t1.Pointer(), ( "Data: 123" ) );
}

TEST( CCharStringTest, allow_acting_like_descriptor )
{
    CCharString     t1( "string" );
    CCharDescriptor d1 = t1;

    // notice that d1 is actually pointing to t1's data
    ASSERT_EQ( (void*)t1.Pointer(), ( (void*)d1.Pointer() ) );
}

TEST( CCharStringTest, support_case_conversion )
{
    CCharString t1( "Sample" );

    t1.ConvertUppercase();
    ASSERT_TRUE( t1 == "SAMPLE" );

    t1.ConvertLowercase();
    ASSERT_TRUE( t1 == "sample" );
}

TEST( CCharStringTest, std_string_assign_from )
{
    std::string s( "Sample" );
    CCharString t = s;

    ASSERT_TRUE( t == "Sample" );
    ASSERT_TRUE( t == s );
}
