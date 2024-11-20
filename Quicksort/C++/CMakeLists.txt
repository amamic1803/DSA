cmake_minimum_required(VERSION 3.29)

project(Quicksort CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(quicksort_lib STATIC
        src/lib/include/quicksort.hpp
)
target_include_directories(quicksort_lib PRIVATE src/lib/include)
set_target_properties(quicksort_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME quicksort
        PUBLIC_HEADER src/lib/include/quicksort.hpp
)

# Add the tests
add_executable(quicksort_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(quicksort_tests PRIVATE src/lib/include)
target_link_libraries(quicksort_tests quicksort_lib)
set_target_properties(quicksort_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME quicksort_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_1 COMMAND quicksort_tests 1)
add_test(NAME test_2 COMMAND quicksort_tests 2)
add_test(NAME test_3 COMMAND quicksort_tests 3)
add_test(NAME test_4 COMMAND quicksort_tests 4)
add_test(NAME test_5 COMMAND quicksort_tests 5)
add_test(NAME test_6 COMMAND quicksort_tests 6)
add_test(NAME test_7 COMMAND quicksort_tests 7)
add_test(NAME test_8 COMMAND quicksort_tests 8)
add_test(NAME test_9 COMMAND quicksort_tests 9)
add_test(NAME test_10 COMMAND quicksort_tests 10)
