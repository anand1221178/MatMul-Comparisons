# Makefile
CC = gcc
CFLAGS = -Wall -O2 -Iinclude

SRC_COMMON = src/matrix.c src/naive.c src/recursive.c src/strassen.c
OBJ_COMMON = $(SRC_COMMON:.c=.o)

#for making a single one
MATMUL_SRC = src/main.c $(SRC_COMMON)
MATMUL_OBJ = $(MATMUL_SRC:.c=.o)
TARGET1 = matmul

# make benchmark
BENCH_SRC = src/bench.c $(SRC_COMMON)
BENCH_OBJ = $(BENCH_SRC:.c=.o)
TARGET2 = bench

.PHONY: all clean run bench

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(MATMUL_OBJ)
	$(CC) $(CFLAGS) -o $@ $(MATMUL_OBJ)

$(TARGET2): $(BENCH_OBJ)
	$(CC) $(CFLAGS) -o $@ $(BENCH_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MATMUL_OBJ) $(BENCH_OBJ) $(TARGET1) $(TARGET2)

run: $(TARGET2)
	./bench
