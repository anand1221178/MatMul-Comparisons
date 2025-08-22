// Recursive O(n^3) implementation
#include "../include/matrix.h"


// TODO : EXPLAIN THIS RECURSION AND PTR MATH IN REPORT
void multiply_mat_recursive(Matrix A, Matrix B, Matrix C,int n, int stride_a, int stride_b, int stride_c){
    // Recursive end base case
    if (n ==1){
        C[0] += A[0] * B[0];
        return; //exit recursion trace
    }

    // MPT
    int half = n/2;


    // SPLIT A into 4 blocks
    // TOP LEFT:
    Matrix A11 = A; //since using 1D we just point to the first element, also since we are using pointer arithmetic we just point here, no copy

    // TOP RIGHT:
    Matrix A12 = A + half; //shift pointer half of cols not rows!
    
    // Bottom left first pointer:
    Matrix A21 = A + half * stride_a; //moves ptr down half rows * stride usually (n -> size of row) so how much down and accross

    // BOTTOM RIGHT:
    Matrix A22 = A + half * stride_a + half; //moves down half of the rows then half of the cols


    // SPLIT B the same way as above
    Matrix B11 = B;
    Matrix B12 = B + half;
    Matrix B21 = B + half * stride_b;
    Matrix B22 = B + half * stride_b + half;

    // SPLIT C THE SAME WAY
    Matrix C11 = C;
    Matrix C12 = C + half;
    Matrix C21 = C + half * stride_c;
    Matrix C22 = C + half * stride_c + half;


    // CALL RESURSION
    // C11 = A11*B11 + A12*B21
    multiply_mat_recursive(A11, B11, C11, half, stride_a, stride_b, stride_c);
    multiply_mat_recursive(A12, B21, C11, half,stride_a,stride_b,stride_c);

    // C12 = A11*B12 + A12*B22
    multiply_mat_recursive(A11, B12, C12, half, stride_a, stride_b, stride_c);
    multiply_mat_recursive(A12, B22, C12, half, stride_a, stride_b, stride_c);

    // C21 = A21*B11 + A22*B21
    multiply_mat_recursive(A21, B11, C21, half, stride_a, stride_b, stride_c);
    multiply_mat_recursive(A22, B21, C21, half, stride_a, stride_b, stride_c);

    // C22 = A21*B12 + A22*B22
    multiply_mat_recursive(A21, B12, C22, half, stride_a, stride_b, stride_c);
    multiply_mat_recursive(A22, B22, C22, half, stride_a, stride_b, stride_c);

}