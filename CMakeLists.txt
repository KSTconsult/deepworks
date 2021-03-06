cmake_minimum_required(VERSION 3.12)

########################################
# Project setup
########################################
project(deepworks)

########################################
# Set up the compiler flags
########################################
set(CMAKE_CXX_STANDARD 17)

########################################
# Define output paths
########################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

########################################
# Define basic flags
########################################
option(BUILD_TESTS      "Build deepworks with tests"         ON)
option(WITH_EIGEN       "Build deepworks with eigen backend" ON)
option(BUILD_SAMPLES    "Build samples"                      ON)
option(BUILD_BENCHMARKS "Build benchmarks"                   ON)
option(DOWNLOAD_DATA    "Download and unpack datasets"       ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(tests)

if (DOWNLOAD_DATA)
    include(cmake/download.cmake)
endif()

if (BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

if (BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
