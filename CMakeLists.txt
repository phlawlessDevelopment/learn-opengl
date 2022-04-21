cmake_minimum_required(VERSION 3.15)

project(Engine)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
# find_package(GLUT REQUIRED)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${GLEW_INCLUDE_DIRS}
        # ${GLUT_INCLUDE_DIRS}
)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(engine 
main.cpp
${all_SRCS}
)

target_link_libraries(engine
glfw 
OpenGL::GL
${CMAKE_DL_LIBS}
${GLEW_LIBRARIES}
# ${GLUT_LIBRARY}
)