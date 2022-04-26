cmake_minimum_required(VERSION 3.15)

project(Engine)

set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)


include_directories(
        ${PROJECT_SOURCE_DIR}/src/vendor/stb
        ${PROJECT_SOURCE_DIR}/src/core
        ${PROJECT_SOURCE_DIR}/src/renderer
        ${PROJECT_SOURCE_DIR}/src/gui
        ${PROJECT_SOURCE_DIR}/src
        ${GLEW_INCLUDE_DIRS}
        )
        
add_subdirectory(
        ${PROJECT_SOURCE_DIR}/src/vendor/glm
        ${PROJECT_SOURCE_DIR}/src/vendor/imgui
)
file(GLOB all_SRCS
"${PROJECT_SOURCE_DIR}/src/*.cpp"
"${PROJECT_SOURCE_DIR}/src/renderer/*.cpp"
"${PROJECT_SOURCE_DIR}/src/gui/*.cpp"
"${PROJECT_SOURCE_DIR}/src/core/*.cpp"
"${PROJECT_SOURCE_DIR}/src/vendor/stb/*.cpp"
"${PROJECT_SOURCE_DIR}/src/vendor/stb/*.c"
"${PROJECT_SOURCE_DIR}/src/vendor/imgui/*.cpp"
"${PROJECT_SOURCE_DIR}/src/vendor/imgui/*.c"
)


add_executable(engine 
main.cpp
${all_SRCS}
)

target_link_libraries(engine
glfw 
OpenGL::GL
${IMGUI_DIR}
${CMAKE_DL_LIBS}
${GLEW_LIBRARIES}
)