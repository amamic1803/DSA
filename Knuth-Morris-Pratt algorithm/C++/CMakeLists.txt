cmake_minimum_required(VERSION 3.29)

project(KnuthMorrisPratt CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(knuth_morris_pratt_lib STATIC
        src/lib/include/knuth_morris_pratt.hpp
        src/lib/include/knuth_morris_pratt.cpp
)
target_include_directories(knuth_morris_pratt_lib PRIVATE src/lib/include)
set_target_properties(knuth_morris_pratt_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME knuth_morris_pratt_lib
        PUBLIC_HEADER src/lib/include/knuth_morris_pratt.hpp
)

# Add the tests
add_executable(knuth_morris_pratt_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(knuth_morris_pratt_tests PRIVATE src/lib/include)
target_link_libraries(knuth_morris_pratt_tests knuth_morris_pratt_lib)
set_target_properties(knuth_morris_pratt_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME knuth_morris_pratt_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_1 COMMAND knuth_morris_pratt_tests 1)
add_test(NAME test_2 COMMAND knuth_morris_pratt_tests 2)
add_test(NAME test_3 COMMAND knuth_morris_pratt_tests 3)
add_test(NAME test_4 COMMAND knuth_morris_pratt_tests 4)
add_test(NAME test_5 COMMAND knuth_morris_pratt_tests 5)
add_test(NAME test_6 COMMAND knuth_morris_pratt_tests 6)
add_test(NAME test_7 COMMAND knuth_morris_pratt_tests 7)
add_test(NAME test_8 COMMAND knuth_morris_pratt_tests 8)
add_test(NAME test_9 COMMAND knuth_morris_pratt_tests 9)
add_test(NAME test_10 COMMAND knuth_morris_pratt_tests 10)
