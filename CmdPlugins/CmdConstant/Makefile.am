
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

lib_LTLIBRARIES = CmdConstant.la

CmdConstant_la_SOURCES = CmdConstant.cpp

CmdConstant_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CmdConstant_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CmdConstant_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CmdConstant_la_LIBADD = -lstdc++ -lc
CmdConstant_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/CmdConstant-0$(DYLIBEXT) CmdConstant$(DYLIBEXT)
