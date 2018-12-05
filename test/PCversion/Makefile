main.out: cltcmd.h flypixy.cpp flyintel.o
	g++ cltcmd.h flyintel.o flypixy.cpp -std=c++11 -o main.out -w
flyintel.o: flyintel.cpp flyintel.h
	g++ -c flyintel.cpp
    
clean:
	rm main.out flyintel.o
