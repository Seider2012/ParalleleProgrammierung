//
// Created by Seider on 27.03.2020.
//

#include <stdio.h>
#include <omp.h>

int EX1() {
    #pragma omp parallel
    {


            printf("Hello, World! I am thread %d\n", omp_get_thread_num());

            #pragma omp single
            printf("There are %d threads\n",omp_get_max_threads());

    };
    return 0;
}
