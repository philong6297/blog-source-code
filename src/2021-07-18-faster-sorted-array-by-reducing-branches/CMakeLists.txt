# Object target
add_library(2021-07-18-source OBJECT solution.hpp solution.cpp)
target_compile_options(
  2021-07-18-source PRIVATE ${LONGLP_DESIRED_COMPILE_OPTIONS}
)
target_compile_features(
  2021-07-18-source PRIVATE ${LONGLP_DESIRED_COMPILE_FEATURES}
)
target_include_directories(2021-07-18-source PRIVATE ${LONGLP_PROJECT_SRC_DIR})

# Main target with benchmark
add_executable(2021-07-18-benchmark)
target_sources(2021-07-18-benchmark PRIVATE main.cpp)
target_compile_options(
  2021-07-18-benchmark PRIVATE ${LONGLP_DESIRED_COMPILE_OPTIONS}
)
target_compile_features(
  2021-07-18-benchmark PRIVATE ${LONGLP_DESIRED_COMPILE_FEATURES}
)
target_include_directories(
  2021-07-18-benchmark PRIVATE ${LONGLP_PROJECT_SRC_DIR}
)
target_link_libraries(
  2021-07-18-benchmark PRIVATE benchmark::benchmark effolkronium_random
                               2021-07-18-source
)
