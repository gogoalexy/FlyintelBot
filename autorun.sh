#!/bin/bash

~/sim07_21_3/flysim.out -daemon 8889 &
FLYSIM=$!

echo ${FLYSIM}

sudo ./build/flypixy.out
FLYINTEL=$!

echo ${FLYINTEL}

kill ${FLYSIM}
