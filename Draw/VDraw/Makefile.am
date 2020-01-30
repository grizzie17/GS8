AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
#AM_CXXFLAGS += -fPIC

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la


lib_LTLIBRARIES = libvdraw.la

libvdraw_la_SOURCES = \
		IDraw.cpp \
		IDrawDebug.cpp \
		IDrawTmx.cpp \
		IDrawWin32.cpp \
		IXPicture.cpp \
		VDraw.cpp \
		VDrawTmx.cpp
libvdraw_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvdraw_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libvdraw_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		$(deplibs)
libvdraw_la_LIBADD = \
		-lc
libvdraw_la_DEPENDENCIES = \
		$(deplibs)
