#ifndef UDeclGadget_H
#define UDeclGadget_H

#include "UDeclSpec.h"


#undef GADGET_API
#undef GADGET_CLASS

#if defined( SHLIB_GADGET )
#    define GADGET_DLLEXPORT DLLEXPORT
#else
#    define GADGET_DLLEXPORT DLLIMPORT
#endif

#define GADGET_CLASS    GADGET_DLLEXPORT
#define GADGET_API( t ) GADGET_DLLEXPORT t CDECL

#endif  // UDeclGadget_H
