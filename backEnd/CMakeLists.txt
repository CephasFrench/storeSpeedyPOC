# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Define the name of the project
project(storeSpeedyPOC)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Find the CURL library package, and make it a required dependency
find_package(CURL REQUIRED)

# Include the jsoncpp directories explicitly
include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.5/include)

# Link directories
link_directories(/opt/homebrew/Cellar/jsoncpp/1.9.5/lib)

# Add an executable target named 'storeSpeedyPOC' built from 'getAPIjson.cpp'
add_executable(storeSpeedyPOC getAPIjson.cpp)

# Link the 'libcurl' and 'jsoncpp' libraries to the 'storeSpeedyPOC' target
target_link_libraries(storeSpeedyPOC CURL::libcurl jsoncpp)
