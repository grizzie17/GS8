AM_CPPFLAGS = \
		-I$(top_srcdir)/Common \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/Draw/VDraw \
		-I$(top_srcdir)/LogFile
AM_CXXFLAGS = \
		-fPIC -Wall -Werror




lib_LIBRARIES = libworkbenchshared.a

libworkbenchshared_a_SOURCES = \
	CApplicationGaugeWorkbench.cpp \
	CCommandProcessorWorkbench.cpp \
	CMouseProcessorWB.cpp
libworkbenchshared_a_CXXFLAGS = $(CXXFLAGS) $(AM_CXXFLAGS)
libworkbenchshared_a_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
