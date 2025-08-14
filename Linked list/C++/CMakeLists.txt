cmake_minimum_required(VERSION 3.29)

project(LinkedList CXX)

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
add_library(linked_list_lib STATIC
        src/lib/include/linked_list.hpp
)
target_include_directories(linked_list_lib PRIVATE src/lib/include)
set_target_properties(linked_list_lib PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linked_list
        PUBLIC_HEADER src/lib/include/linked_list.hpp
)
target_compile_options(linked_list_lib PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

# Add the tests
add_executable(linked_list_tests src/tests/tests.hpp src/tests/tests.cpp)
target_include_directories(linked_list_tests PRIVATE src/lib/include)
target_link_libraries(linked_list_tests linked_list_lib)
set_target_properties(linked_list_tests PROPERTIES
        LANGUAGE CXX
        LINKER_LANGUAGE CXX
        OUTPUT_NAME linked_list_tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
target_compile_options(linked_list_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
)

add_test(NAME test_SinglyLinkedList1 COMMAND linked_list_tests SinglyLinkedList1)
add_test(NAME test_SinglyLinkedList2 COMMAND linked_list_tests SinglyLinkedList2)
add_test(NAME test_SinglyLinkedList3 COMMAND linked_list_tests SinglyLinkedList3)
add_test(NAME test_SinglyLinkedList4 COMMAND linked_list_tests SinglyLinkedList4)
add_test(NAME test_SinglyLinkedList5 COMMAND linked_list_tests SinglyLinkedList5)
add_test(NAME test_SinglyLinkedList6 COMMAND linked_list_tests SinglyLinkedList6)
add_test(NAME test_DoublyLinkedList1 COMMAND linked_list_tests DoublyLinkedList1)
add_test(NAME test_DoublyLinkedList2 COMMAND linked_list_tests DoublyLinkedList2)
add_test(NAME test_DoublyLinkedList3 COMMAND linked_list_tests DoublyLinkedList3)
add_test(NAME test_DoublyLinkedList4 COMMAND linked_list_tests DoublyLinkedList4)
add_test(NAME test_DoublyLinkedList5 COMMAND linked_list_tests DoublyLinkedList5)
add_test(NAME test_DoublyLinkedList6 COMMAND linked_list_tests DoublyLinkedList6)
