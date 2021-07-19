// Copyright 2021 Long Le Phi. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#include "2021-07-18-faster-sorted-array-by-reducing-branches/solution.hpp"

#include <iterator>
#include <sstream>
#include <vector>

#include "doctest/doctest.h"

namespace {}   // namespace

namespace doctest {
  template <typename T>
  struct StringMaker<std::vector<T>> {
    static auto convert(const std::vector<T>& in) -> String {
      std::ostringstream oss;

      oss << "[";
      std::copy(in.cbegin(), in.cend(), std::ostream_iterator<T>(oss, " "));
      oss << "]";

      return oss.str().c_str();
    }
  };
}   // namespace doctest

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
TEST_SUITE("2021-07-18-faster-sorted-array-by-reducing-branches") {
  TEST_CASE(
    "Input 1 duplicate, Input2 duplicate, Input1 same range with Input2") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};
    const std::vector<int32_t> input_2 = {
      0,  0,  0,  0,  0,  3,  3,  5,  6,  7,  8,  8,  9,  11, 11, 12, 14,
      15, 15, 16, 16, 17, 19, 20, 20, 21, 22, 23, 23, 23, 25, 25, 27, 29,
      30, 30, 32, 33, 34, 34, 36, 40, 42, 42, 43, 43, 43, 44, 45, 45, 46,
      46, 47, 49, 49, 49, 51, 52, 52, 53, 54, 56, 57, 58, 59, 60, 61, 64,
      64, 64, 64, 65, 66, 66, 68, 69, 70, 71, 72, 75, 75, 76, 78, 82, 84,
      84, 86, 86, 87, 87, 89, 89, 91, 92, 93, 93, 95, 98, 99, 99};
    constexpr auto expected_union_size = 154;

    CAPTURE(input_1);
    CAPTURE(input_2);
    CAPTURE(expected_union_size);

    std::vector<int32_t> output_standard{};
    std::vector<int32_t> output_branchless{};

    longlp::Union2By2::StandardVersion(input_1.begin(),
                                       input_1.end(),
                                       input_2.begin(),
                                       input_2.end(),
                                       std::back_inserter(output_standard));

    REQUIRE_EQ(output_standard.size(), expected_union_size);

    longlp::Union2By2::StandardVersion(input_1.begin(),
                                       input_1.end(),
                                       input_2.begin(),
                                       input_2.end(),
                                       std::back_inserter(output_branchless));

    REQUIRE_EQ(output_branchless.size(), expected_union_size);

    CAPTURE(output_standard);
    CAPTURE(output_branchless);
    REQUIRE_EQ(output_branchless.size(), output_standard.size());
    REQUIRE_EQ(std::equal(output_standard.begin(),
                          output_standard.end(),
                          output_branchless.begin(),
                          output_branchless.end()),
               true);
  }
}
