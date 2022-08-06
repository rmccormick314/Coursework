CC=g++
PARAMS=-std=c++14 -fopenmp -O3
TARGETS=matrixMultiply

all: $(TARGETS)

matrixMultiply:
	$(CC) $@.cpp -o $@ $(PARAMS)

clean:
	rm $(TARGETS)
