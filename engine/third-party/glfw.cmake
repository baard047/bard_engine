set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Do not build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Do not build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Do not build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Do not generate installation target")

add_subdirectory( glfw )