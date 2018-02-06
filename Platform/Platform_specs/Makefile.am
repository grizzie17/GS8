AM_CPPFLAGS = \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/3rdParty/igloo
AM_CXXFLAGS = \
		-fPIC -Wall -Werror


bin_PROGRAMS = platform_specs
#TESTS = @bindir@/platform_specs

platform_specs_SOURCES = \
	Platform_specs.cpp \
	\
	CCharDescriptor_spec.cpp \
	CCharString_spec.cpp \
	CColor_spec.cpp \
	CDateTime_spec.cpp \
	CSemaphore_spec.cpp \
	cstring_s_spec.cpp \
	TArray_spec.cpp \
	TCharDescriptor_spec.cpp \
	UMachine_spec.cpp \
	UPlatformString_spec.cpp
platform_specs_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
platform_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
platform_specs_LDFLAGS = $(LDFLAGS)
platform_specs_LDADD = \
		../libplatform.a \
		-lpthread -ldl
	