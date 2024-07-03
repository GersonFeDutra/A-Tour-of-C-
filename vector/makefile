vector.out : main.cpp gcm.cache/Vector.gcm
	g++ -std=c++20 -fmodules-ts main.cpp -o vector.out

gcm.cache/Vector.gcm : vector.cpp
	g++ -std=c++20 -fmodules-ts -c vector.cpp

clear :
	rm -rf gcm.cache
