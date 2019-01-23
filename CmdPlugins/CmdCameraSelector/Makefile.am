
AM_CPPFLAGS = \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Platform

deplibs = \
		$(top_builddir)/VSAShared/libvsashared.la \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la

lib_LTLIBRARIES = CmdCameraSelector.la

CmdCameraSelector_la_SOURCES = CCmdCameraSelector.cpp

CmdCameraSelector_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CmdCameraSelector_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CmdCameraSelector_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CmdCameraSelector_la_LIBADD = -lstdc++ -lc
CmdCameraSelector_la_DEPENDENCIES = \
		$(deplibs)
