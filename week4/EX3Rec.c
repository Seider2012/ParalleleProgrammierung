#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void clone(int32_t *org, int32_t *clone, int n) {
    for (int i = 0; i < n; i++) {
        clone[i] = org[i];
    }
}


void merge(int32_t *p1, int l1, int32_t *p2, int l2) {

    int32_t *temp1 = malloc(sizeof(int32_t) * l1);
    clone(p1, temp1, l1);
    int32_t *temp2 = malloc(sizeof(int32_t) * l2);
    clone(p2, temp2, l2);

    int x = 0;
    int i = 0;
    int j = 0;

    while (x < (l1 + l2)) {
        if (temp1[i] > temp2[j]) {
            p1[x] = temp2[j];
            j++;
            x++;
            if (j == l2) {
                clone(&temp1[i], &p1[x], (l1 - i));
                x += (l1 - i);
            }

        } else {
            p1[x] = temp1[i];
            i++;
            x++;

            if (i == l1) {
                x += (l2 - j);
            }
        }
    }
    free(temp1);
    free(temp2);

}



int* mergesortSeq(int *unsorted,int n) {
    if (n <= 1) {
        return unsorted;
    } else {
        int32_t *part1, *part2;
        int d = (int) (n / 2);


        part1 = mergesortSeq(unsorted, d);
        part2 = mergesortSeq(&unsorted[d], (n - d));

        merge(part1, d, part2, (n - d));
        return part1;
    }

}

int main(int argc, char **argv) {
    // handle input
    if (argc != 3) {
        fprintf(stderr, "Error: usage: %s <n> <choice> [choice=0..Seq,choice=1..Par]\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *str = argv[1];
    char *endptr;
    long n = strtol(str, &endptr, 0);
    int choice = strtol(argv[2],&endptr,10);
    if (errno != 0) {
        perror("strtol");
        return EXIT_FAILURE;
    }
    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }
    // allocate memory
    int status = EXIT_FAILURE;
    int *unsorted = malloc(sizeof(int32_t) * n);
    int *sorted = malloc(sizeof(int32_t) * n);


    status = EXIT_SUCCESS;

    // fill matrix
    srand(7);
    for (long i = 0; i < n; ++i) {
        unsorted[i] = rand()%(n);
    }
    clone(unsorted,sorted,n);
    double start_time = omp_get_wtime();


    if (choice == 0) { //Sequenziell
        mergesortSeq(sorted, n);
    }else if(choice ==1){ //Parallel
        //No Parallel Version
    }


    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",sorted[i]);
    }
    printf("%d]\n",sorted[n-1]);

    double end_time = omp_get_wtime();
    printf("time: %2.2f seconds\n",  end_time - start_time);

    // cleanup
    free(unsorted);
    free(sorted);

    return status;
}