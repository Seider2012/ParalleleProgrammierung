
#include "EX1.h"




int EX1Red() {
    int count = 0;
    clock_t begin = clock();
    #pragma omp parallel
    {
        srand((unsigned) time(NULL) + omp_get_thread_num());
        long double x, y, z;
        #pragma omp for reduction(+:count)
        for (int i = 0; i < (DOTS); i++) {
            x = (long double) rand() / (long double) RAND_MAX;
            y = (long double) rand() / (long double) RAND_MAX;
            z = (x * x + y * y);

            if (z <= 1) {
                count=count +1;
            }
        }
    };

    long double pi = (4 * ((long double) count)) / DOTS;

    printf("Reduction Version:\n");
    printf("PI is %Lf \n", pi);
    clock_t end = clock();
    printf("time= %f\n", (double) (end - begin) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

