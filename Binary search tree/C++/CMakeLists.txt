cmake_minimum_required(VERSION 3.29)

project(BinarySearchTree CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(binary_search_tree_lib STATIC
        src/lib/include/binary_search_tree.hpp
)
target_include_directories(binary_search_tree_lib PRIVATE src/lib/include)
set_target_properties(binary_search_tree_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME BinarySearchTree
        PUBLIC_HEADER src/lib/include/binary_search_tree.hpp
)

# Add the tests
add_executable(binary_search_tree_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(binary_search_tree_tests PRIVATE src/lib/include)
target_link_libraries(binary_search_tree_tests binary_search_tree_lib)
set_target_properties(binary_search_tree_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME binary_search_tree_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_1 COMMAND binary_search_tree_tests 1)
add_test(NAME test_2 COMMAND binary_search_tree_tests 2)
add_test(NAME test_3 COMMAND binary_search_tree_tests 3)
add_test(NAME test_4 COMMAND binary_search_tree_tests 4)
add_test(NAME test_5 COMMAND binary_search_tree_tests 5)
add_test(NAME test_6 COMMAND binary_search_tree_tests 6)
add_test(NAME test_7 COMMAND binary_search_tree_tests 7)
add_test(NAME test_8 COMMAND binary_search_tree_tests 8)
