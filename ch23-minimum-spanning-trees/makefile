main : main.o undirectedgraph.o binaryheap.o disjointset.o
	g++ -o main main.o undirectedgraph.o binaryheap.o disjointset.o

main.o : main.cpp
	g++ -c main.cpp

undirectedgraph.o : undirectedgraph.h undirectedgraph.cpp
	g++ -c undirectedgraph.cpp

binaryheap.o : ../ch06-heapsort/binaryheap.h ../ch06-heapsort/binaryheap.cpp
	g++ -c ../ch06-heapsort/binaryheap.cpp

disjointset.o : ../ch21-disjoint-set-data-structures/disjointset.h ../ch21-disjoint-set-data-structures/disjointset.cpp
	g++ -c ../ch21-disjoint-set-data-structures/disjointset.cpp

clean :
	rm main main.o undirectedgraph.o binaryheap.o disjointset.o
