project(project_test)

add_executable(project_test)
target_compile_options(project_test PRIVATE ${LONGLP_DESIRED_COMPILE_OPTIONS})
target_compile_features(project_test PRIVATE ${LONGLP_DESIRED_COMPILE_FEATURES})
target_include_directories(project_test PRIVATE ${LONGLP_PROJECT_SRC_DIR})
target_link_libraries(
  project_test
  PRIVATE doctest::doctest
          # target for each solution
          2021-07-18-source
)
target_compile_definitions(
  project_test PUBLIC DOCTEST_CONFIG_SUPER_FAST_ASSERTS
                      DOCTEST_CONFIG_NO_COMPARISON_WARNING_SUPPRESSION
)
target_sources(
  project_test
  PRIVATE
    doctest_main.cpp
    # unittest for each solution
    ${LONGLP_PROJECT_SRC_DIR}/2021-07-18-faster-sorted-array-by-reducing-branches/solution_unittest.cpp
)

# ---- Discover tests ----
# doctest_DIR is populated by vcpkg
include(${doctest_DIR}/doctest.cmake)
doctest_discover_tests(project_test)
