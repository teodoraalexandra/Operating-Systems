#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int p2c[2], c2p[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThread(void * context) {
	int newcontext = *(int*)context;
	sleep(2);
	srand(time(NULL));
	int random;
	random = rand() % 10 + newcontext;
	printf("Random number generated:%d\n ", random);
	return NULL;
}

int main(int argc, char * argv[]) {
	int n, i;
	pthread_t th;
	pthread_t th2;
	printf("Introduceti un numar mai mic decat 10:\n ");
	scanf("%d", &n);
	int arguments[10];
	arguments[0] = argc;
	pthread_create(&th, NULL, &myThread, (void*)&arguments[0]);
	pthread_join(th, NULL);

	 
	return 0;
}
