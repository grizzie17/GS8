AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = CDrawTmxWin.la

CDrawTmxWin_la_SOURCES = CDrawTmxWin.cpp

CDrawTmxWin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawTmxWin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawTmxWin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)  $(NO_UNDEFINED) -module \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
CDrawTmxWin_la_LIBADD = -lstdc++ -lc
CDrawTmxWin_la_DEPENDENCIES = \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
