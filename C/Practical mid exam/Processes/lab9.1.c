#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int PC[2], CP[2];
	printf("%d\n", atoi(argv[1]));
	if (pipe(PC) < 0) {
		perror("Error on pipe");
		exit(1);
	}

	if (pipe(CP) < 0) {
                perror("Error on pipe");
                exit(1);
        }

	int f = fork();
	if (f<0) {
		perror("Error on fork");
		exit(2);
	}
	if (f == 0) { //child
		close(PC[1]);
		close(CP[0]);
		int x = atoi(argv[1]);
		while (x > 0) {
			int n = rand()%10 + 1;
			x -= n;
			write(CP[1], &x, sizeof(int));
			printf("%d %s\n", x, "child");
			if (read(PC[0], &x, sizeof(int)) < 0) {
                                exit(0);
                        }
		}	
		exit(0);
	}
 	if (f > 0) { //parent
		int x;
		read(CP[0], &x, sizeof(int));
		close(PC[0]);
		close(CP[1]);
		while (x > 0) {
			int n = rand()%10 + 1;
			x -= n;
			write(PC[1], &x, sizeof(int));
			printf("%d %s\n", x, "parent");
			if (read(CP[0], &x, sizeof(int)) < 0 ) {
                           
                                exit(0);
                        }
		}
		
		exit(0);
	}
	return 0;
}
