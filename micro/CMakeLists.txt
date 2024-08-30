cmake_minimum_required(VERSION 3.10)
project(microdrive)

set(CMAKE_CXX_STANDARD 14)

# Find the pybind11 package
find_package(pybind11 REQUIRED)

# Specify the directory where your microdrive library is located
# You may need to adjust this if your library is in a different location
set(MICRODRIVE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add the source file that contains the pybind11 bindings
add_library(microdrive MODULE microdrive_pybind.cpp)

# Include the pybind11 headers
target_include_directories(microdrive PRIVATE ${pybind11_INCLUDE_DIRS})

# Link against the microdrive library (this is the shared library, not the CMake target)
target_link_libraries(microdrive PRIVATE /usr/lib/libmicrodrive.so)

# Set the properties for the output Python module
set_target_properties(microdrive PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
)
