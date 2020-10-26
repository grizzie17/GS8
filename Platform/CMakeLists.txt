set(THIS Platform)

# project( ${THIS}
# 	VERSION 1.0.0
# 	DESCRIPTION "Platform"
# 	)

set(SOURCES
    CCharDescriptor.cpp
    CCharString.cpp
    CColor.cpp
    CDateTime.cpp
    CFilePath.cpp
	CMutex.cpp
	CSemaphore.cpp
	CSerial.cpp
	CSignal.cpp
	CSocket.cpp
	LogFile.cpp
	stdio_sx.cpp
	string_sx.cpp
    UFile.cpp
    UPlatform.cpp
    UPlatformIO.cpp
    UPlatformString.cpp
    UPlatformThreads.cpp
    UPlatformTime.cpp)

# set(SOURCES_DISABLED
#                      )

set(HEADERS
    CCharDescriptor.h
    CCharString.h
    CColor.h
    CDateTime.h
	CFilePath.h
	CheckLeaks.h
    CMutex.h
    CSemaphore.h
    CSerial.h
	CSignal.h
	CSocket.h
    LogFile.h
    stdio_sx.h
    string_sx.h
    TArray.h
    TCharDescriptor.h
    TEnumerator.h
    TPointer.h
    UDeclPlatform.h
    UDeclSpec.h
    UFile.h
    UFloat.h
    UMachine.h
    UMath.h
    UNResult.h
    UOSIncludes.h
    UPlatform.h
    UPlatformIO.h
    UPlatformString.h
    UPlatformThreads.h
    UPlatformTime.h
    UTypes.h
	UWarnings.h)


add_library(${THIS} STATIC ${SOURCES} ${HEADERS})

target_compile_definitions(${THIS} PRIVATE
	SHLIB_PLATFORM
	_WINSOCK_DEPRECATED_NO_WARNINGS )

# find_library( LIB_WS2_32 Ws2_32 )
# find_library( LIB_ADVAPI32 Advapi32 )
# find_library( LIB_MSVCRT msvcrt )

target_link_libraries( ${THIS} Ws2_32 Advapi32 Kernel32 )

add_subdirectory(test)
