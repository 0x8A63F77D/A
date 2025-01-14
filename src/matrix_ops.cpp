
#include "project_a/matrix_ops.hpp"
#include <fmt/format.h>
#include <stdexcept>

namespace project_a {

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.cols() != b.rows()) {
        throw std::invalid_argument(
            fmt::format("Matrix dimensions mismatch: ({}, {}) * ({}, {})",
                       a.rows(), a.cols(), b.rows(), b.cols()));
    }
    return a * b;
}

Matrix inverse(const Matrix& m) {
    if (m.rows() != m.cols()) {
        throw std::invalid_argument(
            fmt::format("Matrix must be square for inverse: ({}, {})",
                       m.rows(), m.cols()));
    }
    return m.inverse();
}

std::string format_matrix(const Matrix& m) {
    std::string result = fmt::format("Matrix {}x{}:\n", m.rows(), m.cols());
    
    // Format each row
    for (Eigen::Index i = 0; i < m.rows(); ++i) {
        result += "[ ";
        for (Eigen::Index j = 0; j < m.cols(); ++j) {
            result += fmt::format("{:8.3f} ", m(i, j));
        }
        result += "]\n";
    }
    
    return result;
}

} // namespace project_a

