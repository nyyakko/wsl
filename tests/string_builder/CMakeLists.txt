set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_NAME string_builder)

add_executable(${TEST_NAME} "${DIR}/${TEST_NAME}.c")

enable_static_analyzers(${TEST_NAME} ON)

set_target_properties(${TEST_NAME} PROPERTIES C_STANDARD ${CMAKE_C_VERSION})

target_link_libraries(${TEST_NAME} PRIVATE wsl)
target_compile_options(${TEST_NAME} PRIVATE ${wsl_CompilerOptions})

add_test(NAME string_builder_chop_until_last      COMMAND ${TEST_NAME} "chop_until_last")
add_test(NAME string_builder_chop_until_first     COMMAND ${TEST_NAME} "chop_until_first")
add_test(NAME string_builder_substring            COMMAND ${TEST_NAME} "substring")
add_test(NAME string_builder_copy_values          COMMAND ${TEST_NAME} "copy_values")
add_test(NAME string_builder_copy_values_nonempty COMMAND ${TEST_NAME} "copy_values_non_empty")
add_test(NAME string_builder_copy_empty           COMMAND ${TEST_NAME} "copy_empty")
add_test(NAME string_builder_append               COMMAND ${TEST_NAME} "append")
add_test(NAME string_builder_append_string        COMMAND ${TEST_NAME} "append_string")
