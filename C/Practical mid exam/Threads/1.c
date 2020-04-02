//Din linia de comanda se ia un numar, iar intr-un for
//se va crea cate un thread

//#include <ctype.h>
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThread(void * context) {
	//int * newcontext;
	//newcontext = (int*)context;
	int newcontext = *(int*)context;
	printf("%d\n", newcontext);
	//while (* newcontext) {
		//*newcontext = toupper(* newcontext);
		//newcontext ++;
	//}
	//printf("%s\n", newcontext);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t th;
	int i;
	for (i = 0; i < 5; i++) {
		pthread_create(&th, NULL, &myThread, (void*)&i);
	}
	pthread_join(th, NULL);
}
