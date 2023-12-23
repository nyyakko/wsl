cmake_minimum_required(VERSION 3.5)

project(wsl LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake")

set(CMAKE_C_VERSION 23)

set(wsl_CompilerOptions ${wsl_CompilerOptions}
    -Werror
    -Wall
    -Wextra
    -Wshadow
    -Wcast-align
    -Wunused
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
)

include(static_analyzers)
include(GNUInstallDirs)

add_subdirectory(wsl)

if (NOT WSL_DISABLE_TESTS)
    message("\n-- Project will be building the test suit.")

    if (NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        message("-- Running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are enabled.")
        set(wsl_TestsLinkerOptions ${wsl_TestsLinkerOptions} -fsanitize=undefined,leak,address)
    else()
        message("-- Running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are disabled.")
    endif()

    set(wsl_TestsCompilerOptions ${wsl_TestsCompilerOptions} ${wsl_CompilerOptions})

    include(GoogleTest)
    find_package(GTest CONFIG REQUIRED)

    enable_testing()
    add_subdirectory(tests)
else()
    message("\n-- Project will not be building the test suit.")
endif()


