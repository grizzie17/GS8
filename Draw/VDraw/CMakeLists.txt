set( THIS VDraw )

set( SOURCES
	IDraw.cpp
	IDrawDebug.cpp
	IDrawTmx.cpp
	IDrawWin32.cpp
	IXPicture.cpp

	VDraw.cpp
	VDrawTmx.cpp)

set( HEADERS
	IDraw.h
	IDrawDebug.h
	IDrawTmx.h
	IDrawWin32.h
	IXPicture.h

	VDraw.h
	VDrawTmx.h)

add_library(${THIS} STATIC ${SOURCES} ${HEADERS})
