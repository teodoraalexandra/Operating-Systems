/*Scrieti un program care primeste N cuvinte ca argumente din linia de comanda, 
iar apoi creeaza un thread caruia i se transmite indexul "1", corespunzator primului argument din linia de comanda. 
Acel thread creeaza la randul lui un alt thread, caruia ii transmite ca argument indexul "2", 
si tot asa, pana cand sunt creeate N threaduri. 
Procesul trebuie sa creeze si un proces fiu, caruia fiecare thread ii va transmite cuvantul corespunzator indexului primit,
neaparat in ordine inversa. 
Procesul fiu citeste cuvant cu cuvant si le afiseaza.*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
int p2c[2], c2p[2];
int idx;
int arguments;
char ** global = (char**)malloc(10*sizeof(char*));
pthread_t th[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThread(void * context) {
	//char ** global = (char**)malloc(10*sizeof(char*));
	while(idx != arguments) {
		pthread_mutex_lock(&mutex);
		printf("thread%s\n", global[2]);
		write(p2c[1], &idx, sizeof(int));
		//arguments --;
		pthread_mutex_unlock(&mutex);

		idx ++;
		//indexes[idx] = idx;
	
		pthread_create(&th[idx], NULL, &myThread, idx);
		pthread_join(th[idx], NULL);
	}
	return NULL;
}

int main(int argc, char * argv[]) {
	int i;
	//char ** global = (char**)malloc(10*sizeof(char*));
	for (i = 0; i < argc; i++) {
		global[i] = (char*)malloc(10*sizeof(char*));
	}
	for (i = 1; i < argc; i++) {
		global[i] = argv[i];
		printf("main%s\n", argv[i]);
		printf("global%s\n", global[i]);
	}

	pipe(p2c);
	pipe(c2p);
	arguments = argc;
	idx = 1;
	int f = fork();
	if (f < 0) 
		return -1;
	if (f == 0) {
		//CHILD
		while(idx < arguments) {
			read(p2c[0], &idx,sizeof(int));
			printf("Child word %s\n", global[idx]);	
		}

	} else {
		//PARENT
		pthread_create(&th[idx], NULL, &myThread, idx);	
		pthread_join(th[idx], NULL);
		return 0;
	}
	return 0;
}
