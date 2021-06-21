# written by Ryan Puhalovich - github.com/rpuhalovich

cmake_minimum_required(VERSION 3.17.1)
project(LearningOpenGL CXX)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEB")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DREL")

# --- src ------------------------------------------
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/src/gfx/shaders/")
set(RES_DIR "${CMAKE_SOURCE_DIR}/res/")
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE src
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.hpp
    ${SRC_DIR}/*.h
    ${SRC_DIR}/*.vert
    ${SRC_DIR}/*.frag
)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})

set(tgt_inc
    ${SRC_DIR}/gfx
)

# --- lib ------------------------------------------
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")

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

# --- exe ------------------------------------------
add_executable(${PROJECT_NAME} ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgt_inc})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    SHADER_DIR="${SHADER_DIR}"
    RES_DIR="${RES_DIR}"
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
    <vector>
    <string>
    <map>
    <unordered_map>
    <memory>
    <iostream>
    <fstream>
    <sstream>
    
    <glm/glm.hpp>
    <glm/gtc/matrix_transform.hpp>
    <glm/gtc/type_ptr.hpp>
)

if(MSVC)
    target_link_libraries(${PROJECT_NAME} ${lib} opengl32)
elseif(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
    target_link_libraries(${PROJECT_NAME} ${lib} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
endif()

set_target_properties(
    glad
    glfw
    uninstall
    stb_image
    PROPERTIES FOLDER "Libraries"
)
