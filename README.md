# Matrix Multiplication Benchmark (AoA Assignment 1)

This project implements three matrix multiplication algorithms from *CLRS Introduction to Algorithms* (Ch. 4):

1. **Naive triple-loop** (Θ(n³))  
2. **Recursive divide-and-conquer** (Θ(n³))  
3. **Strassen’s algorithm** (Θ(n^2.81))  

It benchmarks them over a range of matrix sizes (both powers of two and non-powers) and outputs runtimes to CSV and plots.

---

## 📂 Project Structure

```
include/        # headers
src/            # implementation
 ├─ matrix.c/h  # common utils, allocation, random gen, add/sub, pad/unpad
 ├─ naive.c     # classical O(n^3) algorithm
 ├─ recursive.c # recursive divide-and-conquer
 ├─ strassen.c  # Strassen algorithm (CLRS S1–S10, P1–P7)
 ├─ main.c      # single-run driver (debug/validation)
 └─ bench.c     # benchmarking (writes CSV)
Makefile
run.sh          # helper script: builds, runs benchmark, calls plotter
plot_bench.py   # plots CSV → PNG
```

---

## ⚙️ Requirements

- **C compiler:** GCC or Clang  
  - macOS: `brew install gcc` (or use built-in Clang).  
  - Windows: use MinGW/MSYS2 (`pacman -S mingw-w64-x86_64-gcc`) or run under WSL.  
- **Python 3** (>=3.8) with `pandas` and `matplotlib`:
  ```bash
  pip install pandas matplotlib
  ```

---

## 🛠️ Build

From the project root:

```bash
make
```

This builds two executables:

- `matmul` → single run with a given size (for correctness checks).
- `bench` → benchmark harness (for graphs/CSV).

Clean build artifacts:

```bash
make clean
```

---

## ▶️ Usage

### 1. Single run (manual)

```bash
./matmul <n>
```

Example:

```bash
./matmul 64
```

This multiplies two random n×n matrices with all three algorithms, prints runtimes, and validates results against the naive method.

---

### 2. Benchmark (automated)

```bash
./bench --min_pow 1 --max_pow 10 --trials 5 --csv results/benchmarks.csv
```

- `--min_pow`, `--max_pow`: size range (tests around 2^p and nearby non-powers).
- `--trials`: how many random trials per n.
- `--csv`: where to write results.

Example: test from 2¹ to 2¹⁰ with 5 trials each:

```bash
./bench --min_pow 1 --max_pow 10 --trials 5 --csv results/benchmarks.csv
```

---

### 3. Run everything via script

```bash
./run.sh
```

This will:
1. Build everything.
2. Run the benchmark across the default range.
3. Save results in `results/benchmarks.csv`.
4. Call `plot_bench.py` to generate `results/benchmarks.png`.

---

### 4. Plot results manually

```bash
python3 plot_bench.py results/benchmarks.csv results/benchmarks.png
```

Options:
- `--show-raw`: also plot raw averages as markers.
- `--no-padmarks`: hide padding markers.

---

## 📝 Notes

- **Padding:** Recursive and Strassen require power-of-two sizes; non-powers are padded to the next 2^k (then unpadded). The CSV records both `n` and `padded_n` so you can see the effect.
- **Timings:** Only the multiplication kernels are timed. Matrix allocation and random generation are excluded.
- **Scales:** Plots are log–log with vertical guides at powers of two.

---

## 💻 Cross-platform

- **macOS (Intel/ARM):** The provided `Makefile` works directly with Clang (default `gcc` wrapper). If you install GNU gcc via Homebrew, you may need to set `CC=gcc-13` (or whichever version).
- **Windows:**
  - With MinGW/MSYS2: open the MinGW64 shell, then run `make`.
  - With WSL: same as Linux/macOS.
- Both environments produce the same CSV and plots.

---

## 📊 Example

After running:

```bash
MIN_POW=1 MAX_POW=10 TRIALS=5 ./run.sh
```

You will get:

- `results/benchmarks.csv`: raw timing data (all trials).
- `results/benchmarks.png`: comparative runtime curves.

---

## 🧾 Source

Algorithms implemented from *Introduction to Algorithms, 4th Edition (Cormen, Leiserson, Rivest, Stein)*, Chapter 4.
