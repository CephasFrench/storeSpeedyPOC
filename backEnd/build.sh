#!/bin/bash

# Set the build directory
BUILD_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/build"

# Navigate to your build directory
cd "$BUILD_DIR" || { echo "Failed to navigate to build directory"; exit 1; }

# Remove all existing build files
rm -rf *

# Run cmake to configure the project
cmake .. || { echo "CMake configuration failed"; exit 1; }

# Build the project
cmake --build . || { echo "Build failed"; exit 1; }

# Run the resulting executable
./storeSpeedyPOC || { echo "Execution failed"; exit 1; }

