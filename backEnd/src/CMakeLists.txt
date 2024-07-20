# NOTE: This CMake should work regardless of system

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
set(CROW_DIR ${SRC_DIR}/backEnd/server)  # Assuming Crow is part of the project

# Find the CURL package
# CURL is commonly available on all systems, but the location may vary
find_package(CURL REQUIRED)
if (NOT CURL_FOUND)
    message(FATAL_ERROR "CURL library not found")
endif()

# Find the OpenCV package
# OpenCV can be installed via package managers or built from source
find_package(OpenCV REQUIRED)
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif()

# Find the PkgConfig package
# PkgConfig is a helper tool used to find libraries, commonly available on UNIX systems
find_package(PkgConfig REQUIRED)
if (NOT PkgConfig_FOUND)
    message(FATAL_ERROR "PkgConfig not found")
endif()

# Find the Boost package
# Boost is a portable C++ source libraries suite
find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found")
endif()

# Find Poppler using PkgConfig
# Poppler is a PDF rendering library, often available via package managers
# Flag this as an unnecessary dependency later
pkg_check_modules(POPPLER REQUIRED IMPORTED_TARGET poppler-cpp)
if (NOT POPPLER_FOUND)
    message(FATAL_ERROR "Poppler library not found")
endif()

# Manually find JSONCPP if not found by CMake
# JSONCPP may not always have a CMake configuration file, so we use find_path and find_library
find_path(JSONCPP_INCLUDE_DIR json/json.h)
find_library(JSONCPP_LIBRARY jsoncpp)
if (NOT JSONCPP_INCLUDE_DIR OR NOT JSONCPP_LIBRARY)
    message(FATAL_ERROR "jsoncpp library not found")
endif()

# Include directories
# These include directories need to be set correctly to ensure headers are found
include_directories(${SRC_DIR})
include_directories(${AISLES_DIR})
include_directories(${API_DIR})
include_directories(${CART_DIR})
include_directories(${ITEMS_DIR})
include_directories(${CROW_DIR})  # Include Crow directory
include_directories(${Boost_INCLUDE_DIRS})  # Include Boost directory
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIR})
include_directories(${POPPLER_INCLUDE_DIRS})

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

# Link the libraries to the 'storeSpeedyPOC' target
# Ensure libraries are linked correctly; this may vary based on system and installation method
target_link_libraries(storeSpeedyPOC
    CURL::libcurl
    ${JSONCPP_LIBRARY}
    ${OpenCV_LIBS}
    PkgConfig::POPPLER
    ${Boost_LIBRARIES}
)

# Additional checks for system compatibility

# Check for UNIX-specific settings
if(UNIX)
    message(STATUS "Configuring for UNIX system")
    # Additional UNIX-specific settings can go here
endif()

# Check for Windows-specific settings
if(WIN32)
    message(STATUS "Configuring for Windows system")
    # Ensure libraries and tools are available on Windows
    # Example: find_package might need additional hints for Windows paths
    if (NOT DEFINED CMAKE_PREFIX_PATH)
        set(CMAKE_PREFIX_PATH "C:/path/to/dependencies")
    endif()
    # Additional Windows-specific settings can go here
endif()
