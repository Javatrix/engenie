#!/bin/bash
if [ "$1" == "core" ]; then
    rm -rf build
    mkdir build
fi

cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. && make
