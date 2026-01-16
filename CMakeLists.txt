cmake_minimum_required(VERSION 3.15)
project(FulgurEngine 
        VERSION 1.0 
        DESCRIPTION "Game engine and Game" 
        LANGUAGES CXX C) 

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenAL REQUIRED)

add_executable(${PROJECT_NAME})

enable_testing()
add_subdirectory(src)
add_subdirectory(vendor)
add_subdirectory(tests)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${glm_INCLUDE_DIRS}
    ${glfw3_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIR}
    src
    vendor
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ${glm_LIBRARIES}
    ${glfw3_LIBRARIES}
    ${OPENAL_LIBRARY}
)

