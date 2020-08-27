CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(deneme1)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(/home/tuttyfrutyee/glfw /home/tuttyfrutyee/glfw/src)

FIND_PACKAGE(OpenGL REQUIRED)

SET(SOURCE_FILES deneme1.cpp
 src/Renderer.cpp src/Renderer.h
 src/IndexBuffer.cpp src/IndexBuffer.h
 src/VertexBuffer.cpp src/VertexBuffer.h
 src/VertexArray.cpp src/VertexArray.h
 src/VertexBufferLayout.h src/VertexBufferLayout.cpp
 )

include_directories("${PROJECT_SOURCE_DIR}/src")

ADD_EXECUTABLE(deneme1 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(deneme1 glfw)
TARGET_LINK_LIBRARIES(deneme1 OpenGL::GL)
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

#glad

set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")