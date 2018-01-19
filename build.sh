#!/bin/bash

# Create build folder
rm -rf build/
mkdir build/
cd build/

# Compile code using CMake
cmake ..
make

# Run tests
./run_all_tests
