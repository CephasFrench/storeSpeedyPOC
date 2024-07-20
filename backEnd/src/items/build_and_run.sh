#!/bin/bash

# Set the working directory
WORKING_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/items"
JSON_HANDLER_DIR="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src"
INCLUDE_DIRS="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src /Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/aisles /Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/api /Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/cart /Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/items"
AISLE_CPP="/Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/src/aisles/aisle.cpp"

# Set the JSONCPP and CURL directories based on the CMake file information
JSONCPP_INCLUDE_DIR="/opt/homebrew/opt/jsoncpp/include"  # Update this path to match your system's setup if different
JSONCPP_LIB_DIR="/opt/homebrew/opt/jsoncpp/lib"          # Update this path to match your system's setup if different
CURL_INCLUDE_DIR="/usr/local/opt/curl/include"           # Update this path to match your system's setup if different
CURL_LIB_DIR="/usr/local/opt/curl/lib"                   # Update this path to match your system's setup if different

# Set the default location
LOCATION="DefaultLoc"

# Navigate to the working directory
cd "$WORKING_DIR" || { echo "Failed to navigate to working directory"; exit 1; }

# Ensure filenames are case-insensitive by renaming if necessary
mv "item.h" "Item.h" 2>/dev/null
mv "item.cpp" "Item.cpp" 2>/dev/null

# Compile the files
g++ -std=c++11 -I"$JSON_HANDLER_DIR" -I"$JSONCPP_INCLUDE_DIR" -I"$CURL_INCLUDE_DIR" $(for dir in $INCLUDE_DIRS; do echo -I"$dir"; done) -o itemTesting itemTesting.cpp Item.cpp "$JSON_HANDLER_DIR/StoreSpeedyJsonHandler.cpp" "$AISLE_CPP" -L"$JSONCPP_LIB_DIR" -L"$CURL_LIB_DIR" -ljsoncpp -lcurl

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./itemTesting
else
    echo "Compilation failed."
    exit 1
fi
