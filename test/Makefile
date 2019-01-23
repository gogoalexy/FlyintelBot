CXX=g++
CPPFLAGS=-g -I/usr/include/libusb-1.0 -I../../../gitrepo/pixy2/src/host/libpixyusb2/include -I../../../gitrepo/pixy2/src/host/arduino/libraries/Pixy2
LDLIBS=../../../gitrepo/pixy2/build/libpixyusb2/libpixy2.a -lusb-1.0

OBJS=pixy2chk.cpp


all: pixy2chk.o pixycam.o
	$(CXX) $(CPPFLAGS) -o pixy2chk.out pixy2chk.o pixycam.o $(LDLIBS)

pixy2chk.o: $(OBJS)
	$(CXX) -c $(CPPFLAGS) -o pixy2chk.o $(OBJS)

pixycam.o: ../src/pixycam.cpp
	$(CXX) -c $(CPPFLAGS) -o pixycam.o ../src/pixycam.cpp

clean:
	rm pixy2chk.out pixy2chk.o pixycam.o

