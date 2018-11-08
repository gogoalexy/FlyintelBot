#!/bin/bash

mkdir -pv build
cd build
cmake ../src
echo "Cmake sucesseed!"
make
echo "Compile complete!"
