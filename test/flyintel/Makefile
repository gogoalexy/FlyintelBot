main.out: main.o CXmodel.o flyintel.o connect_to_flysim.o cltcmd.o
	g++ cltcmd.o connect_to_flysim.o flyintel.o CXmodel.o main.o -std=c++14 -o main.out -Wall -O3
main.o: main.cpp
	g++ -c main.cpp -O3
CXmodel.o: CXmodel.cpp
	g++ -c CXmodel.cpp -O3
flyintel.o: flyintel.cpp
	g++ -c flyintel.cpp -O3
connect_to_flysim.o: connect_to_flysim.cpp
	g++ -c -DDEBUG_FILE connect_to_flysim.cpp -O3
cltcmd.o: cltcmd.cpp
	g++ -c cltcmd.cpp -O3

clean:
	rm main.out main.o connect_to_flysim.o flyintel.o cltcmd.o CXmodel.o
