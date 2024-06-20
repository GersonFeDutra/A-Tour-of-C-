vector.out : main.o vector.o
	g++ -std=c++20 -fmodules-ts  -o vector.out main.o vector.o

main.o : main.cpp
	g++ -std=c++20 -fmodules-ts  -c main.cpp

vector.o : vector.cpp
	g++ -std=c++20 -fmodules-ts -c vector.cpp

clear :
	rm *.o *.out
