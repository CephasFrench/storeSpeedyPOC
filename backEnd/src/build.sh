#!/bin/bash

BUILD_DIR="./build"

cd "$BUILD_DIR" || { echo "Failed to navigate to build directory"; exit 1; }

rm -rf *

cmake .. || { echo "CMake configuration failed"; exit 1; }

cmake --build . || { echo "Build failed"; exit 1; }

./storeSpeedyPOC || { echo "Execution failed"; exit 1; }
