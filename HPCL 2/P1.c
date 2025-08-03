#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
    int n = 100000000; 
    float scalar = 2.5;
    float *A = malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        A[i] = i * 1.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++) {
        A[i] += scalar;
    }

    double end = omp_get_wtime();

    printf("Time taken: %f seconds\n", end - start);

    free(A);
    return 0;
}
