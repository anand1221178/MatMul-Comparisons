# Compiler
CC = gcc
CFLAGS = -Wall -O2 -Iinclude

# Files
SRC = src/main.c src/matrix.c src/naive.c src/recursive.c src/strassen.c
OBJ = $(SRC:.c=.o)
TARGET = matmul

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET) 4   # Example: run with n=4
