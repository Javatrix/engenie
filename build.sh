rm -rf build/*
mkdir build
g++ src/*.c* -Iinclude/ -o build/main -lglfw -lGL && build/main
