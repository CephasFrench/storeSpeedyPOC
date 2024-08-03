#!/bin/bash

# Function to start the frontend
start_frontend() {
    echo "Starting frontend..."

    # Determine the frontend directory relative to the script location
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    FRONTEND_DIR="$SCRIPT_DIR/frontEnd"  # Adjusted path

    # Debug prints
    echo "Current script directory: $SCRIPT_DIR"
    echo "Expected frontend directory: $FRONTEND_DIR"

    # Navigate to the frontend directory
    if [ ! -d "$FRONTEND_DIR" ]; then
        echo "Frontend directory does not exist: $FRONTEND_DIR"
        exit 1
    fi

    # Install frontend dependencies
    echo "Installing frontend dependencies..."
    cd "$FRONTEND_DIR" || { echo "Failed to navigate to frontend directory"; exit 1; }
    npm install || { echo "Failed to install frontend dependencies"; exit 1; }

    # Start the frontend server in the same terminal
    echo "Starting the frontend server..."
    npx expo start --port 8082
}

# Ensure the script runs in an interactive terminal
if [ -t 1 ]; then
    echo "Running in an interactive terminal."
else
    echo "This script must be run in an interactive terminal."
    exit 1
fi

# Start the frontend
start_frontend

echo "Frontend has been started."
