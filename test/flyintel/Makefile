SHELL = /bin/sh
.SUFFIXES: .cpp .a .o
.PHONY: clean

CXX=g++
#CXXFLAGS= -I/usr/include/libusb-1.0 -I../../../gitrepos/pixy2/src/host/libpixyusb2/include -I../../../gitrepos/pixy2/src/host/arduino/libraries/Pixy2
#INC=-I/
#LDLIBS=../../../gitrepos/pixy2/build/libpixyusb2/libpixy2.a -lusb-1.0
OPT=-O1

SRCS=HC_SR04.cpp Sharp_IR.cpp flyintel.cpp
OBJS=$(patsubst %.cpp,%.o,$(SRCS))


main.out: spikesHandler.o SCXmodel.o cltcmd.o connect_to_flysim.o main.o flyintel.o

	$(CXX) $^ -o $@ -Wall $(OPT)

main.o: main.cpp timer.h
	$(CXX) -c $< -o $@ $(OPT)

spikesHandler.o: spikesHandler.cpp spikesHandler.h

SCXmodel.o: SCXmodel.cpp SCXmodel.h

flyintel.o: flyintel.cpp flyintel.h

connect_to_flysim.o: connect_to_flysim.cpp connect_to_flysim.h

cltcmd.o: cltcmd.cpp cltcmd.h

clean:
	rm -rf main.out *.o
