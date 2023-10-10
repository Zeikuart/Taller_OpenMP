#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
static long num_steps = 100000000;
static double reference_pi = 3.14159265358979;
double step;

int main (int argc, char *argv[]) {

    // Validation
    if (argc != 2) {
        printf("Usage: %s <times>\n", argv[0]);
        return 1;
    }

    // Times to run program
    int times = atoi(argv[1]);

    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0/(double) num_steps;

    // Max Thraeds
    int max_threads = omp_get_max_threads();
    printf("Max Threads: %d\n", max_threads);
    
    for (int i = 0; i < times; i++) {

        char filename[100];
        snprintf(filename, sizeof(filename), "results/pi_loop_%02d.txt", i);

        for (int i = 1; i <= max_threads; i++) {

            sum = 0.0;

            // Set Threads
            omp_set_num_threads(i);

            // Starting Time
            start_time = omp_get_wtime();

            #pragma omp parallel
            {
                #pragma omp single
                printf("num_threads = %d ",omp_get_num_threads());
            
                #pragma omp for reduction(+:sum) private(x)
                for (int i = 1; i <= num_steps; i++) {
                    x = (i - 0.5) * step;
                    sum = sum + 4.0 / (1.0 + x * x);
                }
            }

            pi = step * sum;
            run_time = omp_get_wtime() - start_time;
            printf("computed pi = %3.15f in %3.15f seconds threads =  %d %% error = %3.15f\n", pi, run_time, i, (pi - reference_pi)*100.0/reference_pi);

            FILE *file = fopen(filename, "a");

            if (file) {

                fprintf(file, "num_threads = %d computed pi = %3.15f in %3.15f seconds threads =  %d %% error = %3.15f\n",i, pi, run_time, max_threads, (pi - reference_pi)*100.0/reference_pi);

                fclose(file);

                printf("Execution %d completed. Results stored in %s\n", i, filename);

            } else {
                
                printf("Error opening file %s for writing.\n", filename);
            }
        }
    }
    
    printf("Finished!\n");
    return 0;

}