#ifndef EqualsFloat_h
#define EqualsFloat_h
#pragma once

#include <cstdlib>
#include <math.h>

const float k_EqualsFloatTolerance = 0.000075f;

inline bool
EqualsFloat( float a, float b )
{
    if ( a + k_EqualsFloatTolerance < b )
        return false;
    if ( b < a - k_EqualsFloatTolerance )
        return false;
    return true;
}

inline bool
EqualsDouble( double a, double b )
{
    if ( a + k_EqualsFloatTolerance < b )
        return false;
    if ( b < a - k_EqualsFloatTolerance )
        return false;
    return true;
    // return fabs( a - b ) < DBL_EPSILON;
}

inline float
EqualsFloat( float a )
{
    return a;
}

inline double
EqualsFloat( double d )
{
    return d;
}

#define AssertEqualsFloat( x, y )  ASSERT_EQ( EqualsFloat( x, y ), true )
#define AssertEqualsDouble( x, y ) ASSERT_EQ( EqualsDouble( x, y ), true )


#endif  // EqualsFloat_h
