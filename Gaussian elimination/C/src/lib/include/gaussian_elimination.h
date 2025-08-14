#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

/**
 * \brief Performs a Gaussian elimination on a matrix.
 *
 * This function performs a Gaussian elimination on a matrix to reduce it to a row-echelon form.
 *
 * @param matrix The matrix to reduce.
 * @param n The number of rows in the matrix.
 * @param m The number of columns in the matrix.
 */
void gaussian_elimination(double *matrix, int n, int m);

/**
 * \brief Performs a Gauss-Jordan elimination on a matrix.
 *
 * This function performs a Gauss-Jordan elimination on a matrix to reduce it to a reduced row-echelon form.
 *
 * @param matrix The matrix to reduce.
 * @param n The number of rows in the matrix.
 * @param m The number of columns in the matrix.
 */
void gauss_jordan_elimination(double *matrix, int n, int m);

/**
 * \brief Solves a linear system of equations.
 *
 * This function solves a linear system of equations using Gaussian elimination.
 *
 * @param matrix The augmented matrix (rightmost column represents the constants, right-hand side of the equations) of the system of equations.
 * @param n The number of rows in the matrix.
 * @param m The number of columns in the matrix.
 * @param solution The array to store the solutions in (should be of size m - 1).
 * @return true if the system was solved successfully, false otherwise.
 */
bool linear_system_solver(const double *matrix, int n, int m, double *solution);

#endif // GAUSSIAN_ELIMINATION_H
