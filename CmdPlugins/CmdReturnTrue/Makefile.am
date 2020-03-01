
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

lib_LTLIBRARIES = CmdReturnTrue.la

CmdReturnTrue_la_SOURCES = CmdReturnTrue.cpp

CmdReturnTrue_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CmdReturnTrue_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CmdReturnTrue_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CmdReturnTrue_la_LIBADD = -lstdc++ -lc
CmdReturnTrue_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/CmdReturnTrue-0$(DYLIBEXT) CmdReturnTrue$(DYLIBEXT)
