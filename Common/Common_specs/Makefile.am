AM_CPPFLAGS = \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Platform/Platform_specs \
		-I$(top_srcdir)/LogFile \
		-I$(top_srcdir)/3rdParty/igloo
AM_LDFLAGS = \
		-L$(blibdir)

bbindir = $(top_builddir)/bin
blibdir = $(top_builddir)/lib

noinst_PROGRAMS = common_specs

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
common_specs_LDADD = \
					$(top_builddir)/Common/libcommon.a \
					$(top_builddir)/Platform/libplatform.a
#common_specs_LDADD = -lcommon -lplatform
	