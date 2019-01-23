
AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/WorkbenchShared


bin_PROGRAMS = workbench

workbench_SOURCES = \
		CApplicationGaugeWorkbenchWin.cpp \
		CWinCEApp.cpp \
		CWinCEDlg.cpp \
		winmain.cpp
workbench_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
workbench_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
workbench_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		-Wl,--whole-archive \
		$(top_builddir)/WorkbenchShared/libworkbenchshared.la \
		$(top_builddir)/VSAShared/libvsashared.la \
		-Wl,--no-whole-archive \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
if OS_MSYS
workbench_LDADD = \
		-lkernel32 \
		-luser32 \
		-lgdi32 \
		-lwinspool \
		-lcomdlg32 \
		-ladvapi32 \
		-lshell32 \
		-lole32 \
		-loleaut32 \
		-lodbc32 \
		-lodbccp32
		-lstdc++ \
		-lc
endif
workbench_DEPENDENCIES = \
		$(top_builddir)/WorkbenchShared/libworkbenchshared.la \
		$(top_builddir)/VSAShared/libvsashared.la \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
