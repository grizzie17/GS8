set( THIS CmdConstant )

set( SOURCES
	CmdConstant.cpp
)

set( HEADERS
	CmdConstant.h
)

add_library( ${THIS} SHARED ${SOURCES} ${HEADERS} )
