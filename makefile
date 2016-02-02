# makefile

all: Main.cpp
	g++ -std=c++11 -o main Main.cpp

clean:
	$(RM) main