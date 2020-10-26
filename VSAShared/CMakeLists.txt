set( THIS VSAShared )

project( ${THIS}
	VERSION 1.0.0
	DESCRIPTION "VSA Shared Library")

set( SOURCES_DISABLED
	CVehicleDataReader.cpp
)

set( SOURCES
	CCommandProcessorForPlugins.cpp
	CDesk.cpp
	CDeskManager.cpp
	CFunctionProcessorForPlugins.cpp
	CHusk.cpp
	CServiceManager.cpp
	CTaskManager.cpp
	CVehicleDataLoader.cpp
	CXMLSampleLoader.cpp
	IActiveXML.cpp
	IApplet.cpp
	IAttribute.cpp
	IBox.cpp
	ICommandPlugin.cpp
	IDesk.cpp
	IDeskManager.cpp
	IEventsKeyboard.cpp
	IEventsMouse.cpp
	IHusk.cpp
	IPanAndTilt.cpp
	IPanAndTiltClient.cpp
	IRepeater.cpp
	IService.cpp
	IServiceManager.cpp
	ITask.cpp
	IVehicleDataSample.cpp
	VDesk.cpp
	VPluginApplet.cpp
	VPluginCommand.cpp
	VPluginService.cpp
	VSAShared.cpp
)

set( HEADERS
	CCommandProcessorForPlugins.h
	CDesk.h
	CDeskManager.h
	CFunctionProcessorForPlugins.h
	CHusk.h
	CServiceManager.h
	CTaskManager.h
	CVehicleDataLoader.h
	CVehicleDataReader.h
	CXMLSampleLoader.h
	IActiveXML.h
	IApplet.h
	IAttribute.h
	IBox.h
	ICommandPlugin.h
	IDesk.h
	IDeskManager.h
	IEventsKeyboard.h
	IEventsMouse.h
	IHusk.h
	IPanAndTilt.h
	IPanAndTiltClient.h
	IRepeater.h
	IService.h
	IServiceManager.h
	ITask.h
	IVehicleDataSample.h
	VDesk.h
	VPluginApplet.h
	VPluginCommand.h
	VPluginService.h
	VSAShared.h
)

add_compile_definitions(SHLIB_VSASHARED)


add_library(${THIS} SHARED ${SOURCES} ${HEADERS})

set_target_properties(${THIS} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1)

target_link_libraries(Common Platform)
