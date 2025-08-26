#!/bin/bash
set -e

MIN_POW="${MIN_POW:-1}"
MAX_POW="${MAX_POW:-10}"
TRIALS="${TRIALS:-5}"
CSV_PATH="results/benchmarks.csv"
PLOT_PATH="results/benchmarks.png"

mkdir -p results

echo "Building..."
make clean
make bench

echo "Benchmarking from 2^$MIN_POW to 2^$MAX_POW, trials=$TRIALS"
./bench --min_pow "$MIN_POW" --max_pow "$MAX_POW" --trials "$TRIALS" --csv "$CSV_PATH" | tee results/bench.log

echo "Plotting..."
python3 plot_bench.py "$CSV_PATH" "$PLOT_PATH"

echo "Done."
echo "CSV:  $CSV_PATH"
echo "Plot: $PLOT_PATH"
