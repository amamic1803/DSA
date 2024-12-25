cmake_minimum_required(VERSION 3.29)

project(GaussianElimination C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy -warnings-as-errors=*)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)
include(CTest)

# Add the library
add_library(gaussian_elimination_lib STATIC
        src/lib/include/gaussian_elimination.h
        src/lib/gaussian_elimination.c
)
target_include_directories(gaussian_elimination_lib PRIVATE src/lib/include)
target_link_libraries(gaussian_elimination_lib m)
set_target_properties(gaussian_elimination_lib PROPERTIES
        OUTPUT_NAME GaussianElimination
        PUBLIC_HEADER src/lib/include/gaussian_elimination.h
)

# Add the tests
add_executable(gaussian_elimination_tests src/tests/tests.h src/tests/tests.c)
target_include_directories(gaussian_elimination_tests PRIVATE src/lib/include)
target_link_libraries(gaussian_elimination_tests gaussian_elimination_lib)
target_link_libraries(gaussian_elimination_tests m)
set_target_properties(gaussian_elimination_tests PROPERTIES
        OUTPUT_NAME gaussian_elimination_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test1 COMMAND gaussian_elimination_tests 1)
add_test(NAME test2 COMMAND gaussian_elimination_tests 2)
add_test(NAME test3 COMMAND gaussian_elimination_tests 3)
add_test(NAME test4 COMMAND gaussian_elimination_tests 4)
add_test(NAME test5 COMMAND gaussian_elimination_tests 5)
add_test(NAME test6 COMMAND gaussian_elimination_tests 6)
add_test(NAME test7 COMMAND gaussian_elimination_tests 7)
add_test(NAME test8 COMMAND gaussian_elimination_tests 8)
