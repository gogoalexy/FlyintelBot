CXX=g++
CPPFLAGS=-g -Winline
LDLIBS=-lwiringPi

all: matrixChk.cpp monitor.o
	$(CXX) $(CPPFLAGS) -o matrixChk.out matrixChk.cpp monitor.o max7219.o $(LDLIBS)

monitor.o: monitor.cpp max7219.o
	$(CXX) -c $(CPPFLAGS) -o monitor.o monitor.cpp

max7219.o: max7219.cpp
	$(CXX) -c $(CPPFLAGS) -o max7219.o max7219.cpp

clean:
	rm matrixChk.out monitor.o max7219.o

