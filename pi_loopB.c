#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
static double reference_pi = 3.14159265358979;
double step;
int main () {
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    int max_threads = omp_get_max_threads();

    step = 1.0/(double) num_steps;
    for (i = 1; i <= max_threads; i++) {
        sum = 0.0;
        omp_set_num_threads(i);
    	start_time = omp_get_wtime();
        #pragma omp parallel  
        {
            #pragma omp single
            printf("num_threads = %d ",omp_get_num_threads());

            #pragma omp for reduction(+:sum) private(x)
            for (i=1; i<= num_steps; i++) {
                x = (i-0.5)*step;
                sum = sum + 4.0/(1.0+x*x);
            }
        }
        pi = step * sum;
        run_time = omp_get_wtime() - start_time;
        printf("computed pi = %3.15f in %3.15f seconds threads =  %d %% error = %3.15f\n", pi, run_time, i, (pi - reference_pi)*100.0/reference_pi);
    }
}






