cmake_minimum_required( VERSION 3.17 )
project( bard-engine )

set( CMAKE_CXX_STANDARD 17 )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE STRING "runtime output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE STRING "library output directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING "release runtime output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING "release library output directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE STRING "debug runtime output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE STRING "debug library output directory")

add_subdirectory( engine )
add_subdirectory( sandbox )