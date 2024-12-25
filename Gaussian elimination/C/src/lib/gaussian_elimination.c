#include "gaussian_elimination.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>


/**
 * \brief Swaps two rows in a matrix.
 *
 * This function swaps two rows in a matrix.
 *
 * @param i The index of the first row to swap.
 * @param j The index of the second row to swap.
 * @param matrix The matrix to swap rows in.
 * @param n The number of rows in the matrix.
 * @param m The number of columns in the matrix.
 */
static void swap_rows(const int i, const int j, double *matrix, const int n, const int m) {
    if (i == j || i >= n || j >= n) {
        return;
    }
    for (int k = 0; k < m; k++) {
        const double temp = matrix[i * m + k];
        matrix[i * m + k] = matrix[j * m + k];
        matrix[j * m + k] = temp;
    }
}

void gaussian_elimination(double *matrix, const int n, const int m) {
    int h = 0;  // current row
    int k = 0;  // current column
    while (h < n && k < m) {
        // find the pivot (maximum absolute value in the current column)
        int i_max = h;
        double val_max = fabs(matrix[h * m + k]);
        for (int i = h + 1; i < n; i++) {
            const double val = fabs(matrix[i * m + k]);
            if (val > val_max) {
                i_max = i;
                val_max = val;
            }
        }

        if (val_max == 0) {                           // no pivot in this column
            k++;
        } else {
            swap_rows(h, i_max, matrix, n, m);   // swap the pivot row with the current row
            for (int i = h + 1; i < n; i++) {         // perform the elimination
                const double f = matrix[i * m + k] / matrix[h * m + k];
                matrix[i * m + k] = 0;
                for (int j = k + 1; j < m; j++) {
                    matrix[i * m + j] -= matrix[h * m + j] * f;
                }
            }
            h++;
            k++;
        }
    }
}

void gauss_jordan_elimination(double *matrix, int n, int m) {
    gaussian_elimination(matrix, n, m);

    for (int i = n - 1; i >= 0; i--) {
        // find pivot
        int pivot = -1;
        for (int j = 0; j < m; j++) {
            if (matrix[i * m + j] != 0) {
                pivot = j;
                break;
            }
        }
        if (pivot == -1) {  // no pivot in this row
            continue;
        }
        if (matrix[i * m + pivot] != 1) {             // make the pivot row have a leading 1
            const double f = 1 / matrix[i * m + pivot];
            matrix[i * m + pivot] = 1;
            for (int j = pivot + 1; j < m; j++) {
                matrix[i * m + j] *= f;
            }
        }

        // eliminate the pivot column
        for (int k = i - 1; k >= 0; k--) {
            const double f = matrix[k * m + pivot] / matrix[i * m + pivot];
            matrix[k * m + pivot] = 0;
            for (int j = pivot + 1; j < m; j++) {
                matrix[k * m + j] -= matrix[i * m + j] * f;
            }
        }
    }
}

bool linear_system_solver(const double *matrix, int n, int m, double *solution) {
    double *local_matrix = malloc(sizeof(double) * n * m);
    if (local_matrix == NULL) { return false; }
    memcpy(local_matrix, matrix, sizeof(double) * n * m);

    // perform Gauss-Jordan elimination, which will reduce the matrix to reduced row-echelon form
    gauss_jordan_elimination(local_matrix, n, m);

    // check for inconsistent system (a row with all zeros except the last element)
    for (int i = n - 1; i >= 0; i--) {
        bool all_zeros = true;
        for (int j = 0; j < m - 1; j++) {
            if (local_matrix[i * m + j] != 0) {
                all_zeros = false;
                break;
            }
        }
        if (!all_zeros) { break; } // if the row is not all zeros, then rows above cannot be all zeros
        if (local_matrix[i * m + m - 1] != 0) {  // if the row is all zeros except the last element, then the system is inconsistent
            free(local_matrix);
            return false;
        }
    }

    // check that the diagonal elements are all 1 (except last column and possibly zero rows at the bottom)
    for (int i = 0; i < m - 1; i++) {
        if (local_matrix[i * m + i] != 1) {
            free(local_matrix);
            return false;
        }
    }

    // copy the solutions
    for (int i = 0; i < m - 1; i++) {
        solution[i] = local_matrix[i * m + m - 1];
    }

    free(local_matrix);
    return true;
}
