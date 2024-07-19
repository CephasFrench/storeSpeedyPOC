# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Define the name of the project
project(storeSpeedyPOC)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Define the directories
set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(AISLES_DIR ${SRC_DIR}/aisles)
set(API_DIR ${SRC_DIR}/api)
set(CART_DIR ${SRC_DIR}/cart)
set(ITEMS_DIR ${SRC_DIR}/items)
set(CROW_DIR /Users/cameronhardin/Desktop/storeSpeedyPOC/backEnd/server)  # Set absolute path for Crow

# Find the CURL and Boost library packages, and make them required dependencies
find_package(CURL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler-cpp)

# Include directories
include_directories(${SRC_DIR})
include_directories(${AISLES_DIR})
include_directories(${API_DIR})
include_directories(${CART_DIR})
include_directories(${ITEMS_DIR})
include_directories(${CROW_DIR})  # Include Crow directory
include_directories(${Boost_INCLUDE_DIRS})  # Include Boost directory
include_directories(/opt/homebrew/opt/jsoncpp/include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${POPPLER_INCLUDE_DIRS})

# Link directories
link_directories(/opt/homebrew/opt/jsoncpp/lib)
link_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${POPPLER_LIBRARY_DIRS})

# Define source files
set(SOURCE_FILES
    ${SRC_DIR}/main.cpp
    ${AISLES_DIR}/Aisle.cpp
    ${API_DIR}/api_util.cpp
    ${CART_DIR}/Cart.cpp
    ${ITEMS_DIR}/Item.cpp
    ${SRC_DIR}/StoreSpeedyJsonHandler.cpp
)

# Add an executable target named 'storeSpeedyPOC' built from multiple source files
add_executable(storeSpeedyPOC ${SOURCE_FILES})

# Link the 'libcurl', 'jsoncpp', 'OpenCV', 'poppler', and 'Boost' libraries to the 'storeSpeedyPOC' target
target_link_libraries(storeSpeedyPOC CURL::libcurl jsoncpp ${OpenCV_LIBS} ${POPPLER_LIBRARIES} ${Boost_LIBRARIES})
