#include "UNResult.h"

// #include "igloo/igloo.h"
// using namespace igloo;

#include "iggy.h"

using namespace Yogi::Core;

Context( UNResult_macros ) {
Spec( status_success )
{
    NResult sts = NR_S_SUCCESS;

    AssertThat( NR_SUCCEEDED( sts ), IsTrue() );
}
};  // Context(UNResult_macros)
