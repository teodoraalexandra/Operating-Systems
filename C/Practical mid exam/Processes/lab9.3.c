#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int p2c[2];
    
    int res = 0;

    // create pipe
    pipe(p2c);

    // create child process
    res = fork();
    switch(res)
    {
        case -1:
            perror("fork failed!");
            exit(0);
        case 0:
            // child process
            
            // read words from pipe
            for(int i=1; i< argc - 1; i++) {
		read(p2c[0], &argv[i], sizeof(char)); 
            	printf("Word is: %s\n", argv[i]);}

            // close pipes
            close(p2c[0]);
            close(p2c[1]);

            // child is done
            exit(0);
        default:
            // parent process

            // send chars to child
		for(int i=1; i<argc - 1 ; i++) {
			write(p2c[1], &argv[i], sizeof(char));
		}

            // wait for child process to terminate
            wait(0);

            // close pipes
            close(p2c[0]);
            close(p2c[1]);
    }

    return 0;
}

