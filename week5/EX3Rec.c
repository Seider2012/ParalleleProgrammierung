#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define BREAK_EVEN_POINT_SORT 1000
#define BREAK_EVEN_POINT_MERGE 10000

// kopiert eine Liste
void clone(int32_t *org, int32_t *clone, int n) {
    for (int i = 0; i < n; i++) {
        clone[i] = org[i];
    }
}

// überprüft ob die listen identisch sind
int equal(const int *t1, const int *t2, int len) {
    int test = 0;
    for (int i = 0; i < len; i++) {
        if (t1[i] != t2[i]) {
            test = 1;
        };
    }
    return test;
}

// simpler comparator für builtin sort
int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

// normale version von merge für die seq. version von mergesort
void merge(int *temp, const int *p1, int l1, const int *p2, int l2) {
    int x = 0;
    int i = 0;
    int j = 0;

    while ((l1 - i) > 0 && (l2 - j) > 0) {
        if (p1[i] < p2[j]) {
            temp[x] = p1[i];
            i++;
            x++;
        } else {
            temp[x] = p2[j];
            j++;
            x++;
        }
    }
    while (l1 > i) {
        temp[x] = p1[i];
        i++;
        x++;
    }
    while (l2 > j) {
        temp[x] = p2[j];
        j++;
        x++;
    }
}

// die seq. version von mergesort
void mergeSortSeq(int *unsorted, int *sorted, int n) {
    if (n == 1) {
        sorted[0] = unsorted[0];
    } else {
        int *temp = (int *) malloc(sizeof(int) * (n));;
        int d = (n / 2);

        mergeSortSeq(unsorted, temp, d);
        mergeSortSeq(&unsorted[d], &temp[d], n - d);

        merge(sorted, temp, d, &temp[d], (n - d));
        free(temp);
    }
}

// binarySearch für die par. version von merge
int mybsearch(int key, int *base, int n) {
    if (n == 0)return 0;
    if (n == 1) {
        return key < base[0] ? 0 : 1;
    }

    int pos = n / 2;
    if (key < base[pos]) {
        return mybsearch(key, base, pos);
    } else {
        return pos + mybsearch(key, &base[pos], n - pos);
    }

}

// parallelisierte version von merge für die par. version von mergesort
void P_merge(int *temp, int *p1, int l1, int *p2, int l2) {
    if (l1 + l2 < BREAK_EVEN_POINT_MERGE) {
        return merge(temp, p1, l1, p2, l2);
    }

    if (l1 < l2) {
        P_merge(temp, p2, l2, p1, l1);
    } else if (l1 == 0) {
        return;
    } else {
        int m1 = l1 / 2;
        int m2 = mybsearch(p1[m1], p2, l2);
        temp[m1 + m2] = p1[m1];

#pragma omp task default(none) shared(temp, p1, m1, p2, m2)
        P_merge(temp, p1, m1, p2, m2);
#pragma omp task default(none) shared(temp, p1, m1, p2, m2, l1, l2)
        P_merge(&temp[m1 + m2 + 1], &p1[m1 + 1], l1 - m1 - 1, &p2[m2], l2 - m2);
#pragma omp taskwait
    }
}

//parallelisierte version von MergeSort
void mergeSortPar(int *unsorted, int *sorted, int n) {
    if (n == 1) {
        sorted[0] = unsorted[0];
    } else if (n < BREAK_EVEN_POINT_SORT) {
        mergeSortSeq(unsorted, sorted, n);
    } else {
        int *temp = (int *) malloc(sizeof(int) * (n));;
        int d = (n / 2);
        //Ausgabe:

#pragma omp task default(none) shared(temp, unsorted, n, d)
        mergeSortPar(unsorted, temp, d);
#pragma omp task default(none) shared(temp, unsorted, n, d)
        mergeSortPar(&unsorted[d], &temp[d], n - d);

#pragma omp taskwait

        P_merge(sorted, temp, d, &temp[d], (n - d));
        free(temp);
    }
}

