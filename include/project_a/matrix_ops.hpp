
#pragma once

#include <Eigen/Dense>
#include <string>

namespace project_a {

using Matrix = Eigen::MatrixXd;

/**
 * @brief Performs matrix multiplication
 * @param a First matrix
 * @param b Second matrix
 * @return Result of a * b
 * @throws std::invalid_argument if matrix dimensions don't match
 */
Matrix multiply(const Matrix& a, const Matrix& b);

/**
 * @brief Computes the inverse of a matrix
 * @param m Input matrix
 * @return Inverse of the input matrix
 * @throws std::invalid_argument if matrix is not square or is singular
 */
Matrix inverse(const Matrix& m);

/**
 * @brief Formats matrix as string for display
 * @param m Matrix to format
 * @return Formatted string representation of the matrix
 */
std::string format_matrix(const Matrix& m);

} // namespace project_a

