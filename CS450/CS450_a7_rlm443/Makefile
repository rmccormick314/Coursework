CC=g++
PARAMS=-std=c++14 -fopenmp
TARGETS=point_epsilon point_epsilon_O3

all: $(TARGETS)

point_epsilon:
	$(CC) point_epsilon.cpp -o $@ $(PARAMS)

point_epsilon_O3:
	$(CC) point_epsilon.cpp -o $@ $(PARAMS) -O3

clean:
	rm $(TARGETS)