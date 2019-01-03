AM_CPPFLAGS += \
		-I$(top_srcdir)/Platform
#AM_CXXFLAGS += -fPIC




lib_LTLIBRARIES = libplatform.la

libplatform_la_SOURCES = \
		CCharDescriptor.cpp \
		CCharString.cpp \
		CColor.cpp \
		CDateTime.cpp \
		CFilePath.cpp \
		CMutex.cpp \
		CSemaphore.cpp \
		CSerial.cpp \
		CSignal.cpp \
		fixed_t.cpp \
		LogFile.cpp \
		stdio_sx.cpp \
		string_sx.cpp \
		UFile.cpp \
		UPlatform.cpp \
		UPlatformIO.cpp \
		UPlatformString.cpp \
		UPlatformThreads.cpp \
		UPlatformTime.cpp
libplatform_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libplatform_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) -DSHLIB_PLATFORM
libplatform_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED)
libplatform_la_LIBADD = -lpthread -lc






TESTS = Platform_specs
check_PROGRAMS = Platform_specs
EXTRA_Platform_specs_DEPENDENCIES = libplatform.la

CHKCPPFLAGS = \
		-I$(top_srcdir)/3rdParty \
		-I$(top_srcdir)/3rdParty/igloo

Platform_specs_SOURCES = \
	test/Platform_specs.cpp \
	\
	test/CCharDescriptor_spec.cpp \
	test/CCharString_spec.cpp \
	test/CColor_spec.cpp \
	test/CDateTime_spec.cpp \
	test/CSemaphore_spec.cpp \
	test/cstring_s_spec.cpp \
	test/TArray_spec.cpp \
	test/TCharDescriptor_spec.cpp \
	test/UMachine_spec.cpp \
	test/UNResult_spec.cpp \
	test/UPlatformString_spec.cpp
Platform_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS) $(GLOBAL_CXXFLAGS)
Platform_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
Platform_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Platform/.libs
		-lplatform.la \
Platform_specs_LDADD = \
		-lpthread \
		-lc

# check-local:
# 	$(top_builddir)/Platform/platform_specs
