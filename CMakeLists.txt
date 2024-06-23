cmake_minimum_required(VERSION 3.12)

project(lbmbench VERSION 0.1.0 LANGUAGES C CXX)

option(lbmbench_BUILD_TESTING "Build the lbmbench tests" ON)
set(lbmbench_CXX_STANDARD 20 CACHE STRING "C++ standard for lbmbench")

include(GNUInstallDirs)
set(lbmbench_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(lbmbench_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(lbmbench_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(lbmbench_INSTALL_CONFDIR ${lbmbench_INSTALL_LIBDIR}/cmake/lbmbench-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(lbmbench_deps)

add_subdirectory(lbmbench)

if(lbmbench_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(lbmbench_testing)
  endif()
endif()

install(EXPORT lbmbench_EXPORTS
  NAMESPACE lbmbench::
  FILE lbmbench-exports.cmake
  DESTINATION ${lbmbench_INSTALL_CONFDIR})

configure_file(lbmbench-config.cmake.in lbmbench-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/lbmbench-config.cmake
  DESTINATION ${lbmbench_INSTALL_CONFDIR})
