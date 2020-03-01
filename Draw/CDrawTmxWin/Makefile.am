AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la


lib_LTLIBRARIES = CDrawTmxWin.la

CDrawTmxWin_la_SOURCES = CDrawTmxWin.cpp

CDrawTmxWin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawTmxWin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawTmxWin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)  $(NO_UNDEFINED) -module \
		$(deplibs)
CDrawTmxWin_la_LIBADD = -lstdc++ -lc
CDrawTmxWin_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/CDrawTmxWin-0$(DYLIBEXT) CDrawTmxWin$(DYLIBEXT)
