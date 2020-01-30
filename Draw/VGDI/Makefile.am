AM_CPPFLAGS += \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la


lib_LTLIBRARIES = libvgdi.la

libvgdi_la_SOURCES = \
		CGDIBrush.cpp \
		CGDIFont.cpp \
		CGDIPen.cpp \
		VGDI.cpp

libvgdi_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvgdi_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libvgdi_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		$(deplibs)
libvgdi_la_LIBADD = \
		-lgdi32 \
		-lc

libvgdi_la_DEPENDENCIES = \
		$(deplibs)
