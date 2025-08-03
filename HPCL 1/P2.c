#include <stdio.h>
#include <omp.h>

int main() {
    int n_threads;

    printf("Enter number of threads: ");
    scanf("%d", &n_threads);

    printf("\nSequential Hello, World:\n");
    for (int i = 0; i < n_threads; i++) {
        printf("Hello, World from iteration %d (sequential)\n", i);
    }

    omp_set_num_threads(n_threads);

    printf("\nParallel Hello, World:\n");

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello, World from thread %d (parallel)\n", tid);
    }

    return 0;
}
