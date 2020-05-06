#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int32_t *calSeqPrefixSums(const int32_t *array, size_t size) {
    int32_t *result = malloc(sizeof(int32_t) * size);

    result[0] = 0;
    for (int i = 1; i < size; i++) {
        result[i] = result[i - 1] + array[i - 1];
    }


    return result;
}

int32_t *calParTaskPrefixSums(const int32_t *array, size_t size) {
    int32_t *result = malloc(sizeof(int32_t) * size);

#pragma omp parallel shared(result,array,size)
#pragma omp single
    {

#pragma omp task depend(out:result[0])
    {
        result[0] = 0;
    }
    for (int i = 1; i < size; i++) {
#pragma omp task depend(in:result[i-1]) depend(out:result[i])
        {
            result[i] = result[i - 1] + array[i - 1];
        }
    }

#pragma omp taskwait
    }
    return result;
}

int32_t *calParCheatPrefixSums(const int32_t *array, size_t size) {
    int32_t result =0;
#pragma omp parallel for reduction(+:result)
        for (int i = 1; i < size; i++) {
                result+= array[i-1];
        }
    return result;
}

int main(int argc, char *argv[]) {

    double start_time;
    double end_time;
    size_t n = 5;
    char *p;

    if (argc == 2) {
        n = (size_t) strtol(argv[1], &p, 10);
    }

    int32_t *array = malloc(sizeof(int32_t) * n);
    int32_t *prefixSums;

    // fill array
    //srand(12);
    for (long i = 0; i < n; ++i) {
        //array[i] = rand() % (n*10);
        array[i] = 1;
    }

    start_time = omp_get_wtime();
    prefixSums = calSeqPrefixSums(array, n);
    end_time = omp_get_wtime();
    printf("Seq. time: %2.4f seconds, last value: %d\n", end_time - start_time, prefixSums[n - 1]);
    //clean up
    free(prefixSums);


    start_time = omp_get_wtime();
    prefixSums = calParTaskPrefixSums(array, n);
    end_time = omp_get_wtime();

    printf("Parallel Task time: %2.4f seconds, last value: %d\n", end_time - start_time, prefixSums[n - 1]);
    free(prefixSums);

    start_time = omp_get_wtime();
    int sum = calParCheatPrefixSums(array, n);
    end_time = omp_get_wtime();

    printf("Parallel Task time: %2.4f seconds, last value: %d\n", end_time - start_time, sum);

    //clean up
    free(array);

    return EXIT_SUCCESS;
}
