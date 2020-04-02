#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//FARA MUTEX-URI: fara linia asta de comanda
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThread(void * context) {
	char * newcontext = (char*)context;
	
	int i = 0;
	//SI ASTA
	pthread_mutex_lock(&mutex);
	for (i = 0; i < strlen(newcontext); i++) {
		printf("%c", newcontext[i]);
	}
	printf("\n");
	//SI ASTA
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t th[100];
	int i;
	for (i = 1; i < argc; i++) {
		pthread_create(&th[i], NULL, &myThread, argv[i]);
	}
	for (i = 1; i < argc; i++) 
		pthread_join(th[i], NULL);
	return 0;
}
