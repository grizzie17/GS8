
AM_CPPFLAGS = \
		-I$(top_srcdir)/VSAShared \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform

deplibs = \
		$(top_builddir)/VSAShared/libvsashared.la \
		$(top_builddir)/Gadget/libgadget.la \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la

lib_LTLIBRARIES = CServiceVehicleDirectLoad.la

CServiceVehicleDirectLoad_la_SOURCES = CServiceVehicleDirectLoad.cpp

CServiceVehicleDirectLoad_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CServiceVehicleDirectLoad_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CServiceVehicleDirectLoad_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CServiceVehicleDirectLoad_la_LIBADD = -lstdc++ -lc
CServiceVehicleDirectLoad_la_DEPENDENCIES = \
		$(deplibs)
