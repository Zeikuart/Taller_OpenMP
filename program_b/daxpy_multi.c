#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Size
#define N 1000

double A = 9.0;
double X[N];
double Y[N];

void initialize_vectors() {

    int i;
    srand(time(NULL));

    for (i = 0; i < N; i++) {
        X[i] = ((double)rand() / RAND_MAX) * 100.0;
        Y[i] = ((double)rand() / RAND_MAX) * 100.0;
    }
}

void multi_thread(int times) {

    double start_time, run_time;

    // Max Threads
    int max_threads = omp_get_max_threads();
    printf("Max Threads: %d\n", max_threads);

    for (int i = 0; i < times; i++) {
        
        char filename[100];
        snprintf(filename, sizeof(filename), "program_b/results/daxpy_%02d.txt", i);

        for (int i = 1; i <= max_threads; i++) {

            // Re-init
            initialize_vectors();

            omp_set_num_threads(i);
            start_time = omp_get_wtime();

            #pragma omp parallel
            {   
                #pragma omp single
                printf("num_threads = %d ",omp_get_num_threads());

                #pragma omp for reduction(+:Y[:N])
                for (i = 0; i < N; i++) {
                    Y[i] = A * X[i] + Y[i];
                }
            }
            run_time = omp_get_wtime() - start_time;
            printf("computed in %3.15f seconds threads =  %d\n", run_time, i);

            FILE *file = fopen(filename, "a");

            if (file) {

                fprintf(file, "num_threads = %d in %3.15f seconds threads =  %d\n", i, run_time, max_threads);

                fclose(file);

                printf("Execution %d completed. Results stored in %s\n", i, filename);

            } else {
                
                printf("Error opening file %s for writing.\n", filename);
            }
        }
    }
    
}


int main(int argc, char *argv[]) {

    // Validation
    if (argc != 2) {
        printf("Usage: %s <times>\n", argv[0]);
        return 1;
    }

    // Times to run program
    int times = atoi(argv[1]);

    // Init
    initialize_vectors();

    // Multi
    multi_thread(times);

    return 0;
}