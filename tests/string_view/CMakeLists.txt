set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_NAME string_view)

project(${TEST_NAME} LANGUAGES CXX)

add_executable(${TEST_NAME} "${DIR}/${TEST_NAME}.cpp")

enable_static_analyzers(${TEST_NAME} ON)

set_target_properties(${TEST_NAME} PROPERTIES CXX_STANDARD ${CMAKE_CXX_VERSION})

target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main wsl)
target_compile_options(${TEST_NAME} PRIVATE ${wsl_CompilerOptions} -Wno-c99-extensions)

gtest_discover_tests(${TEST_NAME})

