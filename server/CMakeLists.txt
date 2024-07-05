cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 11)

# Add Crow and Boost include directories
include_directories(${CMAKE_SOURCE_DIR} /opt/homebrew/include)

add_executable(Server main.cpp)
