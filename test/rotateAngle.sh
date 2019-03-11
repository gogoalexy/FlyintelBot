#!/bin/bash

ENA=23
ENB=24
ENC=1
END=26
IN=(3 2 4 5 22 21 25 27)

gpio mode ${ENA} pwm
gpio mode ${ENB} pwm
gpio mode ${ENC} pwm
gpio mode ${END} pwm
gpio mode ${IN[0]} out
gpio mode ${IN[1]} out
gpio mode ${IN[2]} out
gpio mode ${IN[3]} out
gpio mode ${IN[4]} out
gpio mode ${IN[5]} out
gpio mode ${IN[6]} out
gpio mode ${IN[7]} out

echo "right"

gpio pwm ${ENA} 500
gpio pwm ${ENB} 500
gpio pwm ${ENC} 500
gpio pwm ${END} 500

gpio write ${IN[0]} 1
gpio write ${IN[1]} 0
gpio write ${IN[2]} 1
gpio write ${IN[3]} 0
gpio write ${IN[4]} 1
gpio write ${IN[5]} 0
gpio write ${IN[6]} 1
gpio write ${IN[7]} 0

gpio delay 300

echo "Done."