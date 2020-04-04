#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// simples kopieren
void clone(int32_t *org, int32_t *clone, int n) {
    for (int i = 0; i < n; i++) {
        clone[i] = org[i];
    }
}

// überprüft ob die listen identisch sind
int equal(int32_t *t1,int32_t *t2,int len){
    int test=0;
    for (int i = 0; i < len; i++) {
        if(t1[i] != t2[i]){
            test=1;
        };
    }
    return test;
}

int compare(const void *a, const void *b){
    return( *(int*)a-*(int*)b);
}

void merge(int32_t *p1, int off,int l1, int l2);

void mergeSort(int arr[], int n);

int main(int argc, char **argv) {



    double start_time = omp_get_wtime();
    int n = 5;
    int *unsorted;
    unsorted = (int*)malloc(sizeof(int32_t) * n);
    int *sorted;
    sorted = (int*)malloc(sizeof(int32_t) * n);

    printf("TEST 1: \n");
    printf("SeqMergeSort: \n");
    unsorted[0]=2;
    unsorted[1]=3;
    unsorted[2]=1;
    unsorted[3]=9;
    unsorted[4]=2;
    sorted[0]=1;
    sorted[1]=2;
    sorted[2]=2;
    sorted[3]=3;
    sorted[4]=9;



    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    //sort
    mergeSort(unsorted, n);

    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    double end_time = omp_get_wtime();
    printf("time: %2.2f seconds\n",  end_time - start_time);
    if(!equal(unsorted,sorted,n)){
        printf("\nTEST 1 BESTANDEN!\n\n");
    } else{
        printf("\nTEST 1 NICHT BESTANDEN!\n\n");
    }





    start_time = omp_get_wtime();
    printf("TEST 2: \n");
    printf("SeqMergeSort: \n");
    unsorted[0]=11;
    unsorted[1]=3;
    unsorted[2]=-5;
    unsorted[3]=1;
    unsorted[4]=1;
    sorted[0]=-5;
    sorted[1]=1;
    sorted[2]=1;
    sorted[3]=3;
    sorted[4]=11;



    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    //sort
    mergeSort(unsorted, n);

    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    end_time = omp_get_wtime();
    printf("time: %2.2f seconds\n",  end_time - start_time);
    if(!equal(unsorted,sorted,n)){
        printf("\nTEST 2 BESTANDEN!\n\n");
    } else{
        printf("\nTEST 2 NICHT BESTANDEN!\n\n");
    }
    // cleanup

    //----------------------------------------------------
    // Bei Test 3 kann man die Länge als Variable mitgeben.

    if(argc==2){
        free(unsorted);
        free(sorted);
        char *p;
        n= strtol(argv[1],&p,10);
        unsorted = (int*)malloc(sizeof(int32_t) * n);
        sorted = (int*)malloc(sizeof(int32_t) * n);
    }

    // fill array
    srand(7);
    for (long i = 0; i < n; ++i) {
        unsorted[i] = rand()%n;
        sorted[i] = unsorted[i];
    }


    printf("TEST 3 with n = %d: \n",n);
    printf("SeqMergeSort: \n");

    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    start_time = omp_get_wtime();
    //sort
    mergeSort(unsorted, n);
    end_time = omp_get_wtime();

    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);

    printf("time: %2.4f seconds\n",  end_time - start_time);
    qsort(sorted,n,sizeof(int32_t),compare);
    if(!equal(unsorted,sorted,n)){
        printf("\nTEST 3 BESTANDEN!\n\n");
    } else{
        printf("\nTEST 3 NICHT BESTANDEN!\n\n");
    }

    //----------------------------------------------------

    // cleanup
    free(unsorted);
    free(sorted);

    return EXIT_SUCCESS;
}



void merge(int32_t *p1, int off,int l1, int l2) {


// Falls l1=0 oder l2 = 0 ist dann muss nicht gemerged werden.
    if(!(l1==0||l2==0)){
        int32_t *temp1 = (int*) malloc(sizeof(int32_t) * l1);
        clone(&p1[off], temp1, l1);
        int32_t *temp2 = (int*)malloc(sizeof(int32_t) * l2);
        clone(&p1[off+l1], temp2, l2);

        int x = off;
        int i = 0; //für temp1
        int j = 0; //für temp2

        while (j <l2&&i < l1) {
            if (temp1[i] > temp2[j]) {
                p1[x] = temp2[j];
                j++;
                x++;
            } else {
                p1[x] = temp1[i];
                i++;
                x++;
            }
        }

        //Restliche
        if (i < l1)
        {
            clone(&temp1[i], &p1[x], l1-i);
        }
        if (j < l2)
        {
            clone(&temp2[j], &p1[x], l2-j);
        }
        //clean up
        free(temp1);
        free(temp2);
    }
}
/*________________________________________________________________________________________________________________________________________________________________________________________
 * Die Idee/Code basiert auf die iterative Version von Mergesort auf der Webseite:
 *  https://www.geeksforgeeks.org/iterative-merge-sort/
 *
 *  Die Idee ist sich die Zerlegung nur vorzustellen. Wir bekommen eine Liste mit einer Größe von n.
 *  Bei dieser Größe würden n-Subarraies mit der Größe 1 existieren. (Deswegen:curr_size beginnt mit 1)
 * Diese Subarraies müsste jeweils alle erfasst werden und gemerged. (siehe innere for-Schleife). Die Erfassung erfolgt mit "mid" und "right_end".
 * Nach den Merge werden nun die neuen Subarraies erfasst. Die neuen sollten jetzt die 2-fache Größe haben.(Deswegen:cur_size=2*cur_size)
 * Der Vorgang wird wiederholt bis die cur_size gleich n oder größer ist.
 *
 * Somit wurde der Array sortiert.
 *_________________________________________________________________________________________________________________________________________________________________________________________
 */
// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }
/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
    int curr_size;  // For current size of subarrays to be merged
    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
    // to be merged

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
    {
        // Pick starting point of different subarrays of current size
#pragma omp parallel for
        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = min(left_start + curr_size - 1, n-1);

            int right_end = min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(arr, left_start, 1+mid-left_start, right_end-(mid));
        }
    }
}