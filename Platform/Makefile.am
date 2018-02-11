AM_CPPFLAGS = \
		-I$(top_srcdir)/Platform
AM_CXXFLAGS = \
		-fPIC -Wall -Werror



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


