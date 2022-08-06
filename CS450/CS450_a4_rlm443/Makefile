CC=g++
PARAMS=-std=c++14 -pthread
TARGETS= a4_q1 a4_q2_to_optimize a4_q2_optimized

all: $(TARGETS)

a4_q1:
	$(CC) a4_q1.cpp -o $@ $(PARAMS)

a4_q2_to_optimize:
	$(CC) a4_q2_to_optimize.cpp -o $@ $(PARAMS)

a4_q2_optimized:
	$(CC) a4_q2_optimized.cpp -o $@ $(PARAMS)

clean:
	rm $(TARGETS)