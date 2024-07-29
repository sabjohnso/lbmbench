if(NOT EXISTS ${PROJECT_SOURCE_DIR}/cmake_utilities/FindCMakeUtilities.cmake)
  find_package(Git REQUIRED)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_utilities)

find_package(CMakeUtilities REQUIRED)

find_package(nlohmann_json REQUIRED)

find_package(nlohmann_json_schema_validator REQUIRED)

find_package(Boost REQUIRED COMPONENTS program_options)

if(lbm_USE_MPI)
  find_package(MPI REQUIRED)
endif()

if(lbm_USE_THREADS)
  find_package(Threads REQUIRED)
endif()

if(lbm_USE_OPENMP)
  find_package(OpenMP REQUIRED)
endif()
