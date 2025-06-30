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
find_package(OpenAL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLM REQUIRED)

add_library(
    FulgurEngine STATIC
    src/utils/ThreadPool.cpp
    src/utils/FulgurUtils.cpp
    src/utils/Logger.cpp
    src/utils/Time.cpp
    src/gfx/Shader.cpp
    src/gfx/VulkanCommandBuffer.cpp
    src/gfx/VulkanCommandPool.cpp
    src/gfx/VulkanContext.cpp
    src/gfx/VulkanDevice.cpp
    src/gfx/VulkanFrameBuffer.cpp
    src/gfx/VulkanGraphicsPipeline.cpp
    src/gfx/VulkanQueue.cpp
    src/gfx/VulkanSwapChain.cpp
    src/gfx/VulkanSynchronization.cpp
    src/engine/Window.cpp
    src/engine/Application.cpp
)

target_include_directories(
    FulgurEngine PUBLIC 
    src
    ${GLM_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    ${Vulkan_INCLUDE_DIR}
)

target_link_libraries(
    FulgurEngine PUBLIC
    glfw
    ${GLM_LIBRARIES_DIRS}
    ${OPENAL_LIBRARY}
    ${FREETYPE_LIBRARY_RELEASE}
    ${Vulkan_LIBRARY}
)

