vector.out : main.o vector.o
	g++ -o vector.out main.o vector.o

main.o : main.cpp
	g++ -c main.cpp

vector.o : vector.cpp vector.hpp
	g++ -c vector.cpp

clear :
	rm *.o *.out
