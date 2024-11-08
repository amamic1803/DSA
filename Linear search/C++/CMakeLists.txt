cmake_minimum_required(VERSION 3.29)

project(LinearSearch CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(linear_search_lib STATIC
        src/lib/include/linear_search.hpp
)
target_include_directories(linear_search_lib PRIVATE src/lib/include)
set_target_properties(linear_search_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linear_search
        PUBLIC_HEADER src/lib/include/linear_search.hpp
)

# Add the tests
add_executable(linear_search_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(linear_search_tests PRIVATE src/lib/include)
target_link_libraries(linear_search_tests linear_search_lib)
set_target_properties(linear_search_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linear_search_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_1 COMMAND linear_search_tests 1)
add_test(NAME test_2 COMMAND linear_search_tests 2)
add_test(NAME test_3 COMMAND linear_search_tests 3)
add_test(NAME test_4 COMMAND linear_search_tests 4)
add_test(NAME test_5 COMMAND linear_search_tests 5)
