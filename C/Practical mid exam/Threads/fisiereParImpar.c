#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int caracterePare = 0;
int caractereImpare = 0;
void *myThread(void * context) {
        FILE * newcontext = (FILE*)context;
        char ch;
        pthread_mutex_lock(&mutex);
        while ( (ch = getc(newcontext)) != EOF ) {
		int ascii = (int) ch;
                if (ascii % 2 == 0) {
			caracterePare += 1;
		} 
		else {
			caractereImpare += 1;
		}
		printf("%c", ch);
        }
        pthread_mutex_unlock(&mutex);
        return NULL;
}

void *open(void * context) {
	pthread_t th[100];
	char * newcontext = (char*)context;
	FILE *fp;
	int i;
	fp = fopen(newcontext, "r");
	for (i = 0; i < 5; i++) {
                pthread_create(&th[i], NULL, &myThread, fp);
        }
        for (i = 0; i < 5; i++) {
                pthread_join(th[i], NULL);
        }
	fclose(fp);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t principal;
	int i;
	pthread_create(&principal, NULL, &open, argv[1]);
	pthread_join(principal, NULL);
	printf("Numarul caracterelor pare: %d\n", caracterePare);
	printf("Numarul caracterelor impare: %d\n", caractereImpare);
	return 0;
}
