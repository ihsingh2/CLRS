main : main.o directedgraph.o
	g++ -o main main.o directedgraph.o

main.o : main.cpp
	g++ -c main.cpp

directedgraph.o : directedgraph.h directedgraph.cpp
	g++ -c directedgraph.cpp

clean :
	rm main main.o directedgraph.o
