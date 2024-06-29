containers.out : main.o vector.o
	g++ -std=c++20 -o containers.out main.o vector.o

main.o : main.cpp container.hpp vector_container.hpp
	g++ -std=c++20 -c main.cpp

vector.o : vector.cpp vector.hpp
	g++ -std=c++20 -c vector.cpp

clear :
	rm *.o *.out
