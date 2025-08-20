# Compiler
CC = gcc
CFLAGS = -Wall -O2 -Iinclude

# Detect OS for potential flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS (Clang default)
    CFLAGS += -D_DARWIN_C_SOURCE
endif

# Files
SRC = src/main.c src/matrix.c src/naive.c
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
	./$(TARGET) 4
