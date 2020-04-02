#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t thread[4];
int mat_A[2][2], mat_B[2][2], sum[2][2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* addition(void* context) { 
	int i, j; 
   	int core = (int)context; 
   
    	for (i = core / 2; i < (core + 1) / 2; i++) { 
        	for (j = 0; j < 2; j++) { 
            		sum[i][j] = mat_A[i][j] + mat_B[i][j]; 
        	}
    	}
	return NULL;
} 

int main() {
	int i, j, step = 0;  
    	for (i = 0; i < 2; i++)  { 
  		for (j = 0; j < 2; j++)  { 
  			mat_A[i][j] = rand() % 10; 
            		mat_B[i][j] = rand() % 10; 
		} 
  	}
	printf("\nMatrix A:\n"); 
  
    	for (i = 0; i < 2; i++) { 
  		for (j = 0; j < 2; j++) { 
  			printf("%d ", mat_A[i][j]); 
        	} 
  	printf("\n"); 
    	}  

	printf("\nMatrix B:\n"); 
  
    	for (i = 0; i < 2; i++) { 
  		for (j = 0; j < 2; j++) { 
 			printf("%d ", mat_B[i][j]); 
        	} 
 	printf("\n"); 
    	}

	for (i = 0; i < 4; i++) { 
  		pthread_create(&thread[i], NULL, &addition, (void*)step);  
        	step++; 
    	} 
   
  	for (i = 0; i < 4; i++) { 
  		pthread_join(thread[i], NULL); 
    	} 
	 
	printf("\n Sum of Matrix A and B:\n"); 
  
    	for (i = 0; i < 2; i++) { 
  		for (j = 0; j < 2; j++) { 
  			printf("%d   ", sum[i][j]); 
        	} 
  	printf("\n"); 
   	}
} 
