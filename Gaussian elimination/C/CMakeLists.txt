cmake_minimum_required(VERSION 3.29)

project(GaussianElimination C)

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
add_library(gaussian_elimination_lib STATIC
        src/lib/include/gaussian_elimination.h
        src/lib/gaussian_elimination.c
)
target_include_directories(gaussian_elimination_lib PRIVATE src/lib/include)
target_link_libraries(gaussian_elimination_lib
        $<$<PLATFORM_ID:Linux>:m>
)
set_target_properties(gaussian_elimination_lib PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        OUTPUT_NAME GaussianElimination
        PUBLIC_HEADER src/lib/include/gaussian_elimination.h
)
target_compile_options(gaussian_elimination_lib PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(gaussian_elimination_tests src/tests/tests.h src/tests/tests.c)
target_include_directories(gaussian_elimination_tests PRIVATE src/lib/include)
target_link_libraries(gaussian_elimination_tests gaussian_elimination_lib)
target_link_libraries(gaussian_elimination_tests
        $<$<PLATFORM_ID:Linux>:m>
)
set_target_properties(gaussian_elimination_tests PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        OUTPUT_NAME gaussian_elimination_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(gaussian_elimination_tests PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(NAME test1 COMMAND gaussian_elimination_tests 1)
add_test(NAME test2 COMMAND gaussian_elimination_tests 2)
add_test(NAME test3 COMMAND gaussian_elimination_tests 3)
add_test(NAME test4 COMMAND gaussian_elimination_tests 4)
add_test(NAME test5 COMMAND gaussian_elimination_tests 5)
add_test(NAME test6 COMMAND gaussian_elimination_tests 6)
add_test(NAME test7 COMMAND gaussian_elimination_tests 7)
add_test(NAME test8 COMMAND gaussian_elimination_tests 8)
