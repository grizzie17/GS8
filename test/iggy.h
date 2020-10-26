#ifndef IGGY_H
#define IGGY_H

#include <float.h>


#include "gtest/gtest.h"

#define Context( s )            namespace s
#define Describe( s )           namespace s
#define It( s )                 TEST( __FILE_BASENAME__, s )
#define Spec( s )               TEST( __FILE_BASENAME__, s )
#define AssertThat( t, r )      ASSERT_EQ( ( t ), ( r ) )
#define AssertThatEQ( t, r )    ASSERT_EQ( ( t ), ( r ) )
#define AssertNotThat( t, r )   ASSERT_NE( ( t ), ( r ) )
#define AssertThatNE( t, r )    ASSERT_NE( ( t ), ( r ) )
#define AssertThatGE( t, r )    ASSERT_GE( ( t ), ( r ) )
#define AssertThatGT( t, r )    ASSERT_GT( ( t ), ( r ) )
#define AssertThatStrEq( t, r ) ASSERT_STREQ( ( t ), ( r ) )
#define IsTrue()                true
#define IsFalse()               false

template <typename T>
inline T
Equals( T x )
{
    return x;
}

#endif  // IGGY_H
