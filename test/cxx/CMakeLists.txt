find_package(Catch2 REQUIRED)

macro(lbmbench_add_test test_name)
  set(exe_name ${test_name}_test)
  set(src_name ${exe_name}.cpp)
  add_executable(${exe_name} ${src_name})
  target_link_libraries(${exe_name} PRIVATE
    lbmbench::header
    Catch2::Catch2WithMain)
  target_compile_features(${exe_name} PRIVATE ${lbmbench_CXX_FEATURES})
  add_test(${test_name} ${exe_name})
endmacro()

lbmbench_add_test(fixed_array_index)
lbmbench_add_test(fixed_array_order)
lbmbench_add_test(fixed_array)
lbmbench_add_test(D2Q9)
