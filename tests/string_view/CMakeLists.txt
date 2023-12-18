set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_NAME string_view)

add_executable(${TEST_NAME} "${DIR}/${TEST_NAME}.c")

enable_static_analyzers(${TEST_NAME} ON)

set_target_properties(${TEST_NAME} PROPERTIES C_STANDARD ${CMAKE_C_VERSION})

target_link_libraries(${TEST_NAME} PRIVATE wsl)
target_compile_options(${TEST_NAME} PRIVATE ${wsl_CompilerOptions})

add_test(NAME string_view_chop_until_last       COMMAND ${TEST_NAME} "chop_until_last")
add_test(NAME string_view_chop_until_first      COMMAND ${TEST_NAME} "chop_until_first")
add_test(NAME string_view_subview               COMMAND ${TEST_NAME} "subview")
add_test(NAME string_view_copy_values           COMMAND ${TEST_NAME} "copy_values")
add_test(NAME string_view_copy_values_non_empty COMMAND ${TEST_NAME} "copy_values_non_empty")
add_test(NAME string_view_copy_empty            COMMAND ${TEST_NAME} "copy_empty")
