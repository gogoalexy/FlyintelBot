#!/bin/bash

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
function END_COLOR {
	printf "\0330m"
}

WHITE_TEXT
echo "########################################################################################"
echo "+ Building FlyintelBot...                                                              +"
echo "########################################################################################"
NORMAL_TEXT

uname -a

TARGET_BUILD_FOLDER=../build_pc

mkdir -pv $TARGET_BUILD_FOLDER

if [ -e $TARGET_BUILD_FOLDER/main.out ]
then
	cd ../src
    make -f Makefile_pc clean
fi

cd ../src
make -f Makefile_pc

if [ -f $TARGET_BUILD_FOLDER/main.out ]
then
  GREEN_TEXT
  printf "SUCCESS "
else
  RED_TEXT
  printf "FAILURE "
fi
NORMAL_TEXT
echo ""
