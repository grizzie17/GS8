AM_CPPFLAGS = \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/LogFile \
		-I$(top_srcdir)/3rdParty/igloo

plibdir = @locallib@
pbindir = @checkbin@

pbin_PROGRAMS = common_specs
TESTS = @pbindir@/common_specs

common_specs_SOURCES = \
	Common_specs.cpp \
	\
	CMatrix3x3_spec.cpp \
	CSemaphore_spec.cpp \
	cstring_s_spec.cpp \
	CUnitsOfMeasure_spec.cpp \
	CVariables_spec.cpp \
	CVariantData_spec.cpp \
	TArray_spec.cpp \
	TComPointer_spec.cpp \
	TDictionaryIndexed_spec.cpp \
	TQueue_spec.cpp
common_specs_CXXFLAGS = $(CXXFLAGS)
common_specs_CPPFLAGS = $(CPPFLAGS)
common_specs_LDADD = \
		$(plibdir)/libcommon.a \
		$(plibdir)/libplatform.a \
		$(LDFLAGS)

