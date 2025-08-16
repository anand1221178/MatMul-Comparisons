// MAIN DRIVER FILE -> benchmarking and data output
#include "stdio.h"
#include "stdlib.h" //for atoi
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

    Matrix A = generateRandomMatrix(n,1,10);
    Matrix B = generateRandomMatrix(n,1,10);
    Matrix C = generateRandomMatrix(n,1,10);
    
    return 0;
}