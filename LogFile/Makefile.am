AM_CPPFLAGS = \
		-I$(top_srcdir)/Platform \
		-I$(top_srcdir)/LogFile \
		\
		-D_USRDLL \
		-DLOGFILE_EXPORTS
AM_CXXFLAGS = \
		-fPIC -Wall -Werror



lib_LIBRARIES = liblogfile.a

liblogfile_a_SOURCES = LogFile.cpp 
liblogfile_a_CXXFLAGS = $(CXXFLAGS)


