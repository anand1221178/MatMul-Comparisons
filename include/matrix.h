// HEADER FILE - DECLARATIONS
#ifndef MATRIX_H
#define MATRIX_H

// Setup alias for readability
typedef int* Matrix;

// Allocation : TODO: 
Matrix allocateMatrix(int n);
void freeMatrix(Matrix M);

// IDX HELPER SINCE WE ARE USING 1D for best cache performance!
inline int idx(int i, int j, int n) {return i*n + j;}

// Utils
Matrix generateRandomMatrix(int n, int minVal, int maxVal);






#endif