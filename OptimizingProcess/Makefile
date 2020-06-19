CC=gcc
CFLAGS=-O0 -pg
DEPS = perf.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: lab3.o perf.o
	$(CC) -o perfexe lab3.o perf.o $(CFLAGS)

clean:
	rm -f *.o perfexe gmon.out