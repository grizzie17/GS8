AM_CPPFLAGS = \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/LogFile
AM_CXXFLAGS = \
		-fPIC -Wall -Werror


lib_LIBRARIES = libvdrawopengl.a

libvdrawopengl_a_SOURCES = VDrawOpenGL.cpp

libvdrawopengl_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvdrawopengl_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
