cmake_minimum_required(VERSION 3.21)
project(EpicGLFWProjectXD)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cxx" "src/*.c")
include_directories(include)

add_executable(main ${SOURCES})
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw)
target_link_libraries(main GL)
