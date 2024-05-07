#include "pba/common/Indexing.h"

#include <Eigen/Core>
#include <array>
#include <doctest/doctest.h>
#include <iostream>
#include <ranges>

namespace pba {
namespace common {

TEST_CASE("Cumulative sums are computable from any integral range type")
{
    std::array<Index, 3> v{5, 10, 15};
    auto const cs = cumsum(v);
    CHECK_EQ(cs, std::vector<Index>{0, 5, 15, 30});
}

} // namespace common
} // namespace pba