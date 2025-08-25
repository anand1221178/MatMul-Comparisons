// HEADER FILE - DECLARATIONS
#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// Setup alias for readability
typedef int* Matrix;

// Allocation : 
Matrix allocateMatrix(int n);
Matrix allocate_zero_mat(int n);
void freeMatrix(Matrix M);

// IDX HELPER SINCE WE ARE USING 1D for best cache performance!
inline int idx(int i, int j, int n) {return i*n + j;}

// Utils
Matrix generateRandomMatrix(int n, int minVal, int maxVal);

void printMatrix(Matrix A, int n);
bool matrices_equal(Matrix A, Matrix B, int n);

// Actual functions:
void square_matrix_multiply(Matrix A, Matrix B, Matrix C, int n);
void multiply_mat_recursive(Matrix A, Matrix B, Matrix C, int n, int stride_A, int stride_b, int stride_C);

// Padding functions
Matrix pad_matrix(Matrix M, int n);
Matrix unpad_mat(Matrix M, int n, int m);


// Check power of 2
inline int is_pow_two(int n){
    return(n>0) && ((n & (n-1)) == 0);
}

// All for strassen now
void add_block(Matrix A, Matrix B, Matrix C, int n, int stride_A, int stride_B, int stride_C); //C = A + B
void sub_block(Matrix A, Matrix B, Matrix C, int n, int stride_A, int stride_B, int stride_C); //C = A + B

//Just a wrappr for main call
void strassen(Matrix A, Matrix B, Matrix C, int n);
void strassen_recursive(Matrix A, Matrix B, Matrix C, int n, int stride_A, int stride_B, int stride_C);

#endif