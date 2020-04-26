
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define DOTS 100000000

int main() {
    int count = 0;
    double start;
    double end;
    start = omp_get_wtime();

    #pragma omp parallel num_threads(4) default(none) shared(count)
    {
        #pragma omp for
        for (int i = 0; i < (DOTS); i++) {
                #pragma omp atomic
                count++;
        }
    }

    printf("Count is %d \n", count);
    end = omp_get_wtime();
    printf("time= %f\n",  (end - start));


// Affinität Spread
    count = 0;
    start = omp_get_wtime();

#pragma omp parallel num_threads(4) proc_bind(spread) default(none) shared(count)
    {
#pragma omp for
        for (int i = 0; i < (DOTS); i++) {
#pragma omp atomic
            count++;
        }
    }

    printf("Count is %d (Spread)\n", count);
    end = omp_get_wtime();
    printf("time= %f\n",  (end - start));


// Affinität Close
    count = 0;
    start = omp_get_wtime();

#pragma omp parallel num_threads(4) proc_bind(close) default(none) shared(count)
    {
#pragma omp for
        for (int i = 0; i < (DOTS); i++) {
#pragma omp atomic
            count++;
        }
    }

    printf("Count is %d (Close)\n", count);
    end = omp_get_wtime();
    printf("time= %f\n", (end - start));

    // Affinität Master
    count = 0;
    start = omp_get_wtime();

#pragma omp parallel num_threads(4) proc_bind(master) default(none) shared(count)
    {
#pragma omp for
        for (int i = 0; i < (DOTS); i++) {
#pragma omp atomic
            count++;
        }
    }

    printf("Count is %d (Master)\n", count);
    end = omp_get_wtime();
    printf("time= %f\n", (end - start));

    return EXIT_SUCCESS;
}

