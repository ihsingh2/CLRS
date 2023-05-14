main : main.o weighted_directed_graph.o binaryheap.o
	g++ -o main main.o weighted_directed_graph.o binaryheap.o

main.o : main.cpp
	g++ -c main.cpp

weighted_directed_graph.o : weighted_directed_graph.h weighted_directed_graph.cpp
	g++ -c weighted_directed_graph.cpp

binaryheap.o : ../ch06-heapsort/binaryheap.h ../ch06-heapsort/binaryheap.cpp
	g++ -c ../ch06-heapsort/binaryheap.cpp

clean :
	rm main main.o weighted_directed_graph.o binaryheap.o
