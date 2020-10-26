
#ifndef UDeclPlatform_H
#define UDeclPlatform_H

#include "UDeclSpec.h"

#undef PLATFORM_API
#undef PLATFORM_CLASS

#if defined( SHLIB_PLATFORM )
#    define PLATFORM_DLLEXPORT DLLEXPORT
#else
#    define PLATFORM_DLLEXPORT DLLIMPORT
#endif
#define PLATFORM_CLASS    PLATFORM_DLLEXPORT
#define PLATFORM_API( t ) PLATFORM_DLLEXPORT t CDECL


#define CORE_API( t ) PLATFORM_API( t )
#define CORE_CLASS    PLATFORM_CLASS


#endif  // UDeclPlatform_H
