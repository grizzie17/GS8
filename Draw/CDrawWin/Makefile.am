AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Draw/VGDI \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libcdrawwin.la

libcdrawwin_la_SOURCES = CDrawWin.cpp

libcdrawwin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcdrawwin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcdrawwin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		-L$(top_builddir)/VDraw \
		-L$(top_builddir)/VGDI \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Platform
libcdrawwin_la_LIBADD = \
		-lvdraw \
		-lvgdi \
		-lcommon \
		-lplatform
