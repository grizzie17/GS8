
AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/WorkbenchShared


bin_PROGRAMS = workbench

workbench_SOURCES = \
		CApplicationGaugeWorkbench.cpp \
		CWinCEApp.cpp \
		CWinCEDlg.cpp \
		winmain.cpp
workbench_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
workbench_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
workbench_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Common \
		-L$(top_builddir)/Gadget \
		-L$(top_builddir)/Draw/VDraw \
		-L$(top_builddir)/VSAShared \
		-L$(top_builddir)/WorkbenchShared
workbench_LDADD = \
		-lcommon \
		-lplatform \
		-ldl
