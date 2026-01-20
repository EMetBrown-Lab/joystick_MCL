cmake_minimum_required(VERSION 3.10)
project(nanostage)

set(CMAKE_CXX_STANDARD 14)

# Find the pybind11 package
find_package(pybind11 REQUIRED)

# Specify the directory where your nanostage library is located
# You may need to adjust this if your library is in a different location
set(NANOSTAGE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add the source file that contains the pybind11 bindings
add_library(nanostage MODULE nanostage_pybind.cpp)

# Include the pybind11 headers
target_include_directories(nanostage PRIVATE ${pybind11_INCLUDE_DIRS})

# Link against the microdrive library (this is the shared library, not the CMake target)
target_link_libraries(nanostage PRIVATE /usr/lib/libmadlib.so)

# Set the properties for the output Python module
set_target_properties(nanostage PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
