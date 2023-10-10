#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Size
#define N 1000000

double A = 2.0;
double X[N];
double Y[N];

void initialize_vectors() {

    int i;
    srand(time(NULL));

    for (i = 0; i < N; i++) {
        X[i] = ((double)rand() / RAND_MAX);
        Y[i] = ((double)rand() / RAND_MAX);
    }
}

void single_thread() {

    int i;

    for (i = 0; i < N; i++) {
        Y[i] = A * X[i] + Y[i];
    }
}

int main() {

    // Init
    initialize_vectors();

    double start_time, run_time;

    // Single
    start_time = omp_get_wtime();
    single_thread();
    run_time = omp_get_wtime() - start_time;
    printf("Tiempo para un solo subproceso: %f segundos\n", run_time);

    return 0;
}