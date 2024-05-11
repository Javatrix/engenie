cmake_minimum_required(VERSION 3.21)
project(Engenie-Core)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(engenie-core STATIC ${SOURCES} ${HEADERS})
include_directories(include engenie-headers)
find_package(glfw3 REQUIRED)
target_link_libraries(engenie-core glfw)
target_link_libraries(engenie-core GL)
target_link_libraries(engenie-core assimp)
