#ifndef UDeclCommon_H
#define UDeclCommon_H

#include "UDeclSpec.h"

#undef DECL_API
#undef DECL_CLASS
#undef DECL_SHLIB
#if defined( SHLIB_COMMON )
#	define DECL_API(t)	t DECLSPECEXPORT
#	define DECL_CLASS	DECLSPECEXPORT
#	define DECL_SHLIB	DECLSPECEXPORT
#	define IMPL_SHLIB	DECLSPECIMPORT
#else
#	define DECL_API(t)	t DECLSPECIMPORT
#	define DECL_CLASS	DECLSPECIMPORT
#	define DECL_SHLIB	DECLSPECIMPORT
#	define IMPL_SHLIB
#endif

#endif // UDeclCommon_H
