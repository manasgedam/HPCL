#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Comparison functions for qsort
int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n = 1000000;
    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));
    long long result = 0;

    // Initialize vectors with some values
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Sort A ascending, B descending
    qsort(A, n, sizeof(int), compare_asc);
    qsort(B, n, sizeof(int), compare_desc);

    double start = omp_get_wtime();

    // Parallel dot product using reduction
    #pragma omp parallel for reduction(+:result) num_threads(4)
    for (int i = 0; i < n; i++) {
        result += (long long)A[i] * B[i];
    }

    double end = omp_get_wtime();

    printf("Minimum Scalar Product: %lld\n", result);
    printf("Time Taken: %f seconds\n", end - start);

    free(A);
    free(B);
    return 0;
}
