AM_CPPFLAGS = \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/LogFile \
		-I$(top_srcdir)/3rdParty/igloo


bin_PROGRAMS = gadget_specs
#TESTS = @pbindir@/gadget_specs

gadget_specs_SOURCES = \
	Gadget_specs.cpp \
	\
	CKeyNames_spec.cpp \
	CQueue_spec.cpp \
	Equations_spec.cpp
gadget_specs_CXXFLAGS = $(CXXFLAGS)
gadget_specs_CPPFLAGS = $(CPPFLAGS)
gadget_specs_LDADD = \
		$(libdir)/libgadget.a \
		$(libdir)/libcommon.a \
		$(libdir)/libplatform.a \
		$(libdir)/liblogfile.a \
		$(LDFLAGS)

