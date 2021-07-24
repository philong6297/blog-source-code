// Copyright 2021 Long Le Phi. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#include "2021-07-18-faster-sorted-array-by-reducing-branches/solution.hpp"

#include <iterator>
#include <sstream>
#include <vector>

#include "doctest/doctest.h"

namespace {
  auto OperateTest(const std::vector<int32_t>& input_1,
                   const std::vector<int32_t>& input_2) -> void {
    std::vector<int32_t> output_standard{};
    std::vector<int32_t> output_branchless{};

    longlp::Union2By2::StandardVersion(input_1.begin(),
                                       input_1.end(),
                                       input_2.begin(),
                                       input_2.end(),
                                       std::back_inserter(output_standard));

    longlp::Union2By2::StandardVersion(input_1.begin(),
                                       input_1.end(),
                                       input_2.begin(),
                                       input_2.end(),
                                       std::back_inserter(output_branchless));

    CAPTURE(input_1);
    CAPTURE(input_2);
    CAPTURE(output_standard);
    CAPTURE(output_branchless);
    REQUIRE_EQ(output_branchless.size(), output_standard.size());
    REQUIRE_EQ(std::equal(output_standard.begin(),
                          output_standard.end(),
                          output_branchless.begin(),
                          output_branchless.end()),
               true);
  }
}   // namespace

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
    "Input1: duplicate values/"
    "Input2: duplicate values/"
    "ValueRange: same") {
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

    SUBCASE("union of Input1 and Input2") { OperateTest(input_1, input_2); }
    SUBCASE("union of Input2 and Input1") { OperateTest(input_1, input_2); }
  }

  TEST_CASE(
    "Input1: duplicate values/"
    "Input2: duplicate values/"
    "ValueRange: different") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};
    const std::vector<int32_t> input_2 = {
      100, 100, 102, 102, 104, 106, 107, 107, 108, 109, 109, 110, 114, 114, 114,
      115, 115, 116, 116, 117, 118, 118, 119, 119, 120, 120, 120, 121, 122, 123,
      124, 125, 126, 126, 128, 128, 128, 131, 131, 132, 133, 135, 140, 140, 143,
      143, 143, 143, 144, 146, 147, 147, 147, 150, 151, 151, 151, 152, 154, 154,
      158, 159, 159, 159, 160, 160, 160, 161, 161, 162, 162, 164, 165, 165, 165,
      166, 166, 167, 170, 171, 173, 175, 177, 177, 177, 178, 179, 179, 179, 182,
      182, 183, 188, 189, 190, 192, 195, 197, 199, 200};

    SUBCASE("union of Input1 and Input2") { OperateTest(input_1, input_2); }
    SUBCASE("union of Input2 and Input1") { OperateTest(input_1, input_2); }
  }

  TEST_CASE(
    "Input1: duplicate values/"
    "Input2: unique values/"
    "ValueRange: same") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};
    const std::vector<int32_t> input_2 = {
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
      17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
      34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
      51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
      68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
      85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

    SUBCASE("union of Input1 and Input2") { OperateTest(input_1, input_2); }
    SUBCASE("union of Input2 and Input1") { OperateTest(input_1, input_2); }
  }

  TEST_CASE(
    "Input1: duplicate values/"
    "Input2: unique values/"
    "ValueRange: different") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};
    const std::vector<int32_t> input_2 = {
      100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
      115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
      130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
      145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
      160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174,
      175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
      190, 191, 192, 193, 194, 195, 196, 197, 198, 199};

    SUBCASE("union of Input1 and Input2") { OperateTest(input_1, input_2); }
    SUBCASE("union of Input2 and Input1") { OperateTest(input_1, input_2); }
  }

  TEST_CASE(
    "Input1: unique values/"
    "Input2: unique values/"
    "ValueRange: same") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};

    OperateTest(input_1, input_1);
  }

  TEST_CASE(
    "Input1: unique values/"
    "Input2: unique values/"
    "ValueRange: same") {
    const std::vector<int32_t> input_1 = {
      0,  1,  1,  3,  4,  5,  6,  6,  7,  8,  9,  9,  11, 12, 12, 12, 13,
      14, 14, 14, 15, 16, 16, 17, 17, 18, 22, 24, 24, 25, 27, 27, 28, 33,
      34, 37, 37, 37, 39, 40, 41, 43, 44, 47, 47, 47, 48, 48, 50, 52, 53,
      53, 54, 55, 57, 58, 61, 62, 64, 65, 68, 68, 68, 69, 71, 71, 71, 71,
      73, 75, 76, 76, 77, 77, 78, 78, 79, 79, 79, 81, 81, 81, 83, 84, 84,
      84, 84, 85, 85, 86, 86, 88, 88, 88, 89, 91, 92, 94, 95, 99};

    const std::vector<int32_t> input_2 = {
      100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
      115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
      130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
      145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
      160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174,
      175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
      190, 191, 192, 193, 194, 195, 196, 197, 198, 199};

    SUBCASE("union of Input1 and Input2") { OperateTest(input_1, input_2); }
    SUBCASE("union of Input2 and Input1") { OperateTest(input_1, input_2); }
  }
}
