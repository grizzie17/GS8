AM_CPPFLAGS += \
		-I$(abs_top_srcdir)/Common \
		-I$(abs_top_srcdir)/Platform \
		-I$(abs_top_srcdir)/Draw/VDraw \
		-I$(abs_top_srcdir)/Draw/VGDI \
		-I$(MINGWPREFIX)/include
#AM_CXXFLAGS += -fPIC
AM_LDFLAGS += \
		-L/usr/lib \
		-L$(MINGWPREFIX)/lib \
		-L/lib/x86_64-linux-gnu

deplibs = \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la \
		$(abs_top_builddir)/Draw/VGDI/libvgdi.la


lib_LTLIBRARIES = CDrawWin.la

CDrawWin_la_SOURCES = CDrawWin.cpp

CDrawWin_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawWin_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawWin_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED)  -module \
		-Wl,--whole-archive \
		/usr/lib/libuuid.a \
		-Wl,--no-whole-archive \
		$(deplibs)

#$(NO_UNDEFINED)

CDrawWin_la_LIBADD = \
		-loleaut32 \
		-lole32 \
		-lgdi32 \
		-ladvapi32 \
		-luuid \
		-lstdc++ \
		-lc

CDrawWin_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	cp $(DESTDIR)$(libdir)/CDrawWin-0$(DYLIBEXT) CDrawWin$(DYLIBEXT)
