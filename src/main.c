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

    // Add check for non powers to pad mats

    printf("Matrix size = %d\n", n);

    srand(time(NULL));


    // Alllocate matrix random for A and B, C is just space

    Matrix A = generateRandomMatrix(n,1,10);
    Matrix B = generateRandomMatrix(n,1,10);
    Matrix C = allocateMatrix(n);

    // Do naive
    clock_t start = clock();
    square_matrix_multiply(A,B,C,n);
    clock_t end = clock();

    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("Naive multiplication (n=%d): %.3f ms\n", n, elapsed_ms);


    if (n <= 4) { // small temp check
        printf("Matrix A:\n");
        printMatrix(A, n);
        printf("Matrix B:\n"); 
        printMatrix(B, n);
        printf("Matrix C = A * B:\n"); 
        printMatrix(C, n);
    }

    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    return 0;
}