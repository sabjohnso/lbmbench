add_executable(image_data_geometry_filter image_data_geometry_filter.cpp)
target_link_libraries(image_data_geometry_filter PRIVATE ${VTK_LIBRARIES})

add_executable(dem_reader dem_reader.cpp)
target_link_libraries(dem_reader PRIVATE ${VTK_LIBRARIES})

add_executable(image_map_to_colors image_map_to_colors.cpp)
target_link_libraries(image_map_to_colors PRIVATE ${VTK_LIBRARIES})

add_executable(image_mask image_mask.cpp)
target_link_libraries(image_mask PRIVATE ${VTK_LIBRARIES})
