#!/bin/bash

ENA=1
ENB=26
IN=(2 3 4 5)

echo "Left motor"

for (( c=1; c<=2; c++))
do
	gpio mode ${ENA} pwm
	gpio mode ${ENB} pwm
	gpio mode ${IN[0]} out
	gpio mode ${IN[1]} out
	gpio mode ${IN[2]} out
	gpio mode ${IN[3]} out

	gpio pwm ${ENA} 500
	gpio pwm ${ENB} 500

	echo "D"
	gpio write ${IN[0]} 1
	gpio write ${IN[1]} 0
	gpio write ${IN[2]} 1
	gpio write ${IN[3]} 0
	sleep 1

	echo "R"
	gpio write ${IN[0]} 0
	gpio write ${IN[1]} 1
	gpio write ${IN[2]} 0
	gpio write ${IN[3]} 1
	sleep 1

	gpio write ${IN[0]} 0
	gpio write ${IN[1]} 0
	gpio write ${IN[2]} 0
	gpio write ${IN[3]} 0

	gpio write ${ENA} 0
	gpio write ${ENB} 0

	ENA=23
	ENB=24
	IN=(22 21 27 25)
	echo "Right motor"
done

EN=(1 26 23 24)
IN=(2 3 4 5 22 21 27 25)

gpio pwm ${EN[0]}
gpio pwm ${EN[1]}
gpio pwm ${EN[2]}
gpio pwm ${EN[3]}

gpio write ${IN[0]} 1
gpio write ${IN[1]} 0
gpio write ${IN[2]} 1
gpio write ${IN[3]} 0
gpio write ${IN[4]} 1
gpio write ${IN[5]} 0
gpio write ${IN[6]} 1
gpio write ${IN[7]} 0
sleep 2

gpio write ${IN[0]} 0
gpio write ${IN[1]} 0
gpio write ${IN[2]} 0
gpio write ${IN[3]} 0
gpio write ${IN[4]} 0
gpio write ${IN[5]} 0
gpio write ${IN[6]} 0
gpio write ${IN[7]} 0

gpio pwm ${EN[0]} 0
gpio pwm ${EN[1]} 0
gpio pwm ${EN[2]} 0
gpio pwm ${EN[3]} 0

echo "Motor test finished."
