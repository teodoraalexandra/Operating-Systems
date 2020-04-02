#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int main () 
{
	int CP[2], PC[2];
	if (pipe(CP) < 0) { perror("pipe error"); exit(1); }
	if (pipe(PC) < 0) { perror("pipe error"); exit(2); }

	int f = fork();
	if (f == -1) { perror("fork error"); exit(3); }

	else if (f == 0) {
		//child process - read 2 numbers from parent. write the sum to the parent
		close(PC[1]);
		close(CP[0]);
		while(1) {
			int a, b;
			read(PC[0], &a, sizeof(int));
			if (a==0) {break;}
 			read(PC[0], &b, sizeof(int));
			int sum = a + b;
			//write(CP[1], &sum, sizeof(int));
			printf("As child, I have the sum: %d\n", sum);
		}
		close(PC[0]);
		close(CP[1]);
		exit(0);
	}
	else {
	
	close(PC[0]);
	close(CP[1]);
	while(1) {
		//parent process - read 2 numbers and send to child. read the sum from the child
		int a;
		printf("Enter a number: ");
		scanf("%d", &a);
		//write(PC[1], &a, sizeof(int));

		if(a==0) {break;}
		
		int b;
		printf("Enter b number: ");
		scanf("%d", &b);
		//write(PC[1], &b, sizeof(int));
		
		int sum = 0;
		read(CP[0], &sum, sizeof(int));
		printf("As parent, I have the sum: %d\n", sum);
	}
	//wait for child
	int status;
	wait(&status);
	
	close(PC[1]);
	close(CP[0]);		
	}
	return 0;
}
