cmake_minimum_required(VERSION 3.29)

project(JumpSearch C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy -warnings-as-errors=*)
include(CTest)

# Add the library
add_library(jump_search_lib STATIC
        src/lib/include/jump_search.h
        src/lib/jump_search.c
)
target_include_directories(jump_search_lib PRIVATE src/lib/include)
target_link_libraries(jump_search_lib m)
set_target_properties(jump_search_lib PROPERTIES
        OUTPUT_NAME JumpSearch
        PUBLIC_HEADER src/lib/include/jump_search.h
)

# Add the tests
add_executable(jump_search_tests src/tests/tests.h src/tests/tests.c)
target_include_directories(jump_search_tests PRIVATE src/lib/include)
target_link_libraries(jump_search_tests jump_search_lib)
set_target_properties(jump_search_tests PROPERTIES
        OUTPUT_NAME jump_search_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_p0001 COMMAND jump_search_tests 1)
add_test(NAME test_p0002 COMMAND jump_search_tests 2)
add_test(NAME test_p0003 COMMAND jump_search_tests 3)
add_test(NAME test_p0004 COMMAND jump_search_tests 4)
add_test(NAME test_p0005 COMMAND jump_search_tests 5)
add_test(NAME test_p0006 COMMAND jump_search_tests 6)
add_test(NAME test_p0007 COMMAND jump_search_tests 7)
add_test(NAME test_p0008 COMMAND jump_search_tests 8)
add_test(NAME test_p0009 COMMAND jump_search_tests 9)
add_test(NAME test_p0010 COMMAND jump_search_tests 10)
