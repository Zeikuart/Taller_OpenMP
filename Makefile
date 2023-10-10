CC = gcc
CFLAGS = -Wall -lpthread -fopenmp

.PHONY: all clean

all: pi pi_loopB pi_loopC e_taylor test daxpy_single daxpy_multi

pi: pi.c
	$(CC) -o $@ $^ $(CFLAGS)

pi_loopB: pi_loopB.c
	$(CC) -o $@ $^ $(CFLAGS)

pi_loopC: pi_loopC.c
	$(CC) -o $@ $^ $(CFLAGS)

e_taylor: program_a/e_taylor.c
	$(CC) -o program_a/$@ $^ $(CFLAGS)

daxpy_single: program_b/daxpy_single.c
	$(CC) -o program_b/$@ $^ $(CFLAGS)

daxpy_multi: program_b/daxpy_multi.c
	$(CC) -o program_b/$@ $^ $(CFLAGS)

test: test.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f pi pi_loop pi_loopB pi_loopC program_a/e_taylor test program_b/daxpy_single program_b/daxpy_multi program_a/results/e_taylor_*.txt program_b/results/daxpy_*.txt results/pi_loop_*.txt