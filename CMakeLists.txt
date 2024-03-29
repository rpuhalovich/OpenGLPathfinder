# written by Ryan Puhalovich - github.com/rpuhalovich

cmake_minimum_required(VERSION 3.17.1)
project(OpenGLPathfinder C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE")

if(UNIX AND NOT APPLE)
    if($ENV{CLION_IDE})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")
    endif()
endif()

# --- src ------------------------------------------
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/src/gfx/shaders/")
set(RES_DIR "${CMAKE_SOURCE_DIR}/res/")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE src
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.hpp
    ${SRC_DIR}/*.h
    ${SRC_DIR}/*.vert
    ${SRC_DIR}/*.frag
)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

set(tgt_inc
    ${SRC_DIR}/board
    ${SRC_DIR}/events
    ${SRC_DIR}/gfx
    ${SRC_DIR}/gfx/util
)

# --- lib ------------------------------------------
# OpenGL on Linux
if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    set(inc ${inc} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
endif()

# glad
add_library(glad "${EXTERN_DIR}/glad/src/glad.c")
set(inc ${inc} "${EXTERN_DIR}/glad/include")
set(lib ${lib} glad)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${EXTERN_DIR}/glfw")
set(lib ${lib} glfw)

# glm
set(inc ${inc} "${EXTERN_DIR}/glm/")

# stb_image
add_library(stb_image "${EXTERN_DIR}/stb_image/stb_image.cpp")
set(tgt_inc ${tgt_inc} "${EXTERN_DIR}/stb_image")
set(lib ${lib} stb_image)

include_directories(${inc})

set_target_properties(${lib} uninstall PROPERTIES FOLDER "Libraries")

# --- exe ------------------------------------------
add_executable(${PROJECT_NAME} ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgt_inc})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    SHADER_DIR="${SHADER_DIR}"
    RES_DIR="${RES_DIR}"
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
    <vector>
    <string>
    <map>
    <unordered_map>
    <memory>
    <iostream>
    <stdio.h>
    <fstream>
    <sstream>
    <algorithm>

    <glm/glm.hpp>
    <glm/gtc/matrix_transform.hpp>
    <glm/gtc/type_ptr.hpp>
)
source_group("Precompile Header File" FILES "${CMAKE_SOURCE_DIR}/build/CMakeFiles/${PROJECT_NAME}.dir/cmake_pch.cxx")

if(MSVC)
    target_link_libraries(${PROJECT_NAME} ${lib} opengl32)
elseif(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
    target_link_libraries(${PROJECT_NAME} ${lib} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} ${lib} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif()
