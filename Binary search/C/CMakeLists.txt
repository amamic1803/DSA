cmake_minimum_required(VERSION 3.29)

project(BinarySearch C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy -warnings-as-errors=*)
include(CTest)

# Add the library
add_library(binary_search_lib STATIC
        src/lib/include/binary_search.h
        src/lib/binary_search.c
)
target_include_directories(binary_search_lib PRIVATE src/lib/include)
set_target_properties(binary_search_lib PROPERTIES
        OUTPUT_NAME BinarySearch
        PUBLIC_HEADER src/lib/include/binary_search.h
)

# Add the tests
add_executable(binary_search_tests src/tests/tests.h src/tests/tests.c)
target_include_directories(binary_search_tests PRIVATE src/lib/include)
target_link_libraries(binary_search_tests binary_search_lib)
set_target_properties(binary_search_tests PROPERTIES
        OUTPUT_NAME binary_search_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test1 COMMAND binary_search_tests 1)
add_test(NAME test2 COMMAND binary_search_tests 2)
add_test(NAME test3 COMMAND binary_search_tests 3)
add_test(NAME test4 COMMAND binary_search_tests 4)
add_test(NAME test5 COMMAND binary_search_tests 5)
add_test(NAME test6 COMMAND binary_search_tests 6)
add_test(NAME test7 COMMAND binary_search_tests 7)
