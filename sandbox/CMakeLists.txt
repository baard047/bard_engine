set(TARGET_NAME sandbox )

cmake_minimum_required( VERSION 3.17 )
set( CMAKE_CXX_STANDARD 17 )

file( GLOB_RECURSE HEADER_FILES "*.h" "*.hpp" )
file( GLOB_RECURSE SOURCE_FILES "*.cpp" )

add_executable( ${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES} )
target_link_libraries( ${TARGET_NAME} PRIVATE bard-engine )
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#TODO proper macro copy files
file( COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
