/* 
 Implement a program that writes a number between 0 and 9 in a global
 variable and then creates 10 threads. Each thread will check the  
 global variable  and if its value is the order number of the thread (given
 from main at  creation time), the thread writes in the global variable 
 another number  between 0 and 9 (different than its own). The program ends
 when the global variable is changed 20 times.
*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>

int x, counter = 0;
pthread_t t[10];
pthread_mutex_t mtx;

func(int i)
{
	while (counter != 20) {
		if (x == i) {
			pthread_mutex_lock(&mtx);
			counter++;
			printf("%d. %d \n", counter, x);
			while (x == i) {
				srand(time(NULL));
				x = rand() % 10;
			}
			pthread_mutex_unlock(&mtx);
		}
	}
}

int main()
{
	int i;
	srand(time(NULL));
	x = rand() % 10;
	for (i = 0; i < 10; i++) {
		pthread_create(&t[i], NULL, func, i);
	}

	for (i = 0; i < 10; i++) {
		pthread_join(t[i], NULL);
	}
	return 0;
}
