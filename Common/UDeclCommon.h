#ifndef UDeclCommon_H
#define UDeclCommon_H

#include "UDeclSpec.h"

#undef COMMON_API
#undef COMMON_CLASS

#if defined( SHLIB_COMMON )
#    define COMMON_DLLEXPORT DLLEXPORT
#else
#    define COMMON_DLLEXPORT DLLIMPORT
#endif
#define COMMON_CLASS    COMMON_DLLEXPORT
#define COMMON_API( t ) COMMON_DLLEXPORT t CDECL

#endif  // UDeclCommon_H
