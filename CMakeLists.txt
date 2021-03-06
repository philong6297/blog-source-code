cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----
project(
  blog-source-code
  VERSION 1.0
  LANGUAGES CXX
)

# ---- Main Project check ----
# determine if this project is built as a subproject (using add_subdirectory) or
# if it is the main project
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MAIN_PROJECT ON)
endif()

set(LONGLP_PROJECT_DIR "${PROJECT_SOURCE_DIR}")
set(LONGLP_PROJECT_SRC_DIR "${LONGLP_PROJECT_DIR}/src")
set(LONGLP_PROJECT_OUTPUT_DIR "${PROJECT_BINARY_DIR}")
set(LONGLP_PROJECT_TEST_DIR "${LONGLP_PROJECT_DIR}/test")

# ---- Related tools ----
add_subdirectory(cmake)
longlp_desired_compile_features(LONGLP_DESIRED_COMPILE_FEATURES)
longlp_desired_compile_options(LONGLP_DESIRED_COMPILE_OPTIONS)

# ---- Third parties ----
find_package(fmt REQUIRED)
find_package(benchmark REQUIRED)
find_package(doctest REQUIRED)
find_package(effolkronium_random REQUIRED)

add_subdirectory(${LONGLP_PROJECT_SRC_DIR})

# ---- Test ----
include(CTest)
enable_testing()
add_subdirectory(${LONGLP_PROJECT_TEST_DIR})
