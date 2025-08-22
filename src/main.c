// MAIN DRIVER FILE -> benchmarking and data output
#include "stdio.h"
#include "stdlib.h" //for atoi
#include "time.h"
#include "../include/matrix.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // from <stdlib.h>
    if (n <= 0) {
        printf("Matrix size must be positive!\n");
        return 2;
    }

    printf("Matrix size = %d\n", n);
    srand(time(NULL));


    // Alllocate matrix random for A and B, C is just space
    Matrix A = generateRandomMatrix(n,1,100);
    Matrix B = generateRandomMatrix(n,1,100);
    Matrix C_naive = allocate_zero_mat(n);

    // Do naive
    clock_t start = clock();
    square_matrix_multiply(A,B,C_naive,n);
    clock_t end = clock();

    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("Naive multiplication (n=%d): %.3f ms\n", n, elapsed_ms);


    // DO RECUSRSIVE:

    // Find nearest 2 pow
    int m = n;
    if(!is_pow_two(n)){
        m=1;
        while (m < n){
            m*=2;
        }
    }

    // PAD MATS
    Matrix A_pad = pad_matrix(A, n);
    Matrix B_pad = pad_matrix(B, n);
    Matrix C_pad = allocate_zero_mat(m);


    // MAIN CALL
    start = clock();
    multiply_mat_recursive(A_pad, B_pad, C_pad, m, m, m, m);
    end = clock();

    double rec_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    // Unpad result back to n×n
    Matrix C_rec = unpad_mat(C_pad, n, m);

    printf("Recursive multiplication (n=%d padded to %d): %.3f ms\n", n, m, rec_ms);

    if (matrices_equal(C_naive, C_rec, n)) {
    printf("Validation passed: Naive and Recursive results match.\n");
    } else {
        printf("Validation failed: Results differ!\n");
    }


    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C_naive);
    freeMatrix(A_pad);
    freeMatrix(B_pad);
    freeMatrix(C_pad);
    freeMatrix(C_rec);

    return 0;
}