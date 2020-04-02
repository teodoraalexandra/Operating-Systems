#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int n;
void *myThread(void * context) {
        int i = (int)context; 
        
	while (n != i)
	; 
		pthread_mutex_lock(&mutex);
		printf("%d\n", i);
		n--;
		pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char * argv[]) {
        pthread_t th[1000];
        int i;
	n = atoi(argv[1]);
	
        for (i = 1; i <= n; i++) {
                pthread_create(&th[i], NULL, &myThread, i);
        }
        for (i = 1; i <= n; i++)
                pthread_join(th[i], NULL);
        return 0;
}


