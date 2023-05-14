main : main.o weighted_directed_graph.o
	g++ -o main main.o weighted_directed_graph.o

main.o : main.cpp
	g++ -c main.cpp

weighted_directed_graph.o : weighted_directed_graph.h weighted_directed_graph.cpp
	g++ -c weighted_directed_graph.cpp

clean :
	rm main main.o weighted_directed_graph.o
