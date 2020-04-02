#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count;
void *myThread() {
	int i;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < 1000; i++)
		count ++;
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t th[1000];
	int i;
	for (i = 0; i < 1000; i++) {
		pthread_create(&th[i], NULL, &myThread, NULL);
	}
	for (i = 0; i < 1000; i++)
		pthread_join(th[i], NULL);
	printf("%d\n", count);
	return 0;
}
