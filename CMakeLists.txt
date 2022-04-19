cmake_minimum_required(VERSION 3.15)

project(Engine)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
# add_subdirectory(src)
find_package(glfw3 3.3 REQUIRED)

add_executable(engine 
main.cpp
glad.c
${all_SRCS}
)

target_link_libraries(engine glfw ${CMAKE_DL_LIBS})