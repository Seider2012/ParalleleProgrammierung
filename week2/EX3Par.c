	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>

	#include <pthread.h>
	#include <sys/types.h>
	#include <unistd.h>

	#define NUM_THREADS 5
	#define DOTS 50000

	pthread_t ntid[NUM_THREADS];
	long double nerg[NUM_THREADS];

	void *mythread();
	time_t t;

	int main() {

		srand((unsigned) time(NULL));
		int err;
		long double sum =0;
		err = pthread_create(&ntid[0], NULL, mythread,NULL );
		if(err != 0){
			 perror("can't create thread");
			 exit(EXIT_FAILURE);
		 }
		for(int i=1; i<NUM_THREADS;i++){
			pthread_create(&ntid[i], NULL, mythread,NULL );
		}

		for(int i=0; i<NUM_THREADS;i++){
			pthread_join(ntid[i], NULL);
		}
		for(int i=0; i<NUM_THREADS;i++){
			sum=sum+nerg[i];
		}
		long double pi = sum /NUM_THREADS;
		printf("PI is %Lf \n",pi);
		return EXIT_SUCCESS;
	}

	

	void *mythread(){

		pthread_t myId = pthread_self();
		long double x,y,z;
		int count=0;

		for(int i=0;i<(DOTS/NUM_THREADS);i++){
 			x= (long double)rand() / (long double)RAND_MAX ;
			y= (long double)rand() / (long double)RAND_MAX ;
			z= (x*x+y*y);
			if(z<=1) count=count+1;

		}
		long double erg =(4* ((long double) count))/(DOTS/NUM_THREADS);

		for(int i=0;i<NUM_THREADS; i++){
			if(ntid[i]== myId) nerg[i]=erg;
		}
		return ((void *) 0);
	}
