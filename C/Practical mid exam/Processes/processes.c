/*
	For each command line argument the main process will create a new process (A).
	This process (A) will create a new process (B).
	The nephew process (B) will establish the number of vowels that are part of the argument's name,
	using a shell script launched with popen.
	The B process will send to his parent (A) the number received using a private pipe channel.
	The communication between the main process and his subprocesses (of type A) will be maintained
	using a shared pipe channel.
	The main process will collect all the results and will print them.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100
 
int main(int argc, char const *argv[])
{
	FILE *fp;
	char result[N], cmd[N], msg[N];
	int c2p[2], n2c[2];
	int i;
	
	for (i = 1; i < argc; ++i) {
		pipe(c2p);
		pipe(n2c);
		// child code
		if (0 == fork()) {
			// nephew code
			if (0 == fork()) {
				sprintf(cmd, "echo %s | grep -o [AEIOUaeiou] | wc -l", argv[i]);
				fp = popen(cmd, "r");
				fgets(result, N, fp);
				pclose(fp);
				write(n2c[1], result, 10);
				exit(0);
			}
			read(n2c[0], msg, 10);
			close(n2c[0]);
			close(n2c[1]);
			wait(0);
			write(c2p[1], msg, 10);
			exit(0);
		}
		// parent code
		read(c2p[0], result, 10);
		close(c2p[0]);
		close(c2p[1]);
		wait(0);
		printf("%s\n", argv[i]);
		printf("%s\n", result);
	}
	return 0;
}
