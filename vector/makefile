# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic

vector.out : main.o vector.o
	$(CXX) $(CXXFLAGS) -o vector.out main.o vector.o

vector.o : vector.cpp vector.hpp
	$(CXX) $(CXXFLAGS) -c vector.cpp

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile using modules : support is not complete
# vector.out : main.cpp gcm.cache/Vector.gcm
# 	g++ -std=c++20 -fmodules-ts main.cpp -o vector.out
# 
# gcm.cache/Vector.gcm : vector.cpp
# 	g++ -std=c++20 -fmodules-ts -c vector.cpp
# 
# clear :
# 	rm -rf gcm.cache

# Debug target
debug: CXXFLAGS += -DDEBUG
debug: vector.out

clear :
	rm *.o vector.out
