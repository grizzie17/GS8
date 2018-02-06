AM_CPPFLAGS = \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Common/Common_specs \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/3rdParty/igloo
AM_CXXFLAGS = \
		-fPIC -Wall -Werror


bin_PROGRAMS = common_specs
#TESTS = @pbindir@/common_specs

common_specs_SOURCES = \
	Common_specs.cpp \
	\
	CMatrix3x3_spec.cpp \
	CUnitsOfMeasure_spec.cpp \
	CVariables_spec.cpp \
	CVariantData_spec.cpp \
	TComPointer_spec.cpp \
	TDictionaryIndexed_spec.cpp \
	TQueue_spec.cpp
common_specs_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
common_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
common_specs_LDFLAGS = $(LDFLAGS)
common_specs_LDADD = \
		../libcommon.a \
		../../Platform/libplatform.a \
		-lpthread -ldl

