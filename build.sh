rm -rf build/*
rmdir build
mkdir build
g++ src/*.cpp -Iinclude/ -o build/main -lglfw -lGL && build/main
