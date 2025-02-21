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
add_test(NAME test_GraphAdjacencyList1 COMMAND graph_tests GraphAdjacencyList1)
add_test(NAME test_GraphAdjacencyList2 COMMAND graph_tests GraphAdjacencyList2)
add_test(NAME test_GraphAdjacencyList3 COMMAND graph_tests GraphAdjacencyList3)
add_test(NAME test_GraphAdjacencyList4 COMMAND graph_tests GraphAdjacencyList4)
add_test(NAME test_GraphAdjacencyList5 COMMAND graph_tests GraphAdjacencyList5)
add_test(NAME test_GraphAdjacencyMatrix1 COMMAND graph_tests GraphAdjacencyMatrix1)
add_test(NAME test_GraphAdjacencyMatrix2 COMMAND graph_tests GraphAdjacencyMatrix2)
add_test(NAME test_GraphAdjacencyMatrix3 COMMAND graph_tests GraphAdjacencyMatrix3)
add_test(NAME test_GraphAdjacencyMatrix4 COMMAND graph_tests GraphAdjacencyMatrix4)
add_test(NAME test_GraphAdjacencyMatrix5 COMMAND graph_tests GraphAdjacencyMatrix5)
add_test(NAME test_GraphIncidenceMatrix1 COMMAND graph_tests GraphIncidenceMatrix1)
add_test(NAME test_GraphIncidenceMatrix2 COMMAND graph_tests GraphIncidenceMatrix2)
add_test(NAME test_GraphIncidenceMatrix3 COMMAND graph_tests GraphIncidenceMatrix3)
add_test(NAME test_GraphIncidenceMatrix4 COMMAND graph_tests GraphIncidenceMatrix4)
add_test(NAME test_GraphIncidenceMatrix5 COMMAND graph_tests GraphIncidenceMatrix5)
