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
add_test(NAME test_p0001 COMMAND stack_tests 1)
