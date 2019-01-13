AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Draw/VGDI \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = CDrawWin.la

CDrawWin_la_SOURCES = CDrawWin.cpp

CDrawWin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawWin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawWin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		-Wl,--whole-archive \
		$(top_builddir)/Draw/VGDI/libvgdi.la \
		-Wl,--no-whole-archive \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
CDrawWin_la_LIBADD = \
		-lgdi32 \
		-ladvapi32 \
		-lole32 \
		-loleaut32 \
		-luuid \
		-lstdc++ \
		-lc
CDrawWin_la_DEPENDENCIES = \
		$(top_builddir)/Draw/VGDI/libvgdi.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la

