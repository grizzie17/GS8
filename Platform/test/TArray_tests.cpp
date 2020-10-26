#include "TArray.h"
#include "iggy.h"


// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi::Core;


TEST( TArrayTests, it_should_initialize_as_empty )
{
    TArray<long> a;

    ASSERT_EQ( a.Length(), 0u );
}

TEST( TArrayTests, the_enumerator_should_behave_with_an_empty_array )
{
    TArray<long>           a;
    TArrayEnumerator<long> e = a.GetEnumerator();

    ASSERT_FALSE( e.MoveNext() );
}

TEST( TArrayTests, it_can_hold_items )
{
    TArray<long> a;

    a[0] = 0;
    a[1] = 1;
    a[2] = 2;

    ASSERT_EQ( a.Length(), ( 3u ) );

    ASSERT_EQ( a[0], ( 0 ) );
    ASSERT_EQ( a[1], ( 1 ) );
    ASSERT_EQ( a[2], ( 2 ) );
}

TEST( TArrayTests, it_can_sort_items )
{
    TArray<long> a;

    a[0] = 2;
    a[1] = 1;
    a[2] = 3;

    a.Sort();

    ASSERT_EQ( a[0], ( 1 ) );
    ASSERT_EQ( a[1], ( 2 ) );
    ASSERT_EQ( a[2], ( 3 ) );
}

TEST( TArrayTests, it_can_allocate_space_when_needed )
{
    TArray<long> a;

    ASSERT_EQ( a.Length(), 0u );

    long* p = a.PointItem( 5 );

    ASSERT_NE( (void*)p, (void*)NULL );
    ASSERT_EQ( a.Length(), 6u );
}

TEST( TArrayTests, it_can_determine_if_already_allocated )
{
    TArray<long> a;

    long* p = a.PointArray( 3 );

    ASSERT_EQ( (void*)p, nullptr );
}

TEST( TArrayTests, it_can_clear_its_memory )
{
    TArray<long> a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;

    ASSERT_EQ( a.Length(), 4u );

    a.Clear();

    ASSERT_EQ( a.Length(), 0u );
}
