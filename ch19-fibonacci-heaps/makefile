main : main.o fibheap.o
	g++ -o main main.o fibheap.o

main.o : main.cpp
	g++ -c main.cpp

fibheap.o : fibheap.h fibheap.cpp
	g++ -c fibheap.cpp

clean :
	rm main main.o fibheap.o
