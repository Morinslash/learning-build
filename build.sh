
#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Handle the "clean" argument first to avoid unnecessary steps
if [ "$1" == "clean" ]; then
    rm -rf $BUILD_DIR
    echo "Build directory cleaned."
    exit 0
fi

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Run CMake configuration
cmake -S . -B $BUILD_DIR

# Build the project
cmake --build $BUILD_DIR

# Optionally run tests if "test" argument is provided
if [ "$1" == "test" ]; then
    ctest --test-dir $BUILD_DIR
fi

