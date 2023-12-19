cmake_minimum_required(VERSION 3.5)

project(wsl)

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
include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

# set(wsl_ExternalLibraries )

enable_testing()

add_subdirectory(wsl)
add_subdirectory(tests)

