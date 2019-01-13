AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
AM_CXXFLAGS += -fPIC


noinst_LTLIBRARIES = libvgdi.la

libvgdi_la_SOURCES = \
		CGDIBrush.cpp \
		CGDIFont.cpp \
		CGDIPen.cpp \
		VGDI.cpp

libvgdi_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvgdi_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
