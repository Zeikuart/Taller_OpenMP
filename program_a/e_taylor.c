#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static double reference_e = 2.718281828459045;

int main(int argc, char *argv[]) {

    // Validation
    if (argc != 2) {
        printf("Usage: %s <times>\n", argv[0]);
        return 1;
    }
    // Times to run program
    int times = atoi(argv[1]);
    
    // Approximations
    int n = 100;

    long double e = 1.0;
    long double factorial = 1.0;
    double start_time, run_time;

    // Max Thraeds
    int max_threads = omp_get_max_threads();
    printf("Max Threads: %d\n", max_threads);

    for (int i = 0; i < times; i++) {
        
        char filename[100];
        snprintf(filename, sizeof(filename), "program_a/results/e_taylor_%02d.txt", i);

        for (int k = 1; k <= max_threads; k++) {

            omp_set_num_threads(k);
            e = 1.0;

            // Set Threads
            start_time = omp_get_wtime();

            #pragma omp parallel
            {
                #pragma omp single
                printf("num_threads = %d ",omp_get_num_threads());

                #pragma omp for reduction(+:e) private(factorial)
                for (int i = 1; i <= n; i++) {
                    factorial = 1.0;
                    
                    for (int j = 1; j <= i; j++) {
                        factorial *= j;
                    }
                    e += 1.0 / factorial;
                }
            }

            run_time = omp_get_wtime() - start_time;
            printf("computed e = %3.15Lf in %3.15f seconds threads =  %d %% error = %3.15Lf\n", e, run_time, k, (e - reference_e)*100.0/reference_e);

            FILE *file = fopen(filename, "a");

            if (file) {

                fprintf(file, "num_threads = %d computed e = %3.15Lf in %3.15f seconds threads =  %d %% error = %3.15Lf\n",k, e, run_time, max_threads, (e - reference_e)*100.0/reference_e);

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

