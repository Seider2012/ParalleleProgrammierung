#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

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

void merge(int32_t *temp,int32_t *p1, int l1, int32_t *p2, int l2) {
    int x = 0;
    int i = 0;
    int j = 0;

    while ((l1-i)>0&&(l2-j)>0) {
        if (p1[i]<p2[j]) {
            temp[x] = p1[i];
            i++;
            x++;
        } else {
            temp[x] = p2[j];
            j++;
            x++;
        }
    }
    while(l1>i){
        temp[x] = p1[i];
        i++;
        x++;
    }
    while(l2>j){
        temp[x] = p2[j];
        j++;
        x++;
    }
}

void mergeSort(int32_t *unsorted,int32_t *sorted,int n) {
    if (n == 1) {
        sorted[0]=unsorted[0];
    } else {
        int32_t *temp = (int32_t*)malloc(sizeof(int32_t) * (n));;
        int d = (n / 2);

        mergeSort(unsorted,temp,d);
        mergeSort(&unsorted[d],&temp[d],n-d);

        merge(sorted,temp, d, &temp[d], (n - d));
        free(temp);
    }
}

int main(int argc, char **argv) {

    int n=10;
    if(argc==2){
        char *p;
        n= strtol(argv[1],&p,10);
    }
    int32_t* unsorted = (int32_t*)malloc(sizeof(int32_t) * n);
    int32_t* sorted = (int32_t*)malloc(sizeof(int32_t) * n);

    double start_time;
    double end_time;
    // fill array
    srand(12);
    for (long i = 0; i < n; ++i) {
        unsorted[i] = rand()%n;
        sorted[i] = unsorted[i];
    }

    printf("TEST 1 with n = %d: \n",n);
    printf("SeqMergeSort: \n");

    //Ausgabe:
    printf("Unsorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",unsorted[i]);
    }
    printf("%d]\n",unsorted[n-1]);
    start_time = omp_get_wtime();
    //sort
    mergeSort(unsorted,sorted, n);
    end_time = omp_get_wtime();

    printf("Sorted: [");
    for(int i =0;i<n-1;i++){
        printf("%d,",sorted[i]);
    }
    printf("%d]\n",sorted[n-1]);

    printf("time: %2.4f seconds\n",  end_time - start_time);
    qsort(unsorted,n,sizeof(int32_t),compare);
    if(!equal(unsorted,sorted,n)){
        printf("\nTEST 1 BESTANDEN!\n\n");
    } else{
        printf("\nTEST 1 NICHT BESTANDEN!\n\n");
    }

    //----------------------------------------------------

    // cleanup
    free(unsorted);
    free(sorted);

    return EXIT_SUCCESS;
}