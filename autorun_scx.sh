#!/bin/bash

~/sim07_21_3/flysim.out -daemon 8889 &
FLYSIM=$!

echo ${FLYSIM}

./build/main_scx.out
FLYINTEL=$!

echo ${FLYINTEL}

kill ${FLYSIM}
kill ${FLYINTEL}
