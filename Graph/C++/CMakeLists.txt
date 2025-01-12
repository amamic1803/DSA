cmake_minimum_required(VERSION 3.29)

project(Graph CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
include(CTest)

# Add the library
add_library(graph_lib STATIC
        src/lib/include/graph.hpp
)
target_include_directories(graph_lib PRIVATE src/lib/include)
set_target_properties(graph_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME graph_lib
        PUBLIC_HEADER src/lib/include/graph.hpp
)

# Add the tests
add_executable(graph_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(graph_tests PRIVATE src/lib/include)
target_link_libraries(graph_tests graph_lib)
set_target_properties(graph_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME graph_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_SinglyLinkedList1 COMMAND graph_tests SinglyLinkedList1)
add_test(NAME test_SinglyLinkedList2 COMMAND graph_tests SinglyLinkedList2)
add_test(NAME test_SinglyLinkedList3 COMMAND graph_tests SinglyLinkedList3)
add_test(NAME test_SinglyLinkedList4 COMMAND graph_tests SinglyLinkedList4)
add_test(NAME test_SinglyLinkedList5 COMMAND graph_tests SinglyLinkedList5)
add_test(NAME test_SinglyLinkedList6 COMMAND graph_tests SinglyLinkedList6)
add_test(NAME test_DoublyLinkedList1 COMMAND graph_tests DoublyLinkedList1)
add_test(NAME test_DoublyLinkedList2 COMMAND graph_tests DoublyLinkedList2)
add_test(NAME test_DoublyLinkedList3 COMMAND graph_tests DoublyLinkedList3)
add_test(NAME test_DoublyLinkedList4 COMMAND graph_tests DoublyLinkedList4)
add_test(NAME test_DoublyLinkedList5 COMMAND graph_tests DoublyLinkedList5)
add_test(NAME test_DoublyLinkedList6 COMMAND graph_tests DoublyLinkedList6)
