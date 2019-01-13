
AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC

#libdir = $(top_builddir)/lib

noinst_LTLIBRARIES = libvsashared.la

disabledSources = \
		CVehicleDataLoader.cpp \
		IBox.cpp \
		IServiceManager.cpp \
		VDesk.cpp \
		VPluginApplet.cpp


libvsashared_la_SOURCES = \
		CCommandProcessorForPlugins.cpp \
		CDesk.cpp \
		CDeskManager.cpp \
		CFunctionProcessorForPlugins.cpp \
		CHusk.cpp \
		CServiceManager.cpp \
		CTaskManager.cpp \
		IActiveXML.cpp \
		IApplet.cpp \
		IAttribute.cpp \
		ICommandPlugin.cpp \
		IDesk.cpp \
		IDeskManager.cpp \
		IEventsKeyboard.cpp \
		IEventsMouse.cpp \
		IHusk.cpp \
		IPanAndTiltClient.cpp \
		IPanAndTilt.cpp \
		IRepeater.cpp \
		IService.cpp \
		ITask.cpp \
		IVehicleDataSample.cpp \
		VPluginCommand.cpp \
		VPluginService.cpp \
		VSAShared.cpp
libvsashared_la_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvsashared_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
