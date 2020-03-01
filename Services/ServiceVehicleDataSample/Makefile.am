
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

lib_LTLIBRARIES = CServiceVehicleDataSample.la

CServiceVehicleDataSample_la_SOURCES = CServiceVehicleDataSample.cpp

CServiceVehicleDataSample_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
CServiceVehicleDataSample_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
CServiceVehicleDataSample_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
CServiceVehicleDataSample_la_LIBADD = -lstdc++ -lc
CServiceVehicleDataSample_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/CServiceVehicleDataSample-0$(DYLIBEXT) CServiceVehicleDataSample$(DYLIBEXT)
