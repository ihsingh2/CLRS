main : main.o daryheap.o youngtableau.o
	g++ -o main main.o daryheap.o youngtableau.o

main.o : main.cpp
	g++ -c main.cpp

daryheap.o : daryheap.h daryheap.cpp
	g++ -c daryheap.cpp

youngtableau.o : youngtableau.h youngtableau.cpp
	g++ -c youngtableau.cpp

clean :
	rm main main.o daryheap.o youngtableau.o
