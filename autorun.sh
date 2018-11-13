#!/bin/bash

~/sim07_21_2/flysim07_21_2.out -daemon 8889 &
FLYSIM=$!

echo ${FLYSIM}

sudo ./build/flypixy.out

kill ${FLYSIM}
