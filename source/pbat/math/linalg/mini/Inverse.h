#ifndef PBAT_MATH_LINALG_MINI_INVERSE_H
#define PBAT_MATH_LINALG_MINI_INVERSE_H

#include "Concepts.h"
#include "Matrix.h"
#include "pbat/HostDevice.h"

#include <type_traits>
#include <utility>

namespace pbat {
namespace math {
namespace linalg {
namespace mini {

template <class /*CMatrix*/ TMatrix>
PBAT_HOST_DEVICE
    SMatrix<typename TMatrix::Scalar, TMatrix::RowsAtCompileTime, TMatrix::ColsAtCompileTime>
    Inverse(TMatrix const& A)
{
    using InputMatrixType = TMatrix;
    static_assert(
        InputMatrixType::RowsAtCompileTime < 4 and InputMatrixType::RowsAtCompileTime > 1,
        "Cannot compute inverse of large matrix or scalar");
    static_assert(
        InputMatrixType::RowsAtCompileTime == InputMatrixType::ColsAtCompileTime,
        "Cannot compute inverse of non-square matrix");
    using MatrixType = SMatrix<
        typename InputMatrixType::Scalar,
        InputMatrixType::RowsAtCompileTime,
        InputMatrixType::ColsAtCompileTime>;
    MatrixType Ainv{};
    if constexpr (MatrixType::RowsAtCompileTime == 2)
    {
        auto const a0 = 1.0 / (A(0, 0) * A(1, 1) - A(1, 0) * A(0, 1));
        Ainv(0, 0)    = a0 * A(1, 1);
        Ainv(1, 0)    = -a0 * A(1, 0);
        Ainv(0, 1)    = -a0 * A(0, 1);
        Ainv(1, 1)    = a0 * A(0, 0);
    }
    if constexpr (MatrixType::RowsAtCompileTime == 3)
    {
        auto const a0 = A(1, 1) * A(2, 2);
        auto const a1 = A(2, 1) * A(1, 2);
        auto const a2 = A(1, 0) * A(2, 1);
        auto const a3 = A(1, 0) * A(2, 2);
        auto const a4 = A(2, 0) * A(1, 1);
        auto const a5 = 1.0 / (a0 * A(0, 0) - a1 * A(0, 0) + a2 * A(0, 2) - a3 * A(0, 1) -
                               a4 * A(0, 2) + A(2, 0) * A(0, 1) * A(1, 2));
        Ainv(0, 0)    = a5 * (a0 - a1);
        Ainv(1, 0)    = a5 * (-a3 + A(2, 0) * A(1, 2));
        Ainv(2, 0)    = a5 * (a2 - a4);
        Ainv(0, 1)    = a5 * (-A(0, 1) * A(2, 2) + A(2, 1) * A(0, 2));
        Ainv(1, 1)    = a5 * (A(0, 0) * A(2, 2) - A(2, 0) * A(0, 2));
        Ainv(2, 1)    = a5 * (-A(0, 0) * A(2, 1) + A(2, 0) * A(0, 1));
        Ainv(0, 2)    = a5 * (A(0, 1) * A(1, 2) - A(1, 1) * A(0, 2));
        Ainv(1, 2)    = a5 * (-A(0, 0) * A(1, 2) + A(1, 0) * A(0, 2));
        Ainv(2, 2)    = a5 * (A(0, 0) * A(1, 1) - A(1, 0) * A(0, 1));
    }
    return Ainv;
}

} // namespace mini
} // namespace linalg
} // namespace math
} // namespace pbat

#endif // PBAT_MATH_LINALG_MINI_INVERSE_H