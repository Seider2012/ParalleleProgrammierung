//
// Created by Seider on 27.03.2020.
//
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <omp.h>


int EX2Static(int var,int n) {


    int32_t *a = (int *) malloc(sizeof(int32_t) * n * n);
    int32_t *b = (int *) malloc(sizeof(int32_t) * n * n);
    int32_t *c = (int *) malloc(sizeof(int32_t) * n * n);

    double start;
    double end;
    start = omp_get_wtime();

    int i, j;

    /*
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            a[i*n+j] =  1;
            b[i*n+j]= 2;
        }
    }
     */



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
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", c[i * n + j]);
        printf("\n");
    }
*/

    end = omp_get_wtime();

    if(var==0)
        printf("hadamard:Row Seq n=%d \n"
               "Work took %f sec. time.\n",n,end - start);
    else if(var==1)
        printf("hadamard:Col Seq n=%d \n"
               "Work took %f sec. time.\n",n,end - start);
    else if(var==2)
        printf("hadamard:S Row Par n=%d \n"
               "Work took %f sec. time.\n",n,end - start);
    else if(var==3)
        printf("hadamard:S Cols Par n=%d \n"
               "Work took %f sec. time.\n",n,end - start);


    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}




