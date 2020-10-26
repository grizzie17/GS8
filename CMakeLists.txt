set(MINIMUM_CMAKE_VERSION 3.17)

set(THIS GS8)

cmake_minimum_required(VERSION ${MINIMUM_CMAKE_VERSION})
project(
	${THIS}
	VERSION 0.1.0
	LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add_compile_definitions(SHLIB)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Debug")
endif()
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(_DEBUG 1)
endif()

# if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
# 	set( _DEBUG 1 )
# endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(
		FATAL_ERROR
		"In-Source builds not allowed. Please run CMake from a 'build' directory."
	)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()
enable_testing()
add_subdirectory(googletest)

include_directories(
	Platform
	Common
	Draw/VDraw
	Gadget
	Draw/VGDI
	VSAShared
	WorkbenchShared
	test)

add_subdirectory( Platform )
add_subdirectory( Common )
add_subdirectory( Draw )
add_subdirectory( Gadget )

add_subdirectory( VSAShared )
add_subdirectory( CmdPlugins )
add_subdirectory( WorkbenchShared )
add_subdirectory( WorkbenchWin )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
