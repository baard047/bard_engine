set( TARGET_NAME bard-engine )

cmake_minimum_required( VERSION 3.17 )
set( CMAKE_CXX_STANDARD 17 )

file( GLOB_RECURSE HEADER_FILES "*.h" "*.hpp" )
file( GLOB_RECURSE SOURCE_FILES "*.cpp" )

add_library( ${TARGET_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} )
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
