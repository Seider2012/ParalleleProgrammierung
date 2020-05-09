#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMUM_REMAINING_ROWS 8

int no_attack(int x1, int y1, int x2, int y2) {
    if (x1 == x2)
        return 0;
    if (y1 == y2)
        return 0;
    if (x1 - y1 == x2 - y2)
        return 0;
    if (x1 + y1 == x2 + y2)
        return 0;
    return 1;
}

int conflict(int *queens, int pos) {
    for (int i = 0; i < pos; i += 2) {
        for (int j = i + 2; j < pos; j += 2) {
            if (!no_attack(queens[i], queens[i + 1], queens[j], queens[j + 1]))
                return 1;
        }
    }
    return 0;
}

int calSeqSol(int pos_row, size_t n, int queens[n * 2]) {
    if (pos_row == n) {
        return 1;
    } else {
        int sols = 0;

        for (int i = 0; i < n; i++) {
            queens[pos_row * 2] = pos_row;
            queens[pos_row * 2 + 1] = i;
            if (!conflict(queens, pos_row * 2 + 2))
                sols += calSeqSol(pos_row + 1, n, queens);
            // local_queens[pos_row*2]=0;
            //local_queens[pos_row*2+1]=0;
        }

        return sols;
    }
}


int calParSol(int pos_row, size_t n,int queens[n * 2]) {
    if (pos_row == n) {
        return 1;
    } else {
        int sols = 0;
        for (int i = 0; i < n; i++) {
            queens[pos_row * 2] = pos_row;
            queens[pos_row * 2 + 1] = i;
            if (!conflict(queens, pos_row * 2 + 2)) {
                int *local= malloc(sizeof(int)*2*n);
                local=memcpy(local,queens,n*2*sizeof(int));
                if(n-pos_row<MINIMUM_REMAINING_ROWS)
#pragma omp atomic
                    sols += calSeqSol(pos_row + 1, n, local);
                else{
#pragma omp task shared(local,n,pos_row,sols)
                {
                    int found;
                    found = calParSol(pos_row + 1, n, local);
#pragma omp atomic
                    sols += found;
                };
                }
            }
        }
#pragma omp taskwait
    free(queens);
        return sols;
    }
}

int main(int argc, char *argv[]) {

    double start_time;
    double end_time;
    size_t n = 4;
    char *p;

    if (argc == 2) {
        n = (size_t) strtol(argv[1], &p, 10);
    }

    int solutions = 0;
    int *queens = malloc(sizeof(int) * n * 2);

    start_time = omp_get_wtime();
    solutions = calSeqSol(0, n, queens);
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, found solutions: %d for size %dX%d\n", end_time - start_time, solutions, n, n);

    solutions = 0;
    start_time = omp_get_wtime();
#pragma omp parallel shared(solutions, n, queens)
#pragma omp single
    {
        solutions = calParSol(0, n, queens);
    }
    end_time = omp_get_wtime();
    printf("time: %2.4f seconds, found solutions: %d for size %dX%d\n", end_time - start_time, solutions, n, n);


    //clean up
    free(queens);

    return EXIT_SUCCESS;
}
