
AM_CPPFLAGS += \
		-I$(top_srcdir)/WorkbenchShared \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform

bin_PROGRAMS = workbench

workbench_SOURCES = \
		CApplicationGaugeWorkbench.cpp \
		GaugeViewOpenGL.cpp \
		main.cpp \
		Workbench.cpp
workbench_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
workbench_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
workbench_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)
