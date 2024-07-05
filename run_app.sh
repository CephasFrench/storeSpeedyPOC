#!/bin/bash

# Function to start the backend
start_backend() {
    echo "Starting backend..."

    BACKEND_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src"
    BUILD_DIR="$BACKEND_DIR/build"

    # Check if the backend directory exists
    if [ ! -d "$BACKEND_DIR" ]; then
        echo "Backend directory does not exist: $BACKEND_DIR"
        exit 1
    fi
    
    # Check if CMakeLists.txt exists
    if [ ! -f "$BACKEND_DIR/CMakeLists.txt" ]; then
        echo "CMakeLists.txt not found in $BACKEND_DIR"
        exit 1
    fi

    # Navigate to the backend directory
    cd "$BACKEND_DIR" || { echo "Failed to navigate to backend directory"; exit 1; }

    # Clean, configure, build, and run the backend
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || { echo "Failed to navigate to build directory"; exit 1; }

    # Manually set the source directory for CMake
    cmake "$BACKEND_DIR" || { echo "CMake configuration failed"; exit 1; }
    cmake --build . || { echo "Build failed"; exit 1; }

    # Run the backend server
    ./storeSpeedyPOC &
    BACKEND_PID=$!

    # Return to the root directory
    cd ../../../..
}

# Function to start the frontend
start_frontend() {
    echo "Starting frontend..."

    FRONTEND_DIR="./frontEnd"

    # Navigate to the frontend directory
    if [ ! -d "$FRONTEND_DIR" ]; then
        echo "Frontend directory does not exist: $FRONTEND_DIR"
        exit 1
    fi
    cd "$FRONTEND_DIR" || { echo "Failed to navigate to frontend directory"; exit 1; }

    # Start Expo server
    expo start &
    FRONTEND_PID=$!

    # Return to the root directory
    cd ..
}

# Trap to kill background processes on script exit
trap "kill $BACKEND_PID $FRONTEND_PID" EXIT

# Start the backend and frontend
start_backend
start_frontend

echo "App is running. Backend and frontend have been started."
