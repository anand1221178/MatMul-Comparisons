// Matrix utils -> allocation, printing, random number generator

#include "../include/matrix.h"
#include "time.h"
#include <stdlib.h> 
#include <stdio.h>
#include "stdbool.h"


// Just an allocater
Matrix allocateMatrix(int n){
    return (int*) malloc(n * n * sizeof(int));
}

Matrix allocate_zero_mat(int n){
    return (int*) calloc(n * n , sizeof(int));
}
// Freerer
void freeMatrix(Matrix M){
    free(M);
}

Matrix generateRandomMatrix(int n , int min, int max){
    Matrix M = allocateMatrix(n);

    for (int i = 0; i < n ;++i){
        for (int j = 0; j < n; ++j){
            M[idx(i,j,n)] = rand() % (max - min + 1) + min; //Just random stuff here no biggie
        }
    }

    return M;
}
void printMatrix(Matrix A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", A[idx(i,j,n)]);
        }
        printf("\n");
    }
    printf("\n");
}


// Recieves unpadded as M, returns padded as padded
Matrix pad_matrix(Matrix M, int n){
    // Find the nearest pow
    int m = 1;
    while (m < n){
        m *= 2;
    }

    // Allocate new mats with 0 to copy old over into
    Matrix padded = allocate_zero_mat(m);

    // copy values over
    for (int i = 0 ; i < n; i++){
        for (int j = 0 ; j < n; j++){
            padded[idx(i,j,m)] = M[idx(i,j,n)];
        }
    }

    return padded;

}


// Receives padded array as M, returns unpadded as padded
Matrix unpad_mat(Matrix M, int n, int m){
    Matrix unpad = allocate_zero_mat(n);

    for (int i =0 ; i < n; ++i){
        for (int j = 0 ; j < n; ++j){
            unpad[idx(i,j,n)] = M[idx(i,j,m)];
        }
    }

    return unpad;
}

// Validator:
bool matrices_equal(Matrix A, Matrix B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[idx(i,j,n)] != B[idx(i,j,n)]) {
                return false;  // mismatch 
            }
        }
    }
    return true;  // all good
}