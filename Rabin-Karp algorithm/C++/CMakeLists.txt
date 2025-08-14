cmake_minimum_required(VERSION 3.29)

project(RabinKarp CXX)

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
add_library(rabin_karp_lib STATIC
        src/lib/include/rabin_karp.hpp
        src/lib/include/rabin_karp.cpp
)
target_include_directories(rabin_karp_lib PRIVATE src/lib/include)
set_target_properties(rabin_karp_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME rabin_karp_lib
        PUBLIC_HEADER src/lib/include/rabin_karp.hpp
)
target_compile_options(rabin_karp_lib PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(rabin_karp_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(rabin_karp_tests PRIVATE src/lib/include)
target_link_libraries(rabin_karp_tests rabin_karp_lib)
set_target_properties(rabin_karp_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME rabin_karp_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(rabin_karp_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(NAME test_1 COMMAND rabin_karp_tests 1)
add_test(NAME test_2 COMMAND rabin_karp_tests 2)
add_test(NAME test_3 COMMAND rabin_karp_tests 3)
add_test(NAME test_4 COMMAND rabin_karp_tests 4)
add_test(NAME test_5 COMMAND rabin_karp_tests 5)
add_test(NAME test_6 COMMAND rabin_karp_tests 6)
add_test(NAME test_7 COMMAND rabin_karp_tests 7)
add_test(NAME test_8 COMMAND rabin_karp_tests 8)
add_test(NAME test_9 COMMAND rabin_karp_tests 9)
add_test(NAME test_10 COMMAND rabin_karp_tests 10)
