shapes.out : main.o smiley.o
	g++ -std=c++20 -o shapes.out main.o smiley.o

main.o : main.cpp 
	g++ -std=c++20 -c main.cpp

smiley.o : smiley.cpp shapes.hpp circle.hpp smiley.hpp
	g++ -std=c++20 -c smiley.cpp

clear :
	rm *.o *.out
