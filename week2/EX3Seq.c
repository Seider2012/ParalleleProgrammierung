	#include <stdlib.h>
	#include <stdio.h>
	#include <errno.h>
	#include <pthread.h>
	#include <sys/types.h>
	#include <unistd.h>

	#define DOTS 50000

	time_t t;



	int main() {
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
		return EXIT_SUCCESS;
	}
