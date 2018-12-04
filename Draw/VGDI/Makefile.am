AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
AM_CXXFLAGS += -fPIC


lib_LIBRARIES = libvgdi.a

libvgdi_a_SOURCES = \
	CGDIBrush.cpp \
	CGDIFont.cpp \
	CGDIPen.cpp \
	VGDI.cpp

libvgdi_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvgdi_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
