cmake_minimum_required(VERSION 3.10)

# Project Name and Language
project(ServiceRegistry CXX)

# Standard Setting: C++11 (Appropriate for the features used)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the directory containing header files
# This ensures that #include "Auto.h" works in source files
include_directories(include)

# Set the MEMTRACE macro for compilation
# The -DMEMTRACE flag is added to all source files.
add_definitions(-DMEMTRACE)

# List all source files
file(GLOB SOURCE_FILES
    src/*.cpp
)

# Create the executable target
add_executable(service_app ${SOURCE_FILES})

# Set compilation options for the executable target
target_compile_options(service_app PRIVATE
    -Wall             # Enable all warnings
    -Wextra           # Enable extra warnings
    -Wpedantic        # Enable pedantic mode
    -g                # Include debugging information
)