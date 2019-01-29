main.out: cltcmd.h main.cpp flyintel.o
	g++ cltcmd.h flyintel.o main.cpp -std=c++11 -o main.out -w
flyintel.o: flyintel.cpp flyintel.h
	g++ -c flyintel.cpp -Wall
    
clean:
	rm main.out flyintel.o
