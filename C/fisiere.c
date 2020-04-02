#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int PC[2], CP[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *tcitire(void * context) {
	pthread_t th[100];
	char * newcontext = (char*)context;
	FILE *fp;
	int i;
	fp = fopen(newcontext, "r");
	char ch;
        pthread_mutex_lock(&mutex);
        while ( (ch = getc(fp)) != EOF ) {
                printf("%c", ch);
		//FILE* f;
		//f = fopen(newcontext, "w");
		//pthread_create(&scriere, NULL, &tscriere, f);
		//pthread_join(scriere, NULL);
		//fclose(f); 
        }
        pthread_mutex_unlock(&mutex);
	fclose(fp);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t citire;
	pthread_t scriere;
	pthread_create(&citire, NULL, &tcitire, argv[1]);
	pthread_join(citire, NULL);
	//pthread_create(&scriere, NULL, &tscriere, argv[2]);
	//pthread_join(scriere, NULL);
	return 0;
}
