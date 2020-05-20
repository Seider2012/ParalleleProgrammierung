#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {

    double start_time;
    double end_time;
    size_t n = 4;
    char *p;

    if (argc == 2) {
        n = (size_t) strtol(argv[1], &p, 10);
    }
/*
    double *x = (double*)malloc(n*sizeof(double));
    double *y = (double*)malloc(n*sizeof(double));


    double factor = 1;
    start_time = omp_get_wtime();
    for (int i=0; i < n; i++) {
        x[i] = factor * y[i];
        factor = factor / 2;
    }
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

    factor = 1;
    start_time = omp_get_wtime();
#pragma omp parallel for schedule(guided)
    for (int i=0; i < n; i++) {
        x[i] = (factor/pow(2,i)) * y[i];
    }
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

    free(x);
    free(y);
    */
/*
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    double *z = (double *) malloc(n * sizeof(double));

    start_time = omp_get_wtime();
    for (int i = 1; i < n; i++) {
        x[i] = (x[i] + y[i - 1]) / 2;
        y[i] = y[i] + z[i] * 3;
    }
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

    start_time = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for
           for (int i = 1; i < n; i++) {
              y[i] = y[i] + z[i] * 3;
           }
#pragma omp for
            for (int i = 1; i < n; i++) {
               x[i] = (x[i] + y[i - 1]) / 2;
            }
    };
end_time = omp_get_wtime();
printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

free(x);
free(y);
free(z);
 */
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    int twice = 1;
    start_time = omp_get_wtime();
    x[0] = x[0] + 5 * y[0];
    for (int i = 1; i<n; i++) {
        x[i] = x[i] + 5 * y[i];
        if ( twice ) {
            x[i-1] = 2 * x[i-1];
        }
    }
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

    start_time = omp_get_wtime();
    x[0] = x[0] + 5 * y[0];
#pragma omp parallel
    {
#pragma omp for
        for (int i = 1; i<n; i++) {
            x[i] = x[i] + 5 * y[i];
        }
        if ( twice ) {
#pragma omp for
            for (int i = 1; i<n; i++) {
                x[i-1] = 2 * x[i-1];
            }
        }

    };
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, size %d\n", end_time - start_time, n, n);

    free(x);
    free(y);

return EXIT_SUCCESS;
}


