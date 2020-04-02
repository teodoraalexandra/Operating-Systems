/*Scrieti un program care creeaza cate un proces fiu pentru fiecare numar primit ca argument din linia de comanda, 
trimitandu-i printr-un pipe fiecarui fiu numarul asociat. Procesele fiu creeaza fiecare cate un thread, c
are este responsabil sa citeasca din pipe numarul trimis de parinte, si sa verifice daca este numar prim, 
trimitandu-i raspunsul parintelui.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t th[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int p2c[2], c2p[2];

void *myThread (void * context) {
	int nr, d;

	read(p2c[0], &nr, sizeof(int));
	int ok = 1;
	if (nr%2 == 0 && nr!=2) 
		ok = 0;
	if (nr == 1) 
		ok = 0;
	for (d = 3; d*d <= nr; d+=2) {
		if (nr%d == 0)
			ok = 0;
	}
	char c = ' ';
	//pthread_mutex_lock(&mutex);
	write(c2p[1], &nr, sizeof(int));
	write(c2p[1], &c, sizeof(char));
	write(c2p[1], &ok, sizeof(int));
	//pthread_mutex_unlock(&mutex);
	return NULL;
}

int main (int argc, char * argv[]) {
	pipe(p2c);
	pipe(c2p);
	int i, j, f;
	
	for (i = 1; i < argc; i++) {
		f = fork();
		if ( f < 0 ) 
			return -1;
		else if ( f == 0 ) {
			//CHILD process
			for (j = 1; j < argc; j++) {
				pthread_create(&th[j], NULL, myThread, NULL);
			}		
			for (j = 1; j < argc; j++) {
				pthread_join(th[i], NULL);
			}
			return 0;
		} else {
			//PARENT process
			for (j = 1; j < argc; j++) {
				int nr = atoi(argv[j]);
				write(p2c[1], &nr, sizeof(int));
			}
			for (j = 1; j < argc; j++) {
				int nr, ok;
				char c;
				read(c2p[0], &nr, sizeof(int));
				read(c2p[0], &c, sizeof(char));
				read(c2p[0], &ok, sizeof(int));
				if (ok == 0) {
					printf("Numarul %d nu este prim\n", nr);
				} else {
					printf("Numarul %d este prim\n", nr);
				}
			}
		}
		return 0;
	} 
	return 0;
}


