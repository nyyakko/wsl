cmake_minimum_required(VERSION 3.5)
project(wsl LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_C_VERSION 23)
set(EXPORT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake")

set(wsl_REQUIRES_VCPKG FALSE)

if (NOT ${CMAKE_TOOLCHAIN_FILE} STREQUAL "")
    message(STATUS "vcpkg toolchain found.")
else()
    if (wsl_REQUIRES_VCPKG)
        message(FATAL_ERROR "vcpkg toolchain was not found.")
    else()
        message(STATUS "vcpkg toolchain not found. continuing without it.")
    endif()
endif()

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

if (NOT wsl_DISABLE_TESTS)
    message(STATUS "Project will be building the test suit.")

    if (NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        message(STATUS "Running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are enabled.")
        set(wsl_TestsLinkerOptions ${wsl_TestsLinkerOptions} -fsanitize=undefined,leak,address)
    else()
        message(STATUS "Running on ${CMAKE_HOST_SYSTEM_NAME}, sanitizers for tests are disabled.")
    endif()

    set(wsl_TestsCompilerOptions ${wsl_TestsCompilerOptions} ${wsl_CompilerOptions})

    include(GoogleTest)
    find_package(GTest CONFIG REQUIRED)

    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Project will not be building the test suit.")
endif()


