
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

lib_LTLIBRARIES = GenericContainer.la

GenericContainer_la_SOURCES = GenericContainer.cpp

GenericContainer_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
GenericContainer_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
GenericContainer_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) -module \
		$(deplibs)
GenericContainer_la_LIBADD = -lstdc++ -lc
GenericContainer_la_DEPENDENCIES = \
		$(deplibs)

install-exec-hook:
	cd $(DESTDIR)$(bindir) && \
	$(LN_S) $(DESTDIR)$(libdir)/GenericContainer-0$(DYLIBEXT) GenericContainer$(DYLIBEXT)