void mergeSortIterSeq(int arr[], int n);
void mergeSortIterPar(int arr[], int n);


int main(int argc, char **argv) {

    int n = 10; // größe des arrays
    int choice = 1; // 1..seq, 2..parallel
    if (argc == 3) {
        char *p;
        choice = (int) strtol(argv[1], &p, 10);
        n = (int) strtol(argv[2], &p, 10);
    }
    int *unsorted = (int *) malloc(sizeof(int) * n);
    int *sorted = (int *) malloc(sizeof(int) * n);
    double start_time;
    double end_time;


    // fill array
    srand(12);
    for (long i = 0; i < n; ++i) {
        unsorted[i] = rand() % n;
        sorted[i] = unsorted[i];
    }

    printf("TEST 1 with n = %d: \n", n);

    /*
    printf("mergeSortPar: \n");
    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    */

    start_time = omp_get_wtime();
    //sort
    if (choice == 1) {
        mergeSortSeq(unsorted, sorted, n);
    } else if (choice == 2) {
        mergeSortPar(unsorted, sorted, n);
    } else if (choice == 3) {
        clone(unsorted,sorted,n);
        start_time = omp_get_wtime();
        mergeSortIterSeq(sorted, n);
    } else if (choice == 4) {
        clone(unsorted,sorted,n);
        start_time = omp_get_wtime();
        mergeSortIterPar(sorted, n);
    }
    end_time = omp_get_wtime();

    /*
    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",sorted[i]);
    }
    printf("%d]\n",sorted[n-1]);
    */

    printf("%s time: %2.4f seconds\n",
           choice == 1 ? "Rec Seq:" : choice == 2 ? "Rec Par:" : choice == 3 ? "Iter Seq:" : "Iter Par:",
           end_time - start_time);
    qsort(unsorted, (size_t) n, sizeof(int), compare);
    if (!equal(unsorted, sorted, n)) {
        printf("\nTEST 1 BESTANDEN!\n\n");
    } else {
        printf("\nTEST 1 NICHT BESTANDEN!\n\n");
    }

    //----------------------------------------------------

    // cleanup
    free(unsorted);
    free(sorted);

    return EXIT_SUCCESS;
}

void merge_iter(int32_t *base, int off, int l1, int l2);

// Utility function to find minimum of two integers
int min(int x, int y) { return (x < y) ? x : y; }

void mergeSortIterSeq(int arr[], int n) {
    int curr_size;  // For current size of subarrays to be merged
    int left_start; // For picking starting index of left subarray
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge_iter(arr, left_start, 1 + mid - left_start, right_end - (mid));
        }
    }
}

void mergeSortIterPar(int arr[], int n) {
    int curr_size;  // For current size of subarrays to be merged
    int left_start; // For picking starting index of left subarray
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
#pragma omp parallel for
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge_iter(arr, left_start, 1 + mid - left_start, right_end - (mid));
        }
    }
}

void merge_iter(int32_t *base, int off, int l1, int l2) {

// Falls l1=0 oder l2 = 0 ist dann muss nicht gemerged werden.
    if (!(l1 == 0 || l2 == 0)) {
        int32_t *temp1 = (int *) malloc(sizeof(int32_t) * l1);
        clone(&base[off], temp1, l1);
        int32_t *temp2 = (int *) malloc(sizeof(int32_t) * l2);
        clone(&base[off + l1], temp2, l2);
        int x = off;
        int i = 0; //für temp1
        int j = 0; //für temp2
        while (j < l2 && i < l1) {
            if (temp1[i] > temp2[j]) {
                base[x] = temp2[j];
                j++;
                x++;
            } else {
                base[x] = temp1[i];
                i++;
                x++;
            }
        }
        //Restliche
        if (i < l1) {
            clone(&temp1[i], &base[x], l1 - i);
        }
        if (j < l2) {
            clone(&temp2[j], &base[x], l2 - j);
        }
        //clean up
        free(temp1);
        free(temp2);
    }
}

