// src/bench.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/matrix.h"

static void usage(const char* prog) {
    printf("Usage: %s [--min_pow P] [--max_pow Q] [--trials T] [--csv path]\n", prog);
    printf("Defaults: P=1, Q=10, T=5, csv=results/benchmarks.csv\n");
}

// Build a mixed list: for each 2^p, and (2^p - 3) and (2^p + 5)
static int build_sizes(int min_pow, int max_pow, int *out, int max_out) {
    int cnt = 0;
    for (int p = min_pow; p <= max_pow; ++p) {
        int base = 1 << p;
        int candidates[3] = { base, base - 3, base + 5 };
        for (int k = 0; k < 3; ++k) {
            int n = candidates[k];
            if (n < 2) continue;
            // de-dup
            int seen = 0;
            for (int i = 0; i < cnt; ++i) if (out[i] == n) { seen = 1; break; }
            if (!seen) {
                if (cnt >= max_out) return cnt;
                out[cnt++] = n;
            }
        }
    }
    // sort
    for (int i = 1; i < cnt; ++i) {
        int x = out[i], j = i - 1;
        while (j >= 0 && out[j] > x) { out[j+1] = out[j]; --j; }
        out[j+1] = x;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    int min_pow = 1, max_pow = 10, trials = 5;
    const char* csv_path = "results/benchmarks.csv";

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--min_pow") && i+1 < argc) { min_pow = atoi(argv[++i]); }
        else if (!strcmp(argv[i], "--max_pow") && i+1 < argc) { max_pow = atoi(argv[++i]); }
        else if (!strcmp(argv[i], "--trials")  && i+1 < argc) { trials  = atoi(argv[++i]); }
        else if (!strcmp(argv[i], "--csv")     && i+1 < argc) { csv_path = argv[++i]; }
        else if (!strcmp(argv[i], "--help")) { usage(argv[0]); return 0; }
        else { usage(argv[0]); return 1; }
    }

    srand((unsigned)time(NULL));

    // sizes
    int sizes[128];
    int ns = build_sizes(min_pow, max_pow, sizes, 128);

    FILE* fp = fopen(csv_path, "w");
    if (!fp) { perror("fopen CSV"); return 4; }
    // Include padded_m
    fprintf(fp, "n,padded_n,algo,trial,ms\n");

    for (int si = 0; si < ns; ++si) {
        int n = sizes[si];
        for (int t = 1; t <= trials; ++t) {
            printf("[n=%d] trial %d/%d: generating matrices...\n", n, t, trials);
            fflush(stdout);

            // Generation not timed
            Matrix A = generateRandomMatrix(n, 1, 100);
            Matrix B = generateRandomMatrix(n, 1, 100);

            // time only multipy
            Matrix Cn = allocate_zero_mat(n);
            clock_t s = clock();
            square_matrix_multiply(A, B, Cn, n);
            clock_t e = clock();
            double naive_ms = ((double)(e - s) / CLOCKS_PER_SEC) * 1000.0;
            fprintf(fp, "%d,%d,naive,%d,%.6f\n", n, n, t, naive_ms);
            printf("    naive:     %.3f ms\n", naive_ms);
            freeMatrix(Cn);

            // padd no timing
            int m = n;
            if (!is_pow_two(n)) { m = 1; while (m < n) m <<= 1; }
            Matrix Ap = (m == n) ? A : pad_matrix(A, n);
            Matrix Bp = (m == n) ? B : pad_matrix(B, n);

            // recusrive call timer onyl around functions calll
            Matrix Cr = allocate_zero_mat(m);
            s = clock();
            multiply_mat_recursive(Ap, Bp, Cr, m, m, m, m);
            e = clock();
            double rec_ms = ((double)(e - s) / CLOCKS_PER_SEC) * 1000.0;
            fprintf(fp, "%d,%d,recursive,%d,%.6f\n", n, m, t, rec_ms);
            printf("    recursive: %.3f ms (padded to %d)\n", rec_ms, m);
            freeMatrix(Cr);

            //Same here for strassen only time around function call
            Matrix Cs = allocate_zero_mat(m);
            s = clock();
            strassen(Ap, Bp, Cs, m);
            e = clock();
            double strassen_ms = ((double)(e - s) / CLOCKS_PER_SEC) * 1000.0;
            fprintf(fp, "%d,%d,strassen,%d,%.6f\n", n, m, t, strassen_ms);
            printf("    strassen:  %.3f ms (padded to %d)\n", strassen_ms, m);

            freeMatrix(Cs);
            if (Ap != A) freeMatrix(Ap);
            if (Bp != B) freeMatrix(Bp);
            freeMatrix(A);
            freeMatrix(B);
        }
        printf("== DONE n=%d ==\n\n", n);
        fflush(stdout);
    }

    fclose(fp);
    printf("CSV written to %s\n", csv_path);
    return 0;
}
