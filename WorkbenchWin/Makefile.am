
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
workbench_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)
