#!/bin/bash

mkdir -pv ../build
cd build
cmake ../src
echo "Cmake sucesseed!"
make
echo "Compile complete!"

function WHITE_TEXT {
  printf "\033[1;37m"
}
function NORMAL_TEXT {
  printf "\033[0m"
}
function GREEN_TEXT {
  printf "\033[1;32m"
}
function RED_TEXT {
  printf "\033[1;31m"
}

WHITE_TEXT
echo "########################################################################################"
echo "# Building Get Blocks CPP Demo...                                                      #"
echo "########################################################################################"
NORMAL_TEXT

uname -a

TARGET_BUILD_FOLDER=../build

mkdir -pv $TARGET_BUILD_FOLDER

if [test -e $TARGET_BUILD_FOLDER/main.out]
then
    make clean
fi

cd ../src
make
mv ./get_blocks_cpp_demo ../../../../build/get_blocks_cpp_demo

if [ -f ../../../../build/get_blocks_cpp_demo/get_blocks_cpp_demo ]; then
  GREEN_TEXT
  printf "SUCCESS "
else
  RED_TEXT
  printf "FAILURE "
fi
echo ""
