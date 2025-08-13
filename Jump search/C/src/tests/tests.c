#include "jump_search.h"
#include "tests.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>


int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    char *endptr = nullptr;
    errno = 0; // To distinguish success/failure after call
    const long val = strtol(argv[1], &endptr, 10);

    // Check for various possible errors
    if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) {
        return -1; // Out of range
    }
    if (errno != 0 && val == 0) {
        return -2; // Conversion error
    }
    if (endptr == argv[1]) {
        return -3; // No digits were found
    }
    if (*endptr != '\0') {
        return -4; // Further characters after number
    }

    // Check if the value fits in an int
    if (val > INT_MAX || val < INT_MIN) {
        return -5; // Out of int range
    }

    const int problem_number = (int) val;

    bool test_result = false;
    switch (problem_number) {
        case 1:
            test_result = test01();
            break;
        case 2:
            test_result = test02();
            break;
        case 3:
            test_result = test03();
            break;
        case 4:
            test_result = test04();
            break;
        case 5:
            test_result = test05();
            break;
        case 6:
            test_result = test06();
            break;
        case 7:
            test_result = test07();
            break;
        case 8:
            test_result = test08();
            break;
        case 9:
            test_result = test09();
            break;
        case 10:
            test_result = test10();
            break;
        default:
            return -5;
    }

    return (int) test_result == 1 ? 0 : -1;
}

bool test01() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 3;
    const int expected = 2;

    return expected == jumpSearch(arr, size, target);
}

bool test02() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 1;
    const int expected = 0;

    return expected == jumpSearch(arr, size, target);
}

bool test03() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 5;
    const int expected = 4;

    return expected == jumpSearch(arr, size, target);
}

bool test04() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 6;
    const int expected = -1;

    return expected == jumpSearch(arr, size, target);
}

bool test05() {
    const int arr[] = {1};
    const int size = 0;  // simulate an empty array
    const int target = 1;
    const int expected = -1;

    return expected == jumpSearch(arr, size, target);
}

bool test06() {
    const int arr[] = {1};
    const int size = 1;
    const int target = 1;
    const int expected = 0;

    return expected == jumpSearch(arr, size, target);
}

bool test07() {
    const int arr[] = {1};
    const int size = 1;
    const int target = 2;
    const int expected = -1;

    return expected == jumpSearch(arr, size, target);
}

bool test08() {
    const int arr[] = {1, 2};
    const int size = 2;
    const int target = 2;
    const int expected = 1;

    return expected == jumpSearch(arr, size, target);
}

bool test09() {
    const int size = 100;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < size; i++) {
        if (i != jumpSearch(arr, size, i)) {
            return false;
        }
    }

    return true;
}

bool test10() {
    const int size = 1000;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i * 2;
    }

    for (int i = 0; i < size; i++) {
        if (i != jumpSearch(arr, size, i * 2)) {
            return false;
        }
    }

    return true;
}
