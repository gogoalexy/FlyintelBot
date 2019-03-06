main_scx.out: main_scx.o SCXmodel.o flyintel.o connect_to_flysim.o cltcmd.o
	g++ -g cltcmd.o connect_to_flysim.o flyintel.o SCXmodel.o main_scx.o -std=c++14 -o main_scx.out -Wall
main_scx.o: main_scx.cpp
	g++ -c main_scx.cpp
SCXmodel.o: SCXmodel.cpp
	g++ -c SCXmodel.cpp
flyintel.o: flyintel.cpp
	g++ -c flyintel.cpp
connect_to_flysim.o: connect_to_flysim.cpp
	g++ -DDEBUG -c connect_to_flysim.cpp
cltcmd.o: cltcmd.cpp
	g++ -c cltcmd.cpp

clean:
	rm main.out main.o connect_to_flysim.o flyintel.o cltcmd.o CXmodel.o
