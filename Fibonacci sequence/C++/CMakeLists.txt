cmake_minimum_required(VERSION 3.29)

project(FibonacciSequence CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_CLANG_TIDY clang-tidy -warnings-as-errors=*)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)
include(CTest)

# Add the library
add_library(fibonacci_sequence_lib STATIC
        src/lib/include/fibonacci_sequence.hpp
        src/lib/fibonacci_sequence.cpp
)
target_include_directories(fibonacci_sequence_lib PRIVATE src/lib/include)
set_target_properties(fibonacci_sequence_lib PROPERTIES
        OUTPUT_NAME FibonacciSequence
        PUBLIC_HEADER src/lib/include/fibonacci_sequence.hpp
)

# Add the tests
add_executable(fibonacci_sequence_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(fibonacci_sequence_tests PRIVATE src/lib/include)
target_link_libraries(fibonacci_sequence_tests fibonacci_sequence_lib)
set_target_properties(fibonacci_sequence_tests PROPERTIES
        OUTPUT_NAME fibonacci_sequence_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME test_seq1 COMMAND fibonacci_sequence_tests seq1)
add_test(NAME test_seq2 COMMAND fibonacci_sequence_tests seq2)
add_test(NAME test_seq3 COMMAND fibonacci_sequence_tests seq3)
add_test(NAME test_seq4 COMMAND fibonacci_sequence_tests seq4)
add_test(NAME test_seq5 COMMAND fibonacci_sequence_tests seq5)
add_test(NAME test_num1 COMMAND fibonacci_sequence_tests num1)
add_test(NAME test_num2 COMMAND fibonacci_sequence_tests num2)
add_test(NAME test_num3 COMMAND fibonacci_sequence_tests num3)
add_test(NAME test_num4 COMMAND fibonacci_sequence_tests num4)
add_test(NAME test_num5 COMMAND fibonacci_sequence_tests num5)
add_test(NAME test_num6 COMMAND fibonacci_sequence_tests num6)
