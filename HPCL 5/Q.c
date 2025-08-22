#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 100; 
    int i, j, k;

    // 'static' prevents stack overflow for large arrays
    static double A[100][100], B[100][100], C[100][100];
    static double x[100], y[100];
    double scalar = 2.5;

    // 1
    printf("1. Running Matrix-Matrix Multiplication...\n");

    #pragma omp parallel for private(i, j, k) // Each thread takes a set of rows
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printf("   ...Done.\n\n");

    // 2
    printf("2. Running Matrix-Scalar Multiplication...\n");

    #pragma omp parallel for private(i, j)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            B[i][j] = scalar * A[i][j];
        }
    }
    printf("   ...Done.\n\n");

    // 3
    printf("3. Running Matrix-Vector Multiplication...\n");

    #pragma omp parallel for private(i, j) // Each thread takes a set of rows
    for (i = 0; i < n; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    printf("   ...Done.\n\n");

//    4
    printf("4. Running Parallel Prefix Sum...\n");
    int size = 10000;
    int* in_arr = (int*)malloc(size * sizeof(int));
    int* out_arr = (int*)malloc(size * sizeof(int));

    for(i = 0; i < size; i++) in_arr[i] = 1; // Initialize array

    for (int d = 1; d < size; d *= 2) {
        #pragma omp parallel for private(i) 
        for (i = d; i < size; i++) {
            out_arr[i] = in_arr[i] + in_arr[i - d];
        }
        #pragma omp parallel for private(i) 
        for (i = d; i < size; i++) {
            in_arr[i] = out_arr[i];
        }
    }
    printf("   ...Done.\n\n");
    
    free(in_arr);
    free(out_arr);

    return 0;
}