AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
AM_CXXFLAGS += -fPIC



noinst_LIBRARIES = libvdraw.a

libvdraw_a_SOURCES = \
		IDraw.cpp \
		IDrawDebug.cpp \
		IDrawTmx.cpp \
		IDrawWin32.cpp \
		VDraw.cpp \
		VDrawTmx.cpp
libvdraw_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvdraw_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)


