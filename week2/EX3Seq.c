	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <pthread.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <time.h>

	#define DOTS 500000000

	time_t t;



	int main() {
		clock_t begin = clock();
		srand((unsigned) time(NULL));
		long double x,y,z;
		int count=0;
		for(int i=0;i<(DOTS);i++){
 			x= (long double)rand() / (long double)RAND_MAX ;
			y= (long double)rand() / (long double)RAND_MAX ;
			z= (x*x+y*y);
			if(z<=1)count=count+1;

		}

		long double pi =(4* ((long double) count))/DOTS;

		printf("PI is %Lf \n",pi);
		clock_t end = clock();
		printf("time= %f\n",(double)(end-begin)/CLOCKS_PER_SEC);
		return EXIT_SUCCESS;
	}
