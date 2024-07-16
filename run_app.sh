#!/bin/bash

# Function to check for updates
check_for_updates() {
    read -p "Do you want to check for updates in necessary libraries and packages? (y/n): " -r
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "Checking for updates in necessary libraries and packages..."
        if command -v brew > /dev/null; then
            brew update && brew upgrade
        fi
        if command -v npm > /dev/null; then
            npm update
        fi
    else
        echo "Skipping updates."
    fi
}

# Function to kill processes using a specific port
kill_process_on_port() {
    PORT=$1
    if command -v lsof > /dev/null; then
        lsof -ti tcp:$PORT | xargs kill -9
    else
        echo "lsof is not available to kill processes on port $PORT"
        exit 1
    fi
}

# Function to start the backend
start_backend() {
    echo "Starting backend..."

    BACKEND_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src"
    BUILD_DIR="$BACKEND_DIR/build"

    # Kill any process using port 8080
    kill_process_on_port 8080

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

    FRONTEND_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/frontEnd"

    # Kill any process using port 8081 and 8082
    kill_process_on_port 8081
    kill_process_on_port 8082

    # Navigate to the frontend directory
    if [ ! -d "$FRONTEND_DIR" ]; then
        echo "Frontend directory does not exist: $FRONTEND_DIR"
        exit 1
    fi

    # Use osascript to open a new Terminal window and run npx expo start
    osascript <<EOF
tell application "Terminal"
    do script "cd $FRONTEND_DIR && npx expo start --port 8082"
end tell
EOF
}

# Ensure the script runs in an interactive terminal
if [ -t 1 ]; then
    echo "Running in an interactive terminal."
else
    echo "This script must be run in an interactive terminal."
    exit 1
fi

# Ask the user whether to check for updates
check_for_updates

# Trap to kill background processes on script exit
trap "if [ ! -z $BACKEND_PID ]; then kill $BACKEND_PID; fi" EXIT

# Start the backend and frontend
start_backend
start_frontend

echo "App is running. Backend has been started. Frontend is starting in a new terminal window."