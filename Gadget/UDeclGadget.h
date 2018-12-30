#ifndef UDeclGadget_H
#define UDeclGadget_H

#include "UDeclSpec.h"

#undef DECL_API
#undef DECL_CLASS
#undef DECL_SHLIB
#if defined( SHLIB_GADGET )
#	define DECL_API(t)	t DECLSPECEXPORT
#	define DECL_CLASS	DECLSPECEXPORT
#	define DECL_SHLIB	DECLSPECEXPORT
#else
#	define DECL_API(t)	t DECLSPECIMPORT
#	define DECL_CLASS	DECLSPECIMPORT
#	define DECL_SHLIB	DECLSPECIMPORT
#endif

#endif // UDeclGadget_H
