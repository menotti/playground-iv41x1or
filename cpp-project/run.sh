#!/bin/sh

sample=$1

mkdir build
cd build

cmake ../ -GNinja -DCMAKE_CXX_COMPILER="/usr/bin/g++" -DOpenCL_INCLUDE_DIR="$OCL_INC" -DOpenCL_LIBRARY="$OCL_LIB/libOpenCL.so" -DCOMPUTECPP_PACKAGE_ROOT_DIR="/usr/local/computecpp" -DSAMPLE_NAME=$sample > /dev/null

export COMPUTECPP_TARGET=host

ninja $sample

./$sample
