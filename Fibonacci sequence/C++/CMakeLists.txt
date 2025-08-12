cmake_minimum_required(VERSION 3.29)

project(FibonacciSequence CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/../../.clang-tidy")
set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/../../.clang-tidy")

include(CTest)


# Add the library
add_library(fibonacci_sequence_lib STATIC
        src/lib/include/fibonacci_sequence.hpp
        src/lib/fibonacci_sequence.cpp
)
target_include_directories(fibonacci_sequence_lib PRIVATE src/lib/include)
set_target_properties(fibonacci_sequence_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME FibonacciSequence
        PUBLIC_HEADER src/lib/include/fibonacci_sequence.hpp
)
target_compile_options(fibonacci_sequence_lib PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(fibonacci_sequence_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(fibonacci_sequence_tests PRIVATE src/lib/include)
target_link_libraries(fibonacci_sequence_tests fibonacci_sequence_lib)
set_target_properties(fibonacci_sequence_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME fibonacci_sequence_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(fibonacci_sequence_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
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
