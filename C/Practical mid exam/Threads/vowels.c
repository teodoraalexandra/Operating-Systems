#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int v = 0;
int d = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *myThread (void * context) {
	char * newcontext = (char*) context;
	int i;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < strlen(newcontext); i++) {
		d += 1;
		char pvowel = newcontext[i];
		if (pvowel == 'a' || pvowel == 'e' || pvowel == 'i' || pvowel == 'o' || pvowel == 'u') {
			v += 1;
		}
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t th[100];
	int i;
	for (i = 1; i < argc; i++) {
		pthread_create(&th[i], NULL, &myThread, argv[i]);
	}
	for (i = 1; i < argc; i++) {
		pthread_join(th[i], NULL);
	}
	printf("\n");
	printf("Total number of characters:%d \n", d);
	printf("Total number of vowels:%d \n", v);
	printf("\n");
	return 0;
}
	
