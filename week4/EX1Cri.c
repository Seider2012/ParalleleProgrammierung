
#include "EX1.h"

int EX1Cri() {
    int count = 0;
    double start;
    double end;
    start = omp_get_wtime();
    #pragma omp parallel
    {
        srand((unsigned) time(NULL) + omp_get_thread_num());
        long double x, y, z;
        #pragma omp for
        for (int i = 0; i < (DOTS); i++) {
            x = (long double) rand() / (long double) RAND_MAX;
            y = (long double) rand() / (long double) RAND_MAX;
            z = (x * x + y * y);

            if (z <= 1) {
                #pragma omp critical
                {
                    count = count + 1;
                };
            }
        }
    };

    long double pi = (4 * ((long double) count)) / DOTS;

    printf("Critical Version:\n");
    printf("PI is %Lf \n", pi);
    end = omp_get_wtime();
    printf("time= %f\n", (double) (end - start));
    return EXIT_SUCCESS;
}

