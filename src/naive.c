// Standard O(n^3) implementation
#include "../include/matrix.h"

void square_matrix_multiply(Matrix A, Matrix B, Matrix C, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0 ; j < n; j++){
            C[idx(i,j,n)] = 0;
            for(int k = 0; k < n; ++k){
                C[idx(i,j,n)] += (A[idx(i,k,n)] * B[idx(k,j,n)]);
            }
        }
    }
}