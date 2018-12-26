
#ifndef UDeclPlatform_H
#define UDeclPlatform_H

#   ifdef SHLIB_PLATFORM
#       define BUILDING_SHAREDLIB
#   else
#       undef BUILDING_SHAREDLIB
#   endif
#   include "UDeclSpec.h"

#endif // UDeclPlatform_H
