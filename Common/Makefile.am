


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
libcommon_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)  -DSHLIB_COMMON
libcommon_la_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) $(NO_UNDEFINED) \
		-Wl,--whole-archive \
		$(top_builddir)/Draw/VDraw/libvdraw.la \
		-Wl,--no-whole-archive \
		$(top_builddir)/Platform/libplatform.la

libcommon_la_LIBADD = -lWs2_32 -lpthread -lstdc++ -lc
libcommon_la_DEPENDENCIES = $(top_builddir)/Platform/libplatform.la \
		$(top_builddir)/Draw/VDraw/libvdraw.la



TESTS = Common_specs
bin_PROGRAMS = Common_specs
EXTRA_Common_specs_DEPENDENCIES = libcommon.la $(top_builddir)/Platform/libplatform.la

CHKCPPFLAGS = \
		-I$(top_srcdir)/Platform/test \
		-I$(top_srcdir)/3rdParty/igloo
Common_specs_SOURCES = \
		test/Common_specs.cpp \
		\
		test/CMatrix3x3_spec.cpp \
		test/CUnitsOfMeasure_spec.cpp \
		test/CVariables_spec.cpp \
		test/CVariantData_spec.cpp \
		test/TComPointer_spec.cpp \
		test/TDictionaryIndexed_spec.cpp \
		test/TQueue_spec.cpp
Common_specs_CXXFLAGS = $(CHECK_FLAGS) $(CXXFLAGS) $(AM_CXXFLAGS)
Common_specs_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS) $(CHKCPPFLAGS)
Common_specs_LDFLAGS = $(LDFLAGS) $(AM_LDFLAGS) \
		$(top_builddir)/Common/libcommon.la \
		$(top_builddir)/Platform/libplatform.la
Common_specs_LDADD = -lpthread -lstdc++ -lc


# check-local:
# 	$(top_builddir)/Common/common_specs
