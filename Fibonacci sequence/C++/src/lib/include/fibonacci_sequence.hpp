#ifndef FIBONACCI_SEQUENCE_HPP
#define FIBONACCI_SEQUENCE_HPP

#include <vector>

/**
 * \brief Generates Fibonacci sequence numbers.
 *
 * This function generates the n + 1 (0-indexed) first elements of the Fibonacci sequence.
 *
 * \param n The number of Fibonacci sequence numbers to generate.
 * \return A vector containing the Fibonacci sequence numbers.
 */
std::vector<unsigned long long> fibonacciSequence(unsigned int n);

/**
 * \brief Calculates the n-th Fibonacci number.
 *
 * This function calculates the n-th Fibonacci number.
 *
 * \param n The index of the Fibonacci number to calculate.
 * \return The n-th Fibonacci number.
 */
unsigned long long fibonacciNumber(unsigned int n);

/**
 * \brief Calculates the n-th Fibonacci number using recursive relation.
 *
 * This function calculates the n-th Fibonacci number using recursive relation.
 *
 * \param n The index of the Fibonacci number to calculate.
 * \return The n-th Fibonacci number.
 */
unsigned long long fibonacciNumberRecursive(unsigned int n);

#endif // FIBONACCI_SEQUENCE_HPP
