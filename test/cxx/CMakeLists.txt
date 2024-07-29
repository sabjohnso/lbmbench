find_package(Catch2 REQUIRED)

macro(lbmbench_add_test test_name)
  set(exe_name ${test_name}_test)
  set(src_name ${exe_name}.cpp)
  add_executable(${exe_name} ${src_name})
  target_link_libraries(${exe_name} PRIVATE
    lbmbench::header
    lbmbench::library
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    Catch2::Catch2WithMain)
  target_compile_features(${exe_name} PRIVATE ${lbmbench_CXX_FEATURES})
  add_test(${test_name} ${exe_name})
endmacro()

lbmbench_add_test(array)
lbmbench_add_test(boundary_condition)
lbmbench_add_test(boundary_id)
lbmbench_add_test(bounding_box)
lbmbench_add_test(D2Q9_node)
lbmbench_add_test(D2Q9_state)
lbmbench_add_test(D2Q9_velocity_distribution)
lbmbench_add_test(euclidean)
lbmbench_add_test(expression)
lbmbench_add_test(fixed_array_index)
lbmbench_add_test(fixed_array_order)
lbmbench_add_test(fixed_array)
lbmbench_add_test(index)
lbmbench_add_test(initial_conditions)
lbmbench_add_test(input)
lbmbench_add_test(lattice)
lbmbench_add_test(lexical)
lbmbench_add_test(obstacles)
lbmbench_add_test(runtime_config)
lbmbench_add_test(shape)
lbmbench_add_test(vector)
