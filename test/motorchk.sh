#!/bin/bash

ENA=1
ENB=26
IN=(3 2 4 5)

echo "Front motor"

for (( c=1; c<=2; c++))
do
	gpio mode ${ENA} out
	gpio mode ${ENB} out
	gpio mode ${IN[0]} out
	gpio mode ${IN[1]} out
	gpio mode ${IN[2]} out
	gpio mode ${IN[2]} out

	gpio write ${ENA} 1
	gpio write ${ENB} 1

	echo "F"
	gpio write ${IN[0]} 1
	gpio write ${IN[1]} 0
	gpio write ${IN[2]} 1
	gpio write ${IN[3]} 0
	sleep 1

	echo "B"
	gpio write ${IN[0]} 0
	gpio write ${IN[1]} 1
	gpio write ${IN[2]} 0
	gpio write ${IN[3]} 1
	sleep 1

	echo "L"
	gpio write ${IN[0]} 0
	gpio write ${IN[1]} 1
	gpio write ${IN[2]} 1
	gpio write ${IN[3]} 0
	sleep 1

	echo "R"
	gpio write ${IN[0]} 1
	gpio write ${IN[1]} 0
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
	IN=(22 21 25 27)
	echo "Rear motor"
done

echo "Motor test finished."
