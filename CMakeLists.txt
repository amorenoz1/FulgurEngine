cmake_minimum_required(VERSION 3.16)
project(FulgurEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLM REQUIRED)

add_library(
    FulgurEngine SHARED
    src/utils/ThreadPool.cpp
    src/utils/FulgurUtils.cpp
    src/utils/Logger.cpp
    src/utils/Time.cpp
    src/engine/Application.cpp
    vendor/glad.c
)

target_compile_definitions(FulgurEngine PUBLIC FULGUR_EXPORTS)

target_compile_options(FulgurEngine PUBLIC -Wall -Wextra -g)

target_include_directories(
    FulgurEngine PUBLIC 
    src
    vendor
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    ${Vulkan_INCLUDE_DIR}
)

target_link_libraries(
    FulgurEngine PUBLIC
    glfw
    ${OPENGL_gl_LIBRARY}
    ${GLM_LIBRARIES_DIRS}
    ${OPENAL_LIBRARY}
    ${FREETYPE_LIBRARY_RELEASE}
    ${Vulkan_LIBRARY}
)

