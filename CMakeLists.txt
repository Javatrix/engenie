cmake_minimum_required(VERSION 3.21)
project(EpicGLFWProjectXD)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cxx" "src/*.c")
include_directories(include)

include(FetchContent)
FetchContent_Declare(
  battery-embed
  GIT_REPOSITORY https://github.com/batterycenter/embed.git
  GIT_TAG        v1.2.11
)
FetchContent_MakeAvailable(battery-embed)

add_executable(main ${SOURCES})
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw)
target_link_libraries(main GL)
