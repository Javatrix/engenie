rm -rf build/*
rmdir build
mkdir build
g++ src/*.c* -Iinclude/ -o build/main -lglfw -lGL && build/main
