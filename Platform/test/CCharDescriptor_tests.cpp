#define __FILE_BASENAME__ CCharDescriptor

//

#include "iggy.h"

#include "CCharDescriptor.h"

using namespace Yogi::Core;


Context( CCharDescriptor_class ) {
Spec( it_should_load_pointer_and_count )
{
    const char sample[] = "This is a sample string";

    CCharDescriptor str( sample, sizeof( sample ) - 1 );

    // make sure that we are comparing the original string
    AssertThat( (void*)str.Pointer(), (void*)sample );
    AssertThat( str.Length(), ( strlen( sample ) ) );
}

Spec( it_should_be_able_to_identify_equality )
{
    const char sample1[] = "sample";
    const char sample2[] = "sample";

    CCharDescriptor t1( sample1, sizeof( sample1 ) - 1 );
    CCharDescriptor t2( sample2, sizeof( sample2 ) - 1 );

    AssertThat( ( t1 == t2 ), IsTrue() );
    AssertThat( ( t1 == sample2 ), IsTrue() );
    AssertThat( ( sample1 == t1 ), IsTrue() );
}

Spec( it_should_identify_the_comparitive_operators )
{
    const char s1[] = "abc";
    const char s2[] = "def";

    CCharDescriptor t1( s1, sizeof( s1 ) - 1 );
    CCharDescriptor t2( s2, sizeof( s2 ) - 1 );

    AssertThat( ( t1 < t2 ), IsTrue() );
    AssertThat( ( t1 < s2 ), IsTrue() );
    AssertThat( ( s1 < t2 ), IsTrue() );

    AssertThat( ( t1 <= t2 ), IsTrue() );
    AssertThat( ( t1 <= s2 ), IsTrue() );
    AssertThat( ( s1 <= t2 ), IsTrue() );

    AssertThat( ( t2 > t1 ), IsTrue() );
    AssertThat( ( t2 > s1 ), IsTrue() );
    AssertThat( ( s2 > t1 ), IsTrue() );

    AssertThat( ( t2 >= t1 ), IsTrue() );
    AssertThat( ( t2 >= s1 ), IsTrue() );
    AssertThat( ( s2 >= t1 ), IsTrue() );

    AssertThat( ( t2 != t1 ), IsTrue() );
    AssertThat( ( t2 != s1 ), IsTrue() );
    AssertThat( ( s2 != t1 ), IsTrue() );
}

Spec( it_should_compare_ignoring_case )
{
    const char      s1[] = "sample";
    const char      s2[] = "SAMPLE";
    CCharDescriptor t1( s1, sizeof( s1 ) - 1 );

    AssertThat( t1.CompareIgnoreCase( s2 ), ( 0 ) );
}

Spec( it_needs_to_handle_constant_strings )
{
    const CCharDescriptor t1( "string literal" );
    const char            s2[] = "string constant";
    const CCharDescriptor t2( s2 );

    AssertThat( t1 == "string literal", IsTrue() );
    AssertThat( t2 == s2, IsTrue() );
}
};  // Context(CCharDescriptor_class)
