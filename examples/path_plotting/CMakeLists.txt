cmake_minimum_required(VERSION 3.1)

add_executable(bps_path bps_path.cc ${QCustomPlot_SOURCE_FILES}
                                    ${PlottingUtils_SOURCE_FILES})
target_link_libraries(bps_path ${BPS_LINK_LIBRARIES})

add_executable(zig_zag_path zig_zag_path.cc ${QCustomPlot_SOURCE_FILES}
                                    ${PlottingUtils_SOURCE_FILES})
target_link_libraries(zig_zag_path ${BPS_LINK_LIBRARIES})
