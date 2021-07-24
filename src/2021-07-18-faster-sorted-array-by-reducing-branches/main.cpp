// Copyright 2021 Long Le Phi. All rights reserved.
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <vector>

#include "2021-07-18-faster-sorted-array-by-reducing-branches/solution.hpp"
#include "benchmark/benchmark.h"
#include "effolkronium/random.hpp"

namespace {
  using longlp::Union2By2;
  using Random = effolkronium::random_thread_local;
}   // namespace

auto main(int32_t argc, char** argv) -> int32_t {
  constexpr auto size_input_1{1000};
  constexpr auto size_input_2{1000};
  constexpr int64_t min_value_input_1{10};
  constexpr int64_t max_value_input_1{100};
  constexpr int64_t min_value_input_2{10};
  constexpr int64_t max_value_input_2{100};

  std::vector<int64_t> input_1{};
  std::vector<int64_t> input_2{};

  std::generate_n(std::back_inserter(input_1), size_input_1, [] {
    return Random::get(min_value_input_1, max_value_input_1);
  });
  std::generate_n(std::back_inserter(input_2), size_input_2, [] {
    return Random::get(min_value_input_2, max_value_input_2);
  });

  std::sort(input_1.begin(), input_1.end());
  std::sort(input_2.begin(), input_2.end());

  benchmark::RegisterBenchmark(
    "BM_Branchless",
    [&input_1, &input_2](benchmark::State& state) {
      std::vector<int64_t> output{};
      for ([[maybe_unused]] auto _ : state) {
        benchmark::DoNotOptimize(
          Union2By2::BranchlessVersion(input_1.begin(),
                                       input_1.end(),
                                       input_2.begin(),
                                       input_2.end(),
                                       std::back_inserter(output)));
      }
    })
    ->DisplayAggregatesOnly(true)
    ->Repetitions(100);

  benchmark::RegisterBenchmark(
    "BM_Standard",
    [&input_1, &input_2](benchmark::State& state) {
      std::vector<int64_t> output{};
      for ([[maybe_unused]] auto _ : state) {
        benchmark::DoNotOptimize(
          Union2By2::StandardVersion(input_1.begin(),
                                     input_1.end(),
                                     input_2.begin(),
                                     input_2.end(),
                                     std::back_inserter(output)));
      }
    })
    ->DisplayAggregatesOnly(true)
    ->Repetitions(100);

  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return 1;
  }

  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
