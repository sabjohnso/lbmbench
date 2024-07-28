cmake_minimum_required(VERSION 3.12)

option(lbmbench_BUILD_TESTING "Build the lbmbench tests" ON)
option(lbmbench_USE_MPI "Build LBM benchmarks with MPI support" OFF)
option(lbmbench_USE_THREADS "Build LBM benchmarks with multithreading support" OFF)
option(lbmbench_USE_OPENMP "Build LBM benchmarks with OpenMP support" OFF)
option(lbmbench_USE_CUDA "Build LBM benchmarks with CUDA support" OFF)

option(lbmbench_USE_FLOAT64 "Build LBM benchmarks with 64bit floating-point support" ON)
option(lbmbench_USE_FLOAT32 "Build LBM benchmarks with 32bit floating-point support" ON)
option(lbmbench_USE_FLOAT16 "Build LBM benchmarks with 16bit floating-point support" ON)
option(lbmbench_USE_BFLOAT16 "Build LBM benchmarks with bfloat16 support" ON)

option(lbmbench_USE_FIXED64 "Build LBM benchmarks with 64bit fixed-point support" ON)
option(lbmbench_USE_FIXED32 "Build LBM benchmarks with 32bit fixed-point support" ON)
option(lbmbench_USE_FIXED16 "Build LBM benchmarks with 16bit fixed-point support" ON)

if(lbmbench_USE_CUDA)
  project(lbmbench VERSION 0.1.0 LANGUAGES C CXX CUDA)
else()
  project(lbmbench VERSION 0.1.0 LANGUAGES C CXX)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(lbmbench_CXX_FEATURES cxx_std_23)

include(GNUInstallDirs)
set(lbmbench_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(lbmbench_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(lbmbench_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(lbmbench_INSTALL_CONFDIR ${lbmbench_INSTALL_LIBDIR}/cmake/lbmbench-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(lbmbench_deps)

add_subdirectory(cxx)

if(lbmbench_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(test)
  endif()
endif()

install(EXPORT lbmbench_EXPORTS
  NAMESPACE lbmbench::
  FILE lbmbench-exports.cmake
  DESTINATION ${lbmbench_INSTALL_CONFDIR})

configure_file(lbmbench-config.cmake.in lbmbench-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/lbmbench-config.cmake
  DESTINATION ${lbmbench_INSTALL_CONFDIR})

message(STATUS "***************************")
message(STATUS "options summary")
message(STATUS "***************************")
message(STATUS "lbmbench_CXX_FEATURES: ${lbmbench_CXX_FEATURES}")

message(STATUS "lbmbench_BUILD_TESTING: ${lbmbench_BUILD_TESTING}")
message(STATUS "lbmbench_USE_MPI: ${lbmbench_USE_MPI}")
message(STATUS "lbmbench_USE_THREADS: ${lbmbench_USE_THREADS}")
message(STATUS "lbmbench_USE_OPENMP: ${lbmbench_USE_OPENMP}")
message(STATUS "lbmbench_USE_CUDA: ${lbmbench_USE_CUDA}")

message(STATUS "lbmbench_USE_FLOAT64: ${lbmbench_USE_FLOAT64}")
message(STATUS "lbmbench_USE_FLOAT32: ${lbmbench_USE_FLOAT32}")
message(STATUS "lbmbench_USE_FLOAT16: ${lbmbench_USE_FLOAT16}")
message(STATUS "lbmbench_USE_BFLOAT16: ${lbmbench_USE_BFLOAT16}")

message(STATUS "lbmbench_USE_FIXED64: ${lbmbench_USE_FIXED64}")
message(STATUS "lbmbench_USE_FIXED32: ${lbmbench_USE_FIXED32}")
message(STATUS "lbmbench_USE_FIXED16: ${lbmbench_USE_FIXED16}")
message(STATUS "***************************")
message("")
