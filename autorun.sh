#!/bin/bash

~/sim08_13/flysim.out -daemon 8889 &
#~/sim07_21_3/flysim.out -daemon 8889 &
FLYSIM=$!

echo ${FLYSIM}

sudo ./build/main.out
FLYINTEL=$!

echo ${FLYINTEL}

kill ${FLYSIM}
