#include "binary_search.h"
#include "tests.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>


int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    char *endptr;
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

    const int problem_number = val;

    bool test_result;
    switch (problem_number) {
        case 1:
            test_result = test1();
            break;
        case 2:
            test_result = test2();
            break;
        case 3:
            test_result = test3();
            break;
        case 4:
            test_result = test4();
            break;
        case 5:
            test_result = test5();
            break;
        case 6:
            test_result = test6();
            break;
        case 7:
            test_result = test7();
            break;
        default:
            return -5;
    }

    return test_result ? 0 : -1;
}

bool test1() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 3;
    const int expected = 2;

    return expected == binarySearch(arr, size, target);
}

bool test2() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 1;
    const int expected = 0;

    return expected == binarySearch(arr, size, target);
}

bool test3() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 5;
    const int expected = 4;

    return expected == binarySearch(arr, size, target);
}

bool test4() {
    const int arr[] = {1, 2, 3, 4, 5};
    const int size = 5;
    const int target = 6;
    const int expected = -1;

    return expected == binarySearch(arr, size, target);
}

bool test5() {
    const int arr[] = {1};
    const int size = 0;  // simulate an empty array
    const int target = 1;
    const int expected = -1;

    return expected == binarySearch(arr, size, target);
}

bool test6() {
    const int arr[] = {1};
    const int size = 1;
    const int target = 1;
    const int expected = 0;

    return expected == binarySearch(arr, size, target);
}

bool test7() {
    const int arr[] = {1};
    const int size = 1;
    const int target = 2;
    const int expected = -1;

    return expected == binarySearch(arr, size, target);
}
