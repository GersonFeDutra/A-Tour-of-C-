vector.out : main.o vector.o
	g++ -std=c++20 -o vector.out main.o vector.o

vector.o : vector.cpp vector.hpp
	g++ -std=c++20 -c vector.cpp

main.o : main.cpp
	g++ -std=c++20 -c main.cpp

# vector.out : main.cpp gcm.cache/Vector.gcm
# 	g++ -std=c++20 -fmodules-ts main.cpp -o vector.out
# 
# gcm.cache/Vector.gcm : vector.cpp
# 	g++ -std=c++20 -fmodules-ts -c vector.cpp

clear :
	rm -rf gcm.cache
