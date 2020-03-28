//
// Created by Seider on 27.03.2020.
//
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <omp.h>


int EX2Guided(int var,int n) {


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

        printf("hadamard:Row Seq n=%d \n",n);
        /*
         printf("hadamard: Seq \n"
                "        for (i = 0; i < n; ++i) {\n"
                "            for (j = 0; j < n; ++j) {\n"
                "                c[i * n + j] = a[i * n + j] * b[i * n + j];\n"
                "            }\n"
                "        }\n"
                "\n ");
                */
    } else if (var == 1) {
        // hadamard_cols
        for (j = 0; j < n; ++j) {
            for (i = 0; i < n; ++i) {
                c[i * n + j] = a[i * n + j] * b[i * n + j];
            }
        }
        printf("hadamard:Col Seq n=%d \n",n);
        /* printf("hadamard: Seq \n"
                "            for (j = 0; j < n; ++j) {\n"
                "                for (i = 0; i < n; ++i) {\n"
                "                    c[i * n + j] = a[i * n + j] * b[i * n + j];\n"
                "                }\n"
                "            }\n"
                "\n ");*/
    } else if (var == 2) {
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
        printf("hadamard:G Row Par n=%d \n",n);
/*
        printf("hadamard: Parallel \n"
               " for (i = 0; i < n; ++i) {\n"
               "                for (j = 0; j < n; ++j) {\n"
               "                    c[i * n + j] = a[i * n + j] * b[i * n + j];\n"
               "                }\n"
               "            }\n"
               "\n ");
               */

    } else if (var == 3) {
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
        printf("hadamard:G Cols Par n=%d \n",n);

        /*
        printf("hadamard: Parallel \n"
               "            for (j = 0; j < n; ++j) {\n"
               "                for (i = 0; i < n; ++i) {\n"
               "                    c[i * n + j] = a[i * n + j] * b[i * n + j];\n"
               "                }\n"
               "            }\n"
               "\n ");
               */
    }


    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", c[i * n + j]);
        printf("\n");
    }
*/

    end = omp_get_wtime();


    printf("Work took %f sec. time.\n", end - start);


    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}




