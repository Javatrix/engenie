# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-src"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-build"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/tmp"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/src/battery-embed-populate-stamp"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/src"
  "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/src/battery-embed-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/src/battery-embed-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/javatrix/Sources/C++/OpenGL/build/_deps/battery-embed-subbuild/battery-embed-populate-prefix/src/battery-embed-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
