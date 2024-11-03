cmake_minimum_required(VERSION 3.29)

project(Queue CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(queue_lib STATIC
        src/lib/include/queue.hpp
)
target_include_directories(queue_lib PRIVATE src/lib/include)
set_target_properties(queue_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME queue
        PUBLIC_HEADER src/lib/include/queue.hpp
)

# Add the tests
add_executable(queue_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(queue_tests PRIVATE src/lib/include)
target_link_libraries(queue_tests queue_lib)
set_target_properties(queue_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME queue_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME ListQueue1 COMMAND queue_tests ListQueue1)
add_test(NAME ListQueue2 COMMAND queue_tests ListQueue2)
add_test(NAME ListQueue3 COMMAND queue_tests ListQueue3)
add_test(NAME ListQueue4 COMMAND queue_tests ListQueue4)
add_test(NAME ListQueue5 COMMAND queue_tests ListQueue5)
add_test(NAME StaticQueue1 COMMAND queue_tests StaticQueue1)
add_test(NAME StaticQueue2 COMMAND queue_tests StaticQueue2)
add_test(NAME StaticQueue3 COMMAND queue_tests StaticQueue3)
add_test(NAME StaticQueue4 COMMAND queue_tests StaticQueue4)
add_test(NAME StaticQueue5 COMMAND queue_tests StaticQueue5)
add_test(NAME DynamicQueue1 COMMAND queue_tests DynamicQueue1)
add_test(NAME DynamicQueue2 COMMAND queue_tests DynamicQueue2)
add_test(NAME DynamicQueue3 COMMAND queue_tests DynamicQueue3)
add_test(NAME DynamicQueue4 COMMAND queue_tests DynamicQueue4)
add_test(NAME DynamicQueue5 COMMAND queue_tests DynamicQueue5)
