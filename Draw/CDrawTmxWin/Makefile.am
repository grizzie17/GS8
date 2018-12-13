AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libcdrawtmxwin.la

libcdrawtmxwin_la_SOURCES = CDrawTmxWin.cpp

libcdrawtmxwin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcdrawtmxwin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcdrawtmxwin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)  $(NO_UNDEFINED) \
		-L$(top_builddir)/VDraw
libcdrawtmxwin_la_LIBADD = -lvdraw -lplatform
