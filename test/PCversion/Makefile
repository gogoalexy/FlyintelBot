main.out: main.o flyintel.o connect_to_flysim.o cltcmd.o
	g++ cltcmd.o connect_to_flysim.o flyintel.o main.o -std=c++14 -o main.out -Wall
main.o: main.cpp
	g++ -c main.cpp
flyintel.o: flyintel.cpp
	g++ -c flyintel.cpp
connect_to_flysim.o: connect_to_flysim.cpp
	g++ -c connect_to_flysim.cpp
cltcmd.o: cltcmd.cpp
	g++ -c cltcmd.cpp
    
clean:
	rm main.out main.o connect_to_flysim.o flyintel.o cltcmd.o
