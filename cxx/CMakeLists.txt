add_subdirectory(lbm)

add_library(lbmbench_header INTERFACE)
set_target_properties(lbmbench_header PROPERTIES EXPORT_NAME header)
target_include_directories(lbmbench_header INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${lbmbench_INTSTALL_INCLUDEDIR}>
)
add_library(lbmbench::header ALIAS lbmbench_header)


add_library(lbmbench_library
  lbm/core/Bounding_Box.cpp
  lbm/core/Lattice.cpp
  lbm/core/Expression.cpp
  lbm/core/Euclidean.cpp
  lbm/core/Float_Type.cpp
  lbm/core/Kernel.cpp
  lbm/core/Input.cpp
  lbm/app/Runtime_Config.cpp
  lbm/app/Runtime_Config_Impl.cpp
  lbm/app/Driver.cpp
  lbm/app/Driver_Impl.cpp)

target_link_libraries(lbmbench_library
  PRIVATE Boost::program_options
  lbmbench::header
  nlohmann_json::nlohmann_json
  nlohmann_json_schema_validator)
target_compile_features(lbmbench_library PUBLIC ${lbmbench_CXX_FEATURES})
set_target_properties(lbmbench_header PROPERTIES EXPORT_NAME library)
add_library(lbmbench::library ALIAS lbmbench_library)

add_executable(lbmbench main.cpp)
target_link_libraries(lbmbench PRIVATE lbmbench::header lbmbench::library Boost::program_options
nlohmann_json_schema_validator)

install(TARGETS lbmbench nlohmann_json
  EXPORT lbmbench_EXPORTS
  RUNTIME DESTINATION ${lbmbench_INSTALL_BINDIR}
  LIBRARY DESTINATION ${lbmbench_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${lbmbench_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/lbmbench/config.hpp
  DESTINATION ${lbmbench_INSTALL_INCLUDEDIR}/lbmbench)

install(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/lbmbench
  DESTINATION ${list_processing_INSTALL_INCLUDEDIR}/list_processing
  FILES_MATCHING PATTERN "*.hpp")
