prog: main.o Executive.o
	g++ -std=c++11 -g -Wall main.o Executive.o -o prog

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp Attack.h BoardSetup.h Check.h Ingame.h Printboard.h Move.h
	g++ -std=c++11 -g -Wall -c Executive.cpp

clean:
	rm *.o prog
