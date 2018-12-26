#ifndef UDeclGadget_H
#define UDeclGadget_H

#   ifdef SHLIB_GADGET
#       define BUILDING_SHAREDLIB
#   else
#       undef BUILDING_SHAREDLIB
#   endif
#   include "UDeclSpec.h"

#endif // UDeclGadget_H
