set(THIS GS8)


set(SOURCES main.cpp)
set(HEADERS main.hpp)

add_executable(${THIS} ${SOURCES} ${HEADERS})
add_dependencies(${THIS} Platform Common)
