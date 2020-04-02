#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
        int p2c[2];
        int c2p[2];
        int n=fork();
        if (n!=0)
        {
                printf("Pidul parintelui: %d\n", getpid());
                
        }
        else
        {
                printf("Pidul copilului: %d\n", getpid());
        }
        return 0;
}
