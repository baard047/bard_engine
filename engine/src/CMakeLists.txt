set( TARGET_NAME bard-engine )

cmake_minimum_required( VERSION 3.17 )
set( CMAKE_CXX_STANDARD 17 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

file( GLOB_RECURSE HEADER_FILES "*.h" "*.hpp" )
file( GLOB_RECURSE SOURCE_FILES "*.cpp" )

add_library( ${TARGET_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${STB_IMAGE_FILES} )
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${STB_DIR} )
target_link_libraries( ${TARGET_NAME}
                       spdlog_header_only
                       glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}
                       glad
                       imgui
                       glm
                       )

if( ${CMAKE_BUILD_TYPE} MATCHES "Debug" )
	target_compile_definitions(${TARGET_NAME} PUBLIC BARD_ENABLE_ASSERTS)
	target_compile_definitions(${TARGET_NAME} PUBLIC BARD_SHOW_SOURCE_IN_LOG)
endif()
target_compile_definitions(${TARGET_NAME} PRIVATE GLFW_INCLUDE_NONE)
