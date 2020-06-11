
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//#define N 1000

int main(int argc, void **argv) {
    int repetitions = 1000000;
    int N = 1000;
    if (argc == 2) {
        char **p;
        N = (int) strtol(argv[1], p, 10);

    }
    double start, end;
    double *a = (double *)aligned_alloc(64, sizeof(double)*N);
    double *b = (double *)aligned_alloc(64, sizeof(double)*N);
    double *c = (double *)aligned_alloc(64, sizeof(double)*N);
    double c1, c2, c3;
    c1 = 0;
    c2 = 1;
    c3 = 2;
    for (int i = 0; i < N; ++i) {
        a[i] = c1;
        b[i] = c2;
        c[i] = c3;
    }
    start = omp_get_wtime();
#pragma omp simd aligned(a, b, c:64)
    for (int run = 0; run < repetitions; ++run) {
        for (int i = 0; i < N; ++i) {
            a[i] += b[i] * c[i];
        }
    }
    end = omp_get_wtime();
    int correctness = 1;
    for (int i = 0; i < N; ++i) {
        //printf("%f = %f * %f\n",a[i],b[i],c[i]);
        if (a[i] == N * c2 * c3) {
            correctness = 0;
        }
    }

    printf("%s, N= %d, time = %f s\n", correctness ? "SUCCESS" : "FAILURE", N, end - start);
}