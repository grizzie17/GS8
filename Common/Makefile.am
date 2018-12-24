


AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform
#AM_CXXFLAGS += -fPIC


lib_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = \
		CConfiguration.cpp \
		CEventManager.cpp \
		CFactoryConfiguration.cpp \
		CFactoryPlugin.cpp \
		Chronos.cpp \
		CMatrix3x3.cpp \
		CMatrix3x3d.cpp \
		CPluginConfiguration.cpp \
		CPluginLibrary.cpp \
		CPluginLoader.cpp \
		CUnitsOfMeasure.cpp \
		CVariables.cpp \
		CVariantData.cpp \
		IExternalXML.cpp \
		IKeyboard.cpp \
		IPlugin.cpp \
		IPluginLibrary.cpp \
		IPluginLoadConfiguration.cpp \
		ISupports.cpp \
		ISupportsLocal.cpp \
		VFactory.cpp \
		VFactoryLite.cpp \
		VPlugin.cpp \
		VPluginWithAggregate.cpp \
		VPluginWithAggregateList.cpp \
		VSupports.cpp \
		XMLLiteImpl.cpp
libcommon_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libcommon_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libcommon_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Common

libcommon_la_LIBADD = \
		-lplatform \
		-lpthread



TESTS = common_specs
bin_PROGRAMS = common_specs
EXTRA_common_specs_DEPENDENCIES = libcommon.la

CHKCPPFLAGS = \
		-I$(top_srcdir)/Platform/test \
		-I$(top_srcdir)/3rdParty/igloo
common_specs_SOURCES = \
	test/Common_specs.cpp \
	\
	test/CMatrix3x3_spec.cpp \
	test/CUnitsOfMeasure_spec.cpp \
	test/CVariables_spec.cpp \
	test/CVariantData_spec.cpp \
	test/TComPointer_spec.cpp \
	test/TDictionaryIndexed_spec.cpp \
	test/TQueue_spec.cpp
common_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS)
common_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
common_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		-L$(top_builddir)/Platform \
		-L$(top_builddir)/Common
common_specs_LDADD = \
		-lcommon \
		-lplatform \
		-lpthread -lc


# check-local:
# 	$(top_builddir)/Common/common_specs
