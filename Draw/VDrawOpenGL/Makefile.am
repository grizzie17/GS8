AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libvdrawopengl.la

libvdrawopengl_la_SOURCES = VDrawOpenGL.cpp

libvdrawopengl_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvdrawopengl_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
