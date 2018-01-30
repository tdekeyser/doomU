#!/bin/bash

# Create build folder
rm -rf build/
mkdir build/
cd build/


# Compile code using CMake
if [ $1 == "test" ]
    then
        cmake .. -DSOURCE=OFF -DTEST=ON
        make
        ./doomU_test $2
    else
        cmake .. -DSOURCE=ON -DTEST=OFF
        make
fi


