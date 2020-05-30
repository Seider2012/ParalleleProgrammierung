CC=gcc
CC_FLAGS=-O3 -g3 -lm -fopenmp

.PHONEY: all
all: real

SRC=$(wildcard *.c)

real: $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC) -o real

.PHONEY: clean
clean:
	@rm real

.PHONEY: run
run: all
	@echo "Sequential:"
	@/usr/bin/time -v ./real 0
	@echo
	@echo "Parallel:"
	@/usr/bin/time -v ./real 1
	@echo
