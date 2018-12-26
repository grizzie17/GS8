#ifndef UDeclCommon_H
#define UDeclCommon_H

#   ifdef SHLIB_COMMON
#       define BUILDING_SHAREDLIB
#   else
#       undef BUILDING_SHAREDLIB
#   endif
#   include "UDeclSpec.h"

#endif // UDeclCommon_H
