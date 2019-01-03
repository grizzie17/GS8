
AM_CPPFLAGS += \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/VSAShared
#AM_CXXFLAGS += -fPIC

#libdir = $(top_builddir)/lib

noinst_LIBRARIES = libvsashared.a

libvsashared_a_SOURCES = \
		CCommandProcessorForPlugins.cpp \
		CDesk.cpp \
		CDeskManager.cpp \
		CFunctionProcessorForPlugins.cpp \
		CHusk.cpp \
		CServiceManager.cpp \
		CTaskManager.cpp \
		CVehicleDataLoader.cpp \
		IActiveXML.cpp \
		IApplet.cpp \
		IAttribute.cpp \
		IBox.cpp \
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
		IServiceManager.cpp \
		ITask.cpp \
		IVehicleDataSample.cpp \
		VDesk.cpp \
		VPluginApplet.cpp \
		VPluginCommand.cpp \
		VPluginService.cpp \
		VSAShared.cpp
libvsagadget_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libvsagadget_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
