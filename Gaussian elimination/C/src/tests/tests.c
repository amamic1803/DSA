#include "gaussian_elimination.h"
#include "tests.h"
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define DOUBLE_EPSILON 1e-9


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

    int test_result = 0;
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
        case 8:
            test_result = test8();
            break;
        default:
            return -5;
    }

    return test_result ? 0 : -1;
}

int are_matrices_equal(const double *matrix1, const double *matrix2, const int n, const int m) {
    for (int i = 0; i < n * m; i++) {
        if (fabs(matrix1[i] - matrix2[i]) > DOUBLE_EPSILON) {
            return 0;
        }
    }
    return 1;
}

int test1() {
    double matrix[3][4] = {
            {1, 3, 1, 9},
            {1, 1, -1, 1},
            {3, 11, 5, 35}
    };
    double expected[3][4] = {
            {3, 11, 5, 35},
            {0, -8.0/3.0, -8.0/3.0, -32.0/3.0},
            {0, 0, 0, 0}
    };
    gaussian_elimination(&matrix[0][0], 3, 4);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 4);
}

int test2() {
    double matrix[3][4] = {
            {1, 3, 1, 9},
            {1, 1, -1, 1},
            {3, 11, 5, 35}
    };
    double expected[3][4] = {
            {1, 0, -2, -3},
            {0, 1, 1, 4},
            {0, 0, 0, 0}
    };
    gauss_jordan_elimination(&matrix[0][0], 3, 4);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 4);
}

int test3() {
    double system[3][4] = {
            {2, 1, -1, 8},
            {-3, -1, 2, -11},
            {-2, 1, 2, -3}
    };
    double solution[3];
    double expected_solution[3] = {2, 3, -1};
    if (!linear_system_solver(&system[0][0], 3, 4, solution)) {
        return 0;
    }
    return are_matrices_equal(solution, expected_solution, 1, 3);
}

int test4() {
    double matrix[3][4] = {
            {2, 1, -1, 8},
            {-3, -1, 2, -11},
            {-2, 1, 2, -3}
    };
    double expected[3][4] = {
            {-3, -1, 2, -11},
            {0, 5.0/3.0, 2.0/3.0, 13.0/3.0},
            {0, 0, 1.0/5.0, -1.0/5.0}
    };
    gaussian_elimination(&matrix[0][0], 3, 4);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 4);
}

int test5() {
    double matrix[3][4] = {
            {-3, -1, 2, -11},
            {0, 5.0/3.0, 2.0/3.0, 13.0/3.0},
            {0, 0, 1.0/5.0, -1.0/5.0}
    };
    double expected[3][4] = {
            {1, 0, 0, 2},
            {0, 1, 0, 3},
            {0, 0, 1, -1}
    };
    gauss_jordan_elimination(&matrix[0][0], 3, 4);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 4);
}

int test6() {
    double matrix[3][6] = {
            {2, -1, 0, 1, 0, 0},
            {-1, 2, -1, 0, 1, 0},
            {0, -1, 2, 0, 0, 1}
    };
    double expected[3][6] = {
            {1, 0, 0, 0.75, 0.5, 0.25},
            {0, 1, 0, 0.5, 1, 0.5},
            {0, 0, 1, 0.25, 0.5, 0.75}
    };
    gauss_jordan_elimination(&matrix[0][0], 3, 6);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 6);
}

int test7() {
    double system[4][5] = {
            {2, 1, 0, 2, 4},
            {0, 1, 0, 3, 3},
            {-1, 2, 0, 4, 3},
            {0, 1, 7, 2, 2},
    };
    double solution[4];
    double expected_solution[4] = {1, 0, 0, 1};
    if (!linear_system_solver(&system[0][0], 4, 5, solution)) {
        return 0;
    }
    return are_matrices_equal(solution, expected_solution, 1, 4);
}

int test8() {
    double matrix[3][5] = {
            {-1, 2, 6, 7, 15},
            {3, -6, 0, -3, -9},
            {1, 0, 6, -1, 5},
    };
    double expected[3][5] = {
            {1, 0, 0, -7, -7},
            {0, 1, 0, -3, -2},
            {0, 0, 1, 1, 2},
    };
    gauss_jordan_elimination(&matrix[0][0], 3, 5);
    return are_matrices_equal(&matrix[0][0], &expected[0][0], 3, 5);
}
