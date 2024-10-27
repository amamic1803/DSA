cmake_minimum_required(VERSION 3.29)

project(LinkedList CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(linked_list_lib STATIC
        src/lib/include/linked_list.hpp
)
target_include_directories(linked_list_lib PRIVATE src/lib/include)
set_target_properties(linked_list_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linked_list
        PUBLIC_HEADER src/lib/include/linked_list.hpp
)

# Add the tests
add_executable(linked_list_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(linked_list_tests PRIVATE src/lib/include)
target_link_libraries(linked_list_tests linked_list_lib)
set_target_properties(linked_list_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linked_list_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_p0001 COMMAND linked_list_tests 1)

add_executable(linked_list_main src/main.cpp)
target_include_directories(linked_list_main PRIVATE src/lib/include)
target_link_libraries(linked_list_main linked_list_lib)
