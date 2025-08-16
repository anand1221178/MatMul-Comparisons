// Matrix utils -> allocation, printing, random number generator

#include "../include/matrix.h"
#include "time.h"


// Just an allocater
Matrix allocateMatrix(int n){
    return (int*) malloc(n *n * sizeof(int));
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