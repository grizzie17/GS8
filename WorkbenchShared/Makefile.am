AM_CPPFLAGS += \
		-I$(top_srcdir)/Gadget \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw
AM_CXXFLAGS += -fPIC




lib_LIBRARIES = libworkbenchshared.a

libworkbenchshared_a_SOURCES = \
	CApplicationGaugeWorkbench.cpp \
	CCommandProcessorWorkbench.cpp \
	CMouseProcessorWB.cpp
libworkbenchshared_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libworkbenchshared_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
