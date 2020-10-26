set(THIS GadgetTests)
set(LIB_DEPS Platform Common VDraw Gadget)



file(GLOB TEST_SOURCES LIST_DIRECTORIES false *_tests.cpp)
set(SOURCES ${TEST_SOURCES})

set(HEADERS
	iggy.h)


foreach(file ${TEST_SOURCES})
	set(name)
	get_filename_component(name ${file} NAME_WE)
	set(tname "${THIS}_${name}")
	add_executable("${tname}"
			${file}
			)
	add_dependencies("${tname}" ${LIB_DEPS})
	target_link_libraries("${tname}" gtest_main ${LIB_DEPS})
	add_test(NAME ${name} COMMAND "${tname}")
endforeach()
