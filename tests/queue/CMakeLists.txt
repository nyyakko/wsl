set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_NAME queue)

add_executable(${TEST_NAME} "${DIR}/${TEST_NAME}.c")

enable_static_analyzers(${TEST_NAME} ON)

set_target_properties(${TEST_NAME} PROPERTIES C_STANDARD ${CMAKE_C_VERSION})

target_link_libraries(${TEST_NAME} PRIVATE wsl)
target_compile_options(${TEST_NAME} PRIVATE ${wsl_CompilerOptions})

add_test(NAME queue_initialized_with_values COMMAND ${TEST_NAME} "initialized_with_values")
add_test(NAME queue_push_values             COMMAND ${TEST_NAME} "push_values")
add_test(NAME queue_pop_values              COMMAND ${TEST_NAME} "pop_values")
add_test(NAME queue_copy_values             COMMAND ${TEST_NAME} "copy_values")
add_test(NAME queue_copy_values_non_empty   COMMAND ${TEST_NAME} "copy_values_non_empty")
add_test(NAME queue_copy_empty              COMMAND ${TEST_NAME} "copy_empty")
