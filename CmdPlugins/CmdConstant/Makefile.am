
AM_CPPFLAGS = \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Platform

libs = \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la

lib_LTLIBRARIES = CmdConstant.la

CmdConstant_la_SOURCES = CmdConstant.cpp

CmdConstant_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CmdConstant_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CmdConstant_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(libs)
CmdConstant_la_LIBADD = -lstdc++ -lc
CmdConstant_la_DEPENDENCIES = \
		$(libs)
