cmake_minimum_required(VERSION 3.25)

project(wsl LANGUAGES C CXX)

set(EXPORT_DIR "${CMAKE_SOURCE_DIR}/build/cmake")

include(cmake/static_analyzers.cmake)
include(cmake/CPM.cmake)
include(cmake/remote_clone.cmake)
include(cmake/enable_tests.cmake)
include(GNUInstallDirs)

option(ENABLE_CLANGTIDY "" TRUE)
option(ENABLE_CPPCHECK "" TRUE)
option(ENABLE_TESTING "" TRUE)

if (ENABLE_TESTING)
    enable_tests()
endif()

# set(wsl_CompilerOptions ${wsl_CompilerOptions})
# set(wsl_LinkerOptions ${wsl_LinkerOptions})

# CPMAddPackage("gh:repo/package1#REF")
# CPMAddPackage("gh:repo/package2#REF")
# ...
#
# set(wsl_ExternalLibraries package1 package2 ...)

add_subdirectory(wsl)

