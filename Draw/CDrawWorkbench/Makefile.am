AM_CPPFLAGS += \
		-I$(abs_top_srcdir)/Gadget \
		-I$(abs_top_srcdir)/Common \
		-I$(abs_top_srcdir)/Platform \
		-I$(abs_top_srcdir)/Draw/VDraw \
		-I/mingw64/x86_64-w64-mingw32/include
#AM_CXXFLAGS += -fPIC
AM_LDFLAGS += \
		-L/mingw64/x86_64-w64-mingw32/lib \
		-L/lib/x86_64-linux-gnu

deplibs = \
		$(abs_top_builddir)/Gadget/libgadget.la \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Platform/libplatform.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la


lib_LTLIBRARIES = CDrawWorkbench.la

CDrawWorkbench_la_SOURCES = CDrawWorkbench.cpp

CDrawWorkbench_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CDrawWorkbench_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CDrawWorkbench_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CDrawWorkbench_la_LIBADD = \
		-loleaut32 \
		-lole32 \
		-lgdi32 \
		-ladvapi32 \
		-lstdc++ \
		-lc

CDrawWorkbench_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/CDrawWorkbench-0$(DYLIBEXT) CDrawWorkbench$(DYLIBEXT)
