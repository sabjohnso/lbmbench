configure_file(config.hpp.in config.hpp)

add_library(lbmbench_header INTERFACE)
set_target_properties(lbmbench_header PROPERTIES EXPORT_NAME header)
target_include_directories(lbmbench_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${lbmbench_INSTALL_INCLUDEDIR}>)

add_library(lbmbench::header ALIAS lbmbench_header)
  
install(TARGETS lbmbench_header
  EXPORT lbmbench_EXPORTS
  RUNTIME DESTINATION ${lbmbench_INSTALL_BINDIR}
  LIBRARY DESTINATION ${lbmbench_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${lbmbench_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${lbmbench_INSTALL_INCLUDEDIR}/lbmbench)
