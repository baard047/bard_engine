cmake_minimum_required(VERSION 3.10)
set( TARGET_NAME glad )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library( ${TARGET_NAME} SHARED
               include/glad/glad.h
               include/KHR/khrplatform.h
               src/glad.c )
target_include_directories(${TARGET_NAME} PUBLIC include/ )