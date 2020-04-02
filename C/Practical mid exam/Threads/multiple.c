#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int multiple = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *myThread (void * context) {
	int newcontext = *(int*)context;
	int i = 0;
	pthread_mutex_lock(&mutex);
	//printf("%d", newcontext);
	//printf("\n");
	if (newcontext % 2 == 0 || newcontext % 5 == 0) {
		multiple += 1;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t th[100];
	int i;
	int number[100];
	for (i = 1; i < argc; i++) {
		number[i] = atoi(argv[i]);
		pthread_create(&th[i], NULL, &myThread, (void*)&number[i]);
	}
	for (i = 1; i < argc; i++) {
		pthread_join(th[i], NULL);
	}
	printf("There are %d numbers which are multiple of 2 or 5.\n", multiple); 
	return 0;	
}
