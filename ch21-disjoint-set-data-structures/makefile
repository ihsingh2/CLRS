main : main.o disjointset.o
	g++ -o main main.o disjointset.o

main.o : main.cpp
	g++ -c main.cpp

disjointset.o : disjointset.h disjointset.cpp
	g++ -c disjointset.cpp

clean :
	rm main main.o disjointset.o
