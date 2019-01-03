AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libcdrawtmxwin.la

libcdrawtmxwin_la_SOURCES = CDrawTmxWin.cpp

libcdrawtmxwin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcdrawtmxwin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcdrawtmxwin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)  $(NO_UNDEFINED) \
		-L$(top_builddir)/Draw/VDraw \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Platform \
		-Wl,--whole-archive \
		-lvdraw.a \
		-Wl,--no-whole-archive
libcdrawtmxwin_la_LIBADD = -lcommon.la -lplatform.la -lpthread -lc
