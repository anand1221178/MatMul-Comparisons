#!/bin/bash
# Simple script to build and run your program

make clean
make

if [ ! -f ./matmul ]; then
  echo "Build failed!"
  exit 1
fi

# Run with a few different matrix sizes
for n in 32 64 128; do
  echo "Running with n=$n"
  ./matmul $n
  echo
done
