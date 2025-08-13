cmake_minimum_required(VERSION 3.29)

project(JumpSearch C)

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
add_library(jump_search_lib STATIC
        src/lib/include/jump_search.h
        src/lib/jump_search.c
)
target_include_directories(jump_search_lib PRIVATE src/lib/include)
target_link_libraries(jump_search_lib
        $<$<PLATFORM_ID:Linux>:m>
)
set_target_properties(jump_search_lib PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        OUTPUT_NAME JumpSearch
        PUBLIC_HEADER src/lib/include/jump_search.h
)
target_compile_options(jump_search_lib PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(jump_search_tests src/tests/tests.h src/tests/tests.c)
target_include_directories(jump_search_tests PRIVATE src/lib/include)
target_link_libraries(jump_search_tests jump_search_lib)
set_target_properties(jump_search_tests PROPERTIES
        LANGUAGE C
        LINKER_LANGUAGE C
        OUTPUT_NAME jump_search_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(jump_search_tests PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(NAME test01 COMMAND jump_search_tests 1)
add_test(NAME test02 COMMAND jump_search_tests 2)
add_test(NAME test03 COMMAND jump_search_tests 3)
add_test(NAME test04 COMMAND jump_search_tests 4)
add_test(NAME test05 COMMAND jump_search_tests 5)
add_test(NAME test06 COMMAND jump_search_tests 6)
add_test(NAME test07 COMMAND jump_search_tests 7)
add_test(NAME test08 COMMAND jump_search_tests 8)
add_test(NAME test09 COMMAND jump_search_tests 9)
add_test(NAME test10 COMMAND jump_search_tests 10)
