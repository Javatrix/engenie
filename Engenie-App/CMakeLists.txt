cmake_minimum_required(VERSION 3.21)
project(EngenieGame)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(EngenieGame ${SOURCES})

add_dependencies(EngenieGame engenie-core)
add_subdirectory(../Engenie-Core ${CMAKE_BINARY_DIR}/Engenie-Core)

include_directories(include ../Engenie-Core/engenie-headers ../Engenie-Core/include)
target_link_libraries(EngenieGame PRIVATE engenie-core)
