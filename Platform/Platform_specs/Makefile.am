AM_CPPFLAGS = \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/LogFile \
		-I$(top_srcdir)/3rdParty/igloo
AM_LDFLAGS = -L$(blibdir)

bbindir = $(top_builddir)/bin
blibdir = $(top_builddir)/lib
noinst_PROGRAMS = platform_specs

platform_specs_SOURCES = \
	Platform_specs.cpp \
	\
	CCharDescriptor_spec.cpp \
	CCharString_spec.cpp \
	CColor_spec.cpp \
	CDateTime_spec.cpp \
	CSemaphore_spec.cpp \
	cstring_s_spec.cpp \
	TCharDescriptor_spec.cpp \
	UMachine_spec.cpp \
	UPlatformString_spec.cpp
platform_specs_LDADD = $(top_builddir)/Platform/libplatform.a
	