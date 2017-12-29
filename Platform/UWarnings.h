#ifndef _H_UWarnings
#define _H_UWarnings

#if defined(_MSC_VER)

#	define	BEGIN_IGNORE_WARNING( x )	\
		__pragma( warning(push) )		\
		__pragma( warning(disable:x) )

#	define	END_IGNORE_WARNING	__pragma( warning(pop) )

#	define	GCC_DIAG_OFF(x)
#	define	GCC_DIAG_ON(x)

#else

#	define	BEGIN_IGNORE_WARNING( x )
#	define	END_IGNORE_WARNING

#	if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#		define GCC_DIAG_STR(s) #s
#		define GCC_DIAG_JOINSTR(x,y) GCC_DIAG_STR(x ## y)
#		define GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
#		define GCC_DIAG_PRAGMA(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
#		if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#			define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(push) \
				GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#			define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(pop)
#		else
#			define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#			define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(warning GCC_DIAG_JOINSTR(-W,x))
#		endif
#	else
#		define GCC_DIAG_OFF(x)
#		define GCC_DIAG_ON(x)
#	endif

#endif

#	define	BEGIN_OVERRUN_WARNING	BEGIN_IGNORE_WARNING(4748)
#	define	END_OVERRUN_WARNING		END_IGNORE_WARNING



#endif //_H_UWarnings
