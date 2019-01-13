AM_CPPFLAGS += \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/VSAShared
AM_CXXFLAGS += -fPIC




noinst_LTLIBRARIES = libworkbenchshared.la

libworkbenchshared_la_SOURCES = \
	CCommandProcessorWorkbench.cpp \
	CMouseProcessorWB.cpp
libworkbenchshared_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libworkbenchshared_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libworkbenchshared_la_DEPENDENCIES = \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
