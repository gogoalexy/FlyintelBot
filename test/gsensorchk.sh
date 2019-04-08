#!/bin/bash

touch grecord.log

ENA=23
ENB=24
ENC=1
END=26
INF=(3 2 4 5)
INB=(22 21 25 27)

echo "S\n" >> grecord.log
echo gpio -x mcp3004:100:0 aread 104 >> grecord.log
echo '\n' >> grecord.log

gpio mode ${INF[0]} out
gpio mode ${INF[1]} out
gpio mode ${INF[2]} out
gpio mode ${INF[3]} out
gpio mode ${INB[0]} out
gpio mode ${INB[1]} out
gpio mode ${INB[2]} out
gpio mode ${INB[3]} out

echo "F\n" >> grecord.log
gpio write ${INF[0]} 1
gpio write ${INF[1]} 0
gpio write ${INF[2]} 1
gpio write ${INF[3]} 0
gpio write ${INB[0]} 1
gpio write ${INB[1]} 0
gpio write ${INB[2]} 1
gpio write ${INB[3]} 0
echo gpio -x mcp3004:100:0 aread 104 >> grecord.log
echo '\n' >> grecord.log
sleep 0.3

echo "B\n" >> grecord.log
gpio write ${INF[0]} 0
gpio write ${INF[1]} 1
gpio write ${INF[2]} 0
gpio write ${INF[3]} 1
gpio write ${INB[0]} 0
gpio write ${INB[1]} 1
gpio write ${INB[2]} 0
gpio write ${INB[3]} 1
echo gpio -x mcp3004:100:0 aread 104 >> grecord.log
echo '\n' >> grecord.log
sleep 0.3

echo "L\n" >> grecord.log
gpio write ${INF[0]} 0
gpio write ${INF[1]} 1
gpio write ${INF[2]} 1
gpio write ${INF[3]} 0
gpio write ${INB[0]} 0
gpio write ${INB[1]} 1
gpio write ${INB[2]} 1
gpio write ${INB[3]} 0
echo gpio -x mcp3004:100:0 aread 104 >> grecord.log
echo '\n' >> grecord.log
sleep 0.3

echo "R\n" >> grecord.log
gpio write ${INF[0]} 1
gpio write ${INF[1]} 0
gpio write ${INF[2]} 0
gpio write ${INF[3]} 1
gpio write ${INB[0]} 1
gpio write ${INB[1]} 0
gpio write ${INB[2]} 0
gpio write ${INB[3]} 1
echo gpio -x mcp3004:100:0 aread 104 >> grecord.log
echo '\n' >> grecord.log
sleep 0.3

gpio write ${INF[0]} 0
gpio write ${INF[1]} 0
gpio write ${INF[2]} 0
gpio write ${INF[3]} 0
gpio write ${INB[0]} 0
gpio write ${INB[1]} 0
gpio write ${INB[2]} 0
gpio write ${INB[3]} 0

echo "END" >> grecord.log
