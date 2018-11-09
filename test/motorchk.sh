#!/bin/bash

ENA=1
ENB=26
IN=(8 9 7 0)

gpio mode ${ENA} out
gpio mode ${ENB} out
gpio mode ${IN[0]} out
gpio mode ${IN[1]} out
gpio mode ${IN[2]} out
gpio mode ${IN[2]} out


gpio write ${ENA} 1
gpio write ${ENB} 1

gpio write ${IN[0]} 1
gpio write ${IN[1]} 0
gpio write ${IN[2]} 1
gpio write ${IN[3]} 0
sleep 1

gpio write ${IN[0]} 0
gpio write ${IN[1]} 1
gpio write ${IN[2]} 0
gpio write ${IN[3]} 1
sleep 1

gpio write ${IN[0]} 1
gpio write ${IN[1]} 0
gpio write ${IN[2]} 0
gpio write ${IN[3]} 1
sleep 1

gpio write ${IN[0]} 0
gpio write ${IN[1]} 1
gpio write ${IN[2]} 1
gpio write ${IN[3]} 0
sleep 1

gpio write ${IN[0]} 0
gpio write ${IN[1]} 0
gpio write ${IN[2]} 0
gpio write ${IN[3]} 0

gpio write ${ENA} 0
gpio write ${ENB} 0

echo "Motor test finished."
