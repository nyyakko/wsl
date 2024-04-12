set(TEST_NAME linked_list)

project(${TEST_NAME} LANGUAGES CXX)

add_executable(${TEST_NAME} "${TEST_NAME}.cpp")

enable_clang_tidy()
enable_cppcheck()

target_compile_features(${TEST_NAME} PRIVATE cxx_std_23)

target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main wsl::wsl)
target_compile_options(${TEST_NAME} PRIVATE ${wsl_TestsCompilerOptions} -Wno-c99-extensions)
target_link_options(${TEST_NAME} PRIVATE ${wsl_TestsLinkerOptions})

gtest_discover_tests(${TEST_NAME})

