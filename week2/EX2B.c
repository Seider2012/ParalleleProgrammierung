#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int n = 5000;


void hadamard(int32_t *a ,int32_t *b ,int32_t *c ){

	for (size_t i = 0; i < n; ++i) {
	    for (size_t j = 0; j < n; ++j) {
	        a[i*n+j] =  rand()%3;
     		  b[i*n+j]= rand()%3;
	    }
	}

	for (size_t j = 0; j < n; ++j) {
	    for (size_t i = 0; i < n; ++i) {
	        c[i*n+j]= a[i*n+j]* b[i*n+j];
	    }
	}

}

int main(int argc, char *argv[]) {

int32_t *a = (int *)malloc( sizeof(int32_t)*n*n);
int32_t *b = (int *)malloc( sizeof(int32_t)*n*n);
int32_t *c = (int *)malloc( sizeof(int32_t)*n*n);

	hadamard(a,b,c);	
	/*
  	for (int i = 0; i < n; i++) {
   	   for (int j = 0; j < n; j++)
   	     printf("%d\t", c[i*n+j]);
   	   printf("\n");
 	 }
	*/
	free(a);
	free(b);
	free(c);

	return EXIT_SUCCESS;
}

