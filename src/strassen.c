// Strassen implementation O(n^2.81)

#include "../include/matrix.h"

void strassen(Matrix A, Matrix B, Matrix C, int n){
    strassen_recursive(A,B,C,n,n,n,n);
}

// main recursive call
void strassen_recursive(Matrix A, Matrix B, Matrix C, int n,int stride_A, int stride_B, int stride_C)
{
    if (n == 1) {                    // base case (scalar multiply)
        C[0] = A[0] * B[0];
        return;
    }

    int h = n/2;

    // Quadrants with pointer offsets as req
    Matrix A11 = A;
    Matrix A12 = A + h;
    Matrix A21 = A + h*stride_A;
    Matrix A22 = A + h*stride_A + h;

    Matrix B11 = B;
    Matrix B12 = B + h;
    Matrix B21 = B + h*stride_B;
    Matrix B22 = B + h*stride_B + h;

    Matrix C11 = C;
    Matrix C12 = C + h;
    Matrix C21 = C + h*stride_C;
    Matrix C22 = C + h*stride_C + h;

    // S1 to S10
    Matrix S1  = allocate_zero_mat(h);
    Matrix S2  = allocate_zero_mat(h);
    Matrix S3  = allocate_zero_mat(h);
    Matrix S4  = allocate_zero_mat(h);
    Matrix S5  = allocate_zero_mat(h);
    Matrix S6  = allocate_zero_mat(h);
    Matrix S7  = allocate_zero_mat(h);
    Matrix S8  = allocate_zero_mat(h);
    Matrix S9  = allocate_zero_mat(h);
    Matrix S10 = allocate_zero_mat(h);

    // P1 to P7
    Matrix P1 = allocate_zero_mat(h);
    Matrix P2 = allocate_zero_mat(h);
    Matrix P3 = allocate_zero_mat(h);
    Matrix P4 = allocate_zero_mat(h);
    Matrix P5 = allocate_zero_mat(h);
    Matrix P6 = allocate_zero_mat(h);
    Matrix P7 = allocate_zero_mat(h);

    // Temps
    Matrix T1 = allocate_zero_mat(h);
    Matrix T2 = allocate_zero_mat(h);

    // Assign s1 to s10
    sub_block(B12, B22, S1,  h, stride_B, stride_B, h); // S1 = B12 - B22
    add_block(A11, A12, S2,  h, stride_A, stride_A, h); // S2 = A11 + A12
    add_block(A21, A22, S3,  h, stride_A, stride_A, h); // S3 = A21 + A22
    sub_block(B21, B11, S4,  h, stride_B, stride_B, h); // S4 = B21 - B11
    add_block(A11, A22, S5,  h, stride_A, stride_A, h); // S5 = A11 + A22
    add_block(B11, B22, S6,  h, stride_B, stride_B, h); // S6 = B11 + B22
    sub_block(A12, A22, S7,  h, stride_A, stride_A, h); // S7 = A12 - A22
    add_block(B21, B22, S8,  h, stride_B, stride_B, h); // S8 = B21 + B22
    sub_block(A11, A21, S9,  h, stride_A, stride_A, h); // S9 = A11 - A21
    add_block(B11, B12, S10, h, stride_B, stride_B, h); // S10 = B11 + B12

    //All 7 products
    strassen_recursive(A11, S1,  P1, h, stride_A, h,       h); // P1 = A11*S1
    strassen_recursive(S2,  B22, P2, h, h,       stride_B, h); // P2 = S2*B22
    strassen_recursive(S3,  B11, P3, h, h,       stride_B, h); // P3 = S3*B11
    strassen_recursive(A22, S4,  P4, h, stride_A, h,       h); // P4 = A22*S4
    strassen_recursive(S5,  S6,  P5, h, h,       h,       h); // P5 = S5*S6
    strassen_recursive(S7,  S8,  P6, h, h,       h,       h); // P6 = S7*S8
    strassen_recursive(S9,  S10, P7, h, h,       h,       h); // P7 = S9*S10

    
    // C11 = P5 + P4 - P2 + P6
    add_block(P5, P4, T1,  h, h, h, h);
    sub_block(T1, P2, T2,  h, h, h, h);
    add_block(T2, P6, C11, h, h, h, stride_C);

    // C12 = P1 + P2
    add_block(P1, P2, C12, h, h, h, stride_C);

    // C21 = P3 + P4
    add_block(P3, P4, C21, h, h, h, stride_C);

    // C22 = P5 + P1 - P3 - P7
    add_block(P5, P1, T1,  h, h, h, h);
    sub_block(T1, P3, T2,  h, h, h, h);
    sub_block(T2, P7, C22, h, h, h, stride_C);

    // free temps
    freeMatrix(S1); 
    freeMatrix(S2);
    freeMatrix(S3);
    freeMatrix(S4);
    freeMatrix(S5);
    freeMatrix(S6); 
    freeMatrix(S7);
    freeMatrix(S8);
    freeMatrix(S9);
    freeMatrix(S10);
    freeMatrix(P1);
    freeMatrix(P2); 
    freeMatrix(P3); 
    freeMatrix(P4);
    freeMatrix(P5);
    freeMatrix(P6);
    freeMatrix(P7);
    freeMatrix(T1); 
    freeMatrix(T2);
}