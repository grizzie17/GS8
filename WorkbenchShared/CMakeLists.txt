set( THIS WorkbenchShared )

set( SOURCES
	CCommandProcessorWorkbench.cpp
	CMouseProcessorWB.cpp
)

set ( HEADERS
	CCommandProcessorWorkbench.h
	CMouseProcessorWB.h
)

add_library(${THIS} STATIC ${SOURCES} ${HEADERS})
