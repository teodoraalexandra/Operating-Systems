#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

int p2c[2], c2p[2];
char word[20];
char ch;
pthread_t th[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fourth(void * context) {
	read(c2p[0], &word, sizeof(word));
	printf("Ultimul thread: %s\n", word);
	return NULL;
}

void *first(void *context) {
	//printf("Enter sentence: ");
	//gets(word);
	int i = 0;
	char * newcontext = (char*) context;
	FILE* fp;
	fp = fopen(newcontext, "r");
	while ((ch = fgetc(fp)) != EOF) {
		word[i] = ch;
		i ++;
	}
		
	write(p2c[1], &word, sizeof(word)); 
	return NULL;
}

void *third(void * context) {
	char * newcontext = (char*)context;
	write(c2p[1], &newcontext, sizeof(char));
	return NULL;
}

void *second(void *context) {
	read(p2c[0], &word, sizeof(word));
	int i;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < strlen(word); i++) {
		word[i] = toupper(word[i]);	
	}
	pthread_mutex_unlock(&mutex);
	for (i = 0; i < strlen(word); i++) {
		pthread_create(&th[i], NULL, &third, word[i]);
	}
	for (i = 0; i < strlen(word); i++) {
		  pthread_join(th[i], NULL);
	}
	return NULL;
}

int main(int argc, char * argv[]) {
	int i;

	pipe(p2c);
	pipe(c2p);
	int f = fork();
	if (f < 0) 
		return -1;
	if (f == 0) {
		//child
		pthread_create(&th[1], NULL, &second, NULL);
		pthread_join(th[1], NULL);
		exit(0);
	} else {
		//parent
		pthread_create(&th[0], NULL, &first, argv[1]);
		pthread_join(th[0], NULL);
		wait(0);
		pthread_create(&th[2], NULL, &fourth, NULL);
		pthread_join(th[2], NULL);
	}
	return 0;
}
