AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Draw/VDrawOpenGL \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libcdrawopengl.la

libcdrawopengl_la_SOURCES = CDrawOpenGL.cpp

libcdrawopengl_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcdrawopengl_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcdrawopengl_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) -L$(top_builddir)/VDraw -L$(top_builddir)/VDrawOpenGL
libcdrawopengl_la_LIBADD = -lvdraw -lvdrawopengl -lplatform
