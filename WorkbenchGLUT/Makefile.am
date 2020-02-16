
AM_CPPFLAGS += \
		-I$(top_srcdir)/WorkbenchShared \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Platform

AM_LDFLAGS += \
		-L$(abs_top_builddir)/WorkbenchShared \
		-L$(abs_top_builddir)/VSAShared \
		-L$(abs_top_builddir)/Gadget \
		-L$(abs_top_builddir)/Common \
		-L$(abs_top_builddir)/Draw/VDraw \
		-L$(abs_top_builddir)/Platform

bin_PROGRAMS = workbench

workbench_SOURCES = \
		CApplicationGaugeWorkbench.cpp \
		GaugeViewOpenGL.cpp \
		Workbench.cpp
workbench_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
workbench_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
workbench_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS)
workbench_LDADD = \
		-lworkbenchshared -lvsashared \
		-lgadget -lcommon -lplatform -lglut -lGL -ldl -lstdc++ -lc

workbench_DEPENDENCIES = \
		$(abs_top_builddir)/WorkbenchShared/libworkbenchshared.la \
		$(abs_top_builddir)/VSAShared/libvsashared.la \
		$(abs_top_builddir)/Gadget/libgadget.la \
		$(abs_top_builddir)/Common/libcommon.la \
		$(abs_top_builddir)/Draw/VDraw/libvdraw.la \
		$(abs_top_builddir)/Platform/libplatform.la
