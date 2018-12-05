main.out: flyintel.o
	g++ cltcmd.h flyintel.o flypixy.cpp -o main.out -w
flyintel.o: flyintel.cpp flyintel.h
	g++ -c flyintel.cpp
    
clean:
	rm main.out flyintel.o
