add_executable(state_tests state_tests.cc)
target_link_libraries(state_tests gtest gmock)

add_executable(flow_tests flow_tests.cc)
target_link_libraries(flow_tests gtest gmock)

add_executable(pdmp_tests pdmp_tests.cc)
target_link_libraries(pdmp_tests gtest gmock)

add_executable(dependencies_graph_tests dependencies_graph_tests.cc)
target_link_libraries(dependencies_graph_tests gtest gmock)

add_executable(nodes_tests nodes_tests.cc)
target_link_libraries(nodes_tests gtest gmock)

add_executable(poisson_process_policy_tests poisson_process_policy_tests.cc)
target_link_libraries(poisson_process_policy_tests gtest gmock)

add_executable(pdmp_integration_tests pdmp_integration_tests.cc)
target_link_libraries(pdmp_integration_tests gtest gmock)

add_test(NAME state_tests COMMAND state_tests)
add_test(NAME flow_tests COMMAND flow_tests)
add_test(NAME pdmp_tests COMMAND pdmp_tests)
add_test(NAME dependencies_graph_tests COMMAND dependencies_graph_tests)
add_test(NAME nodes_tests COMMAND nodes_tests)
add_test(NAME poisson_process_policy_tests COMMAND poisson_process_policy_tests)
add_test(NAME pdmp_integration_tests COMMAND pdmp_integration_tests)
