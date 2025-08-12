cmake_minimum_required(VERSION 3.29)

project(MergeSort CXX)

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
add_library(merge_sort_lib STATIC
        src/lib/include/merge_sort.hpp
)
target_include_directories(merge_sort_lib PRIVATE src/lib/include)
set_target_properties(merge_sort_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME merge_sort
        PUBLIC_HEADER src/lib/include/merge_sort.hpp
)
target_compile_options(merge_sort_lib PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(merge_sort_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(merge_sort_tests PRIVATE src/lib/include)
target_link_libraries(merge_sort_tests merge_sort_lib)
set_target_properties(merge_sort_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME merge_sort_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(merge_sort_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(NAME test_1 COMMAND merge_sort_tests 1)
add_test(NAME test_2 COMMAND merge_sort_tests 2)
add_test(NAME test_3 COMMAND merge_sort_tests 3)
add_test(NAME test_4 COMMAND merge_sort_tests 4)
add_test(NAME test_5 COMMAND merge_sort_tests 5)
add_test(NAME test_6 COMMAND merge_sort_tests 6)
add_test(NAME test_7 COMMAND merge_sort_tests 7)
add_test(NAME test_8 COMMAND merge_sort_tests 8)
add_test(NAME test_9 COMMAND merge_sort_tests 9)
add_test(NAME test_10 COMMAND merge_sort_tests 10)
