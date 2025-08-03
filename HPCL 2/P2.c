#include <stdio.h>
#include <omp.h>

int main() {
    int num_steps = 100000000;
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum) num_threads(4)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = sum * step;
    double end = omp_get_wtime();

    printf("Calculated Pi: %.15f\n", pi);
    printf("Time taken: %f seconds\n", end - start);
    return 0;
}
