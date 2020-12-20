set(TARGET_NAME sandbox )

cmake_minimum_required( VERSION 3.17 )
set( CMAKE_CXX_STANDARD 17 )

add_executable( ${TARGET_NAME} main.cpp )
target_link_libraries( ${TARGET_NAME} PUBLIC bard-engine )
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
