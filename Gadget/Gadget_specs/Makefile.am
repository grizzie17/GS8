AM_CPPFLAGS = \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/LogFile \
		-I$(top_srcdir)/3rdParty/igloo
AM_CXXFLAGS = \
		-fPIC -Wall -Werror


bin_PROGRAMS = gadget_specs
#TESTS = @pbindir@/gadget_specs

gadget_specs_SOURCES = \
	Gadget_specs.cpp \
	\
	CKeyNames_spec.cpp \
	CQueue_spec.cpp \
	Equations_spec.cpp
gadget_specs_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
gadget_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
gadget_specs_LDFLAGS = $(LDFLAGS)
gadget_specs_LDADD = \
		../libgadget.a \
		../../Common/libcommon.a \
		../../Platform/libplatform.a \
		-lpthread -ldl

