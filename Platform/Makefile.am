

AM_CPPFLAGS += \
		-I$(top_srcdir)/Platform
AM_CXXFLAGS += -fPIC




lib_LIBRARIES = libplatform.a

libplatform_a_SOURCES = \
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
libplatform_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libplatform_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)



TESTS = platform_specs
check_PROGRAMS = platform_specs
EXTRA_platform_specs_DEPENDENCIES = libplatform.a

CHKCPPFLAGS = \
		-I$(top_srcdir)/3rdParty \
		-I$(top_srcdir)/3rdParty/igloo

platform_specs_SOURCES = \
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
	test/UPlatformString_spec.cpp
platform_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS)
platform_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
platform_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		-L$(top_builddir)/Platform
platform_specs_LDADD = \
		-lplatform \
		-lpthread -ldl

check-local:
	$(top_builddir)/Platform/platform_specs
