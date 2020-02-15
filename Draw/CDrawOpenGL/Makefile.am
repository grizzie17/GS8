AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Draw/VDrawOpenGL \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/3rdParty/SOIL \
		-I/usr/include/freetype2

AM_LDFLAGS += \
		-L$(abs_top_builddir)/Common \
		-L$(abs_top_builddir)/Platform \
		-L$(abs_top_builddir)/Draw/VDraw \
		-L$(abs_top_builddir)/Draw/VDrawOpenGL
#AM_CXXFLAGS += -fPIC

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la \
		$(abs_top_builddir)/Draw/VDrawOpenGL/libvdrawopengl.la



lib_LTLIBRARIES = libcdrawopengl.la

libcdrawopengl_la_SOURCES = CDrawOpenGL.cpp

libcdrawopengl_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcdrawopengl_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcdrawopengl_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module
libcdrawopengl_la_LIBADD = -lvdrawopengl -lvdraw -lcommon -lplatform  -lstdc++ -lc
libcdrawopengl_la_DEPENDENCIES = \
		$(deplibs)
