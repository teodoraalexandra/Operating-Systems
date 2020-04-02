#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	int MAX_THREADS = argv[1];
	pthread_t tid[MAX_THREADS]={{0}};
    	int count=0;
    	for(count=0;count<MAX_THREADS;count++)
    {
        printf("\r\n CREATING THREADS %d",count);
        pthread_create(&tid[count],NULL,printprime,(void*)count);
    }
    printf("\n");
    for(count=0;count<MAX_THREADS;count++)
    {
        pthread_join(tid[count],NULL);
    }

    int c=0;
    for(count=0;count<N;count++)
        if(prime_arr[count]==1)
            printf("%d ",count);

    return 0;
}
