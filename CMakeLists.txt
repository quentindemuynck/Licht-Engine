cmake_minimum_required(VERSION 3.25)
project(LichtEngine VERSION 1.0 LANGUAGES CXX C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/engine/main.cpp
        src/engine/ServiceLocator.h)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/.gitignore *)

include(Libraries.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE Licht-Engine-Libraries)

target_copy_webgpu_binaries(${PROJECT_NAME})
