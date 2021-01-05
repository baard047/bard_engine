cmake_minimum_required(VERSION 3.10)
set( TARGET_NAME glad )

add_library( ${TARGET_NAME} STATIC
               include/glad/glad.h
               include/KHR/khrplatform.h
               src/glad.c )
target_include_directories(${TARGET_NAME} PUBLIC include/ )