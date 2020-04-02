/*Scrieti un program care creeaza un proces fiu, caruia ii trimite printr-un pipe toate numerele primite ca argumente din linia de comanda. Procesul fiu le citeste si creeaza cate un thread pentru fiecare numar primit, caruia ii trimite numarul ca argument. Fiecare fiu verifica daca numarul este prim, si ii trimite un raspuns parintelui prin pipe.*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_t th[100];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int p2c[2],c2p[2];
void* work(void* arg)
{
	int nr = *((int*)arg);
	int raspuns = 1;
	if(nr % 2 == 0 && nr!=2)
		raspuns = 0;
	if(nr==1)
		raspuns = 0;
	for(int d=3;d*d<=nr;d+=2)
		if(nr%d==0)
			raspuns = 0;
	char c = ' ';
	pthread_mutex_lock(&mtx);
	write(c2p[1],&nr, sizeof(int));
	write(c2p[1],&c, sizeof(char));
	write(c2p[1],&raspuns, sizeof(int));
	pthread_mutex_unlock(&mtx);
}
int main(int argc, char** argv)
{
	pipe(p2c);
	pipe(c2p);
	int f = fork();
	if(f<0)
	{
		perror("Fork failed");
		return -1;
	}
	if(f==0)
	{
		for(int i = 1;i<argc;i++)
		{
			int* p = (int*)malloc(sizeof(int));
			if(read(p2c[0],p,sizeof(int)) < 0)
				return 0;
			pthread_create(&th[i],NULL, work, (void*)p);
		}
		for(int i=1;i<argc;i++)
		{
			pthread_join(th[i],NULL);
		}
		return 0;
	}
	else
	{
		for(int i=1;i<argc;i++)
		{
			int nr = atoi(argv[i]);
			write(p2c[1],&nr,sizeof(int));
		}
		for(int i=1;i<argc;i++)
		{
			int nr;
			int raspuns;
			char c;
			read(c2p[0],&nr, sizeof(int));
			read(c2p[0],&c, sizeof(char));
			read(c2p[0],&raspuns,sizeof(int));
			if(raspuns == 1)
				printf("%d este prim\n",nr);
			else printf("%d este neprim\n", nr);
		}
		return 0;

	}

	return 0;

}

