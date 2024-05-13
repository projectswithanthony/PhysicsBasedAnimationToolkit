#ifndef PBA_COMMON_CONCEPTS_H
#define PBA_COMMON_CONCEPTS_H

#include "pba/aliases.h"

#include <concepts>
#include <iterator>
#include <ranges>
#include <type_traits>

namespace pba {
namespace common {

template <class R>
concept CIndexRange = std::ranges::range<R> && std::is_integral_v<std::ranges::range_value_t<R>>;

template <class R>
concept CContiguousIndexRange =
    CIndexRange<R> && std::ranges::sized_range<R> && std::ranges::contiguous_range<R>;

template <class R>
concept CArithmeticRange =
    std::ranges::range<R> && std::is_arithmetic_v<std::ranges::range_value_t<R>>;

template <class R>
concept CContiguousArithmeticRange =
    CArithmeticRange<R> && std::ranges::sized_range<R> && std::ranges::contiguous_range<R>;

template <class R>
concept CContiguousArithmeticMatrixRange = requires(R r)
{
    requires std::ranges::range<R>;
    requires std::ranges::sized_range<R>;
    requires std::ranges::contiguous_range<R>;
    {
        std::ranges::range_value_t<R>::RowsAtCompileTime
    } -> std::convertible_to<int>;
    {
        std::ranges::range_value_t<R>::ColsAtCompileTime
    } -> std::convertible_to<int>;
    requires std::is_arithmetic_v<typename std::ranges::range_value_t<R>::Scalar>;
    {std::ranges::range_value_t<R>::Flags};
};

} // namespace common
} // namespace pba

#endif // PBA_COMMON_CONCEPTS_H
