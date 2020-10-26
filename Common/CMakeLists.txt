set(THIS Common)

project( ${THIS}
	VERSION 1.0.0
	DESCRIPTION "Common"
	)

set(SOURCES
    CConfiguration.cpp
    CEventManager.cpp
    CFactoryConfiguration.cpp
    CFactoryPlugin.cpp
    Chronos.cpp
    CMatrix3x3.cpp
    CMatrix3x3d.cpp
    CPluginConfiguration.cpp
    CPluginLibrary.cpp
    CPluginLoader.cpp
    CUnitsOfMeasure.cpp
    CVariables.cpp
    CVariantData.cpp
    IExternalXML.cpp
    IKeyboard.cpp
    IPlugin.cpp
    IPluginLibrary.cpp
    IPluginLoadConfiguration.cpp
    ISupports.cpp
    ISupportsLocal.cpp
    VFactory.cpp
    VFactoryLite.cpp
    VPlugin.cpp
    VPluginWithAggregate.cpp
    VPluginWithAggregateList.cpp
	VSupports.cpp
	XMLLiteImpl.cpp
	)

set(DISABLED_SOURCES)

set(HEADERS
	CCharStringHash.h
    CConfiguration.h
    CEventManager.h
    CFactoryConfiguration.h
    CFactoryPlugin.h
    Chronos.h
    CMatrix3x3.h
    CMatrix3x3d.h
    CPluginConfiguration.h
    CPluginLibrary.h
    CPluginLoader.h
    CUnitsOfMeasure.h
    CVariables.h
    CVariantData.h
    IExternalXML.h
    IKeyboard.h
    IPlugin.h
    IPluginLibrary.h
    IPluginLoadConfiguration.h
    ISupports.h
	ISupportsLocal.h
	IXID.h
	TComPointer.h
	TDictionaryIndexed.h
	THash.h
	TList.h
	UDeclCommon.h
	UPluginConfiguration.h
	VConfiguration.h
    VFactory.h
	VFactoryLite.h
	VInterface.h
	VObject.h
	VPlugin.h
	VPluginConfiguration.h
	VPluginFactory.h
	VPluginFilter.h
	VPluginLibrary.h
    VPluginWithAggregate.h
    VPluginWithAggregateList.h
	VSupports.h
	XMLLite.h
	XMLLiteExtImpl.h
	XMLLiteImpl.h
	)


add_library(${THIS} SHARED ${SOURCES} ${HEADERS})
target_compile_definitions(${THIS} PRIVATE SHLIB_COMMON)
add_dependencies(${THIS} Platform)
target_link_libraries( ${THIS} Platform Ws2_32 Advapi32 Kernel32 )

add_subdirectory(test)
