#!/bin/bash

echo "test IR ch0"
gpio -x mcp3004:100:0 aread 100
echo "test IR ch1"
gpio -x mcp3004:100:0 aread 101
echo "test IR ch2"
gpio -x mcp3004:100:0 aread 102
echo "test IR ch3"
gpio -x mcp3004:100:0 aread 103
echo "completed"
