AM_CPPFLAGS += \
		-I$(abs_top_srcdir)/Common \
		-I$(abs_top_srcdir)/Platform \
		-I$(abs_top_srcdir)/Draw/VDraw \
		-I$(abs_top_srcdir)/Draw/VGDI
#AM_CXXFLAGS += -fPIC

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la \
		$(abs_top_builddir)/Draw/VGDI/libvgdi.la


lib_LTLIBRARIES = CDrawWin.la

CDrawWin_la_SOURCES = CDrawWin.cpp

CDrawWin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawWin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawWin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		-Wl,--whole-archive \
		$(abs_top_builddir)/Draw/VGDI/libvgdi.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la \
		-Wl,--no-whole-archive \
		$(deplibs)
CDrawWin_la_LIBADD = \
		-loleaut32 \
		-lole32 \
		-lgdi32 \
		-ladvapi32 \
		-lstdc++ \
		-lc
#		# -luuid \#

CDrawWin_la_DEPENDENCIES = \
		$(abs_top_builddir)/Draw/VGDI/libvgdi.la \
		$(deplibs)
