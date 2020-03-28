
//
// Created by Seider on 27.03.2020.
//
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <omp.h>


int EX2(int var, int n) {


    int32_t *a = (int *) malloc(sizeof(int32_t) * n * n);
    int32_t *b = (int *) malloc(sizeof(int32_t) * n * n);
    int32_t *c = (int *) malloc(sizeof(int32_t) * n * n);

    double start;
    double end;
    start = omp_get_wtime();

    int i, j;

    if (var == 0) {
        // hadamard_rows
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                c[i * n + j] = a[i * n + j] * b[i * n + j];
            }
        }
    } else if (var == 1) {
        // hadamard_cols
        for (j = 0; j < n; ++j) {
            for (i = 0; i < n; ++i) {
                c[i * n + j] = a[i * n + j] * b[i * n + j];
            }
        }
    } else if (var == 2) {
        // hadamard_rows
#pragma omp parallel private(j)
        {
#pragma omp for schedule(static)
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }
    } else if (var == 3) {
        // hadamard_cols
#pragma omp parallel private(i)
        {
#pragma omp for schedule(static)
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }

        /*
        printf("hadamard: Parallel \n"
               "            for (j = 0; j < n; ++j) {\n"
               "                for (i = 0; i < n; ++i) {\n"
               "                    c[i * n + j] = a[i * n + j] * b[i * n + j];\n"
               "                }\n"
               "            }\n"
               "\n ");
               */
    } else if (var == 4) {
        // hadamard_rows
#pragma omp parallel private(j)
        {
#pragma omp for schedule(dynamic, 4)
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }
    } else if (var == 5) {
        // hadamard_cols
#pragma omp parallel private(i)
        {
#pragma omp for schedule(dynamic, 4)
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }
    } else if (var == 6) {
// hadamard_rows
#pragma omp parallel private(j)
        {
#pragma omp for schedule(guided)
            for (i = 0; i < n; ++i) {
                for (j = 0; j < n; ++j) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }
    } else if (var == 7) {
// hadamard_cols
#pragma omp parallel private(i)
        {
#pragma omp for schedule(guided)
            for (j = 0; j < n; ++j) {
                for (i = 0; i < n; ++i) {
                    c[i * n + j] = a[i * n + j] * b[i * n + j];
                }
            }
        }
    }


    end = omp_get_wtime();

    if (var == 0)
        printf("hadamard:Row Seq n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 1)
        printf("hadamard:Col Seq n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 2)
        printf("hadamard:S Row Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 3)
        printf("hadamard:S Cols Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 4)
        printf("hadamard:D Row Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 5)
        printf("hadamard:D Cols Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 6)
        printf("hadamard:G Row Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);
    else if (var == 7)
        printf("hadamard:G Cols Par n=%d \n"
               "Work took %f sec. time.\n", n, end - start);

    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}




