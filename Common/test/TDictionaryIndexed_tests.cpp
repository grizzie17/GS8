
#include "CCharString.h"
#include "TDictionaryIndexed.h"

#include "iggy.h"

// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;

TEST( TDictionaryIndexedTests, it_should_initialize_as_empty )
{
    TDictionaryIndexed<CCharString, long> a;

    ASSERT_EQ( a.Length(), 0u );
}

TEST( TDictionaryIndexedTests,
        the_enumerator_should_behave_with_an_empty_array )
{
    TDictionaryIndexed<CCharString, long>           a;
    TDictionaryIndexedEnumerator<CCharString, long> e = a.GetEnumerator();

    ASSERT_FALSE( e.MoveNext() );
}

TEST( TDictionaryIndexedTests, it_can_hold_items )
{
    TDictionaryIndexed<CCharString, long> a;

    a.Add( CCharString( "a" ), 0 );
    a.Add( CCharString( "b" ), 1 );
    a.Add( CCharString( "c" ), 2 );


    ASSERT_EQ( a.Length(), 3u );

    ASSERT_EQ( *a.Find( CCharString( "a" ) ), 0 );
    ASSERT_EQ( *a.Find( CCharString( "b" ) ), 1 );
    ASSERT_EQ( *a.Find( CCharString( "c" ) ), 2 );
}
