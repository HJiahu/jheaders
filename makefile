main:main.cpp
	g++ -std=c++11 main.cpp
.PHONY:clean
clean:
	rm -f *.o *.out
