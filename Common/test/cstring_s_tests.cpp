// #include "igloo/igloo.h"
// using namespace igloo;
#define __FILE_BASENAME__ cstring_s

#include <string.h>

#include "iggy.h"


Context( cstring_s ) {
Spec( should_define_STDC_SECURE_LIB )
{
#if defined( __STDC_SECURE_LIB__ )
#    if defined( _MSC_VER )
    AssertThatGT( __STDC_SECURE_LIB__, ( 200410L ) );
#    else
    AssertThatGT( __STDC_SECURE_LIB__, ( 201101L ) );
#    endif
#endif
}

};  // Context(cstring_s)
