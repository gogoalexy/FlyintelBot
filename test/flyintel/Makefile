SHELL = /bin/sh
.SUFFIXES: .cpp .a .o

CXX=g++

main.out: SCXmodel.o cltcmd.o connect_to_flysim.o main.o flyintel.o 
	$(CXX) $^ -o $@ -Wall

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o

SCXmodel.o: SCXmodel.cpp SCXmodel.h
	$(CXX) -c SCXmodel.cpp -o SCXmodel.o

flyintel.o: flyintel.cpp flyintel.h
	$(CXX) -c flyintel.cpp -o flyintel.o

connect_to_flysim.o: connect_to_flysim.cpp connect_to_flysim.h
	$(CXX) -c connect_to_flysim.cpp -o connect_to_flysim.o

cltcmd.o: cltcmd.cpp cltcmd.h
	$(CXX) -c cltcmd.cpp -o cltcmd.o

clean:
	rm -rf main.out *.o
