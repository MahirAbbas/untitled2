cmake_minimum_required(VERSION 3.24)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(imgui)
add_subdirectory(imgui/backends)
add_executable(untitled2 imgui/glad.c main.cpp Vector.h shapes.h)
target_link_libraries(untitled2 glfw GL dl pthread imgui backends )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
