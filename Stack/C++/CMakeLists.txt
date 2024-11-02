cmake_minimum_required(VERSION 3.29)

project(Stack CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(stack_lib STATIC
        src/lib/include/stack.hpp
)
target_include_directories(stack_lib PRIVATE src/lib/include)
set_target_properties(stack_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME stack
        PUBLIC_HEADER src/lib/include/stack.hpp
)

# Add the tests
add_executable(stack_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(stack_tests PRIVATE src/lib/include)
target_link_libraries(stack_tests stack_lib)
set_target_properties(stack_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME stack_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_ListStack1 COMMAND stack_tests ListStack1)
add_test(NAME test_ListStack2 COMMAND stack_tests ListStack2)
add_test(NAME test_ListStack3 COMMAND stack_tests ListStack3)
add_test(NAME test_ListStack4 COMMAND stack_tests ListStack4)
add_test(NAME test_ListStack5 COMMAND stack_tests ListStack5)
add_test(NAME test_ListStack6 COMMAND stack_tests ListStack6)

add_test(NAME test_StaticStack1 COMMAND stack_tests StaticStack1)
add_test(NAME test_StaticStack2 COMMAND stack_tests StaticStack2)
add_test(NAME test_StaticStack3 COMMAND stack_tests StaticStack3)
add_test(NAME test_StaticStack4 COMMAND stack_tests StaticStack4)
add_test(NAME test_StaticStack5 COMMAND stack_tests StaticStack5)
add_test(NAME test_StaticStack6 COMMAND stack_tests StaticStack6)

add_test(NAME test_DynamicStack1 COMMAND stack_tests DynamicStack1)
add_test(NAME test_DynamicStack2 COMMAND stack_tests DynamicStack2)
add_test(NAME test_DynamicStack3 COMMAND stack_tests DynamicStack3)
add_test(NAME test_DynamicStack4 COMMAND stack_tests DynamicStack4)
add_test(NAME test_DynamicStack5 COMMAND stack_tests DynamicStack5)
add_test(NAME test_DynamicStack6 COMMAND stack_tests DynamicStack6)
