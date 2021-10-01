#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>

int main() {
    int to[2], from[2], n;
    char buffer[256];

    int ret1 = pipe(to);
    int ret2 = pipe(from);
    if (ret1 != 0 || ret2 != 0) {
        printf("[Error] Unable to create a pipe.\n");
        exit(1);
    }
    
    printf("[%d] Enter String: ", getpid());
    fgets(buffer, 256, stdin);
    pid_t pid = fork();

    if (pid > 0) {
        /* Parent Process: Sender */
        write(to[1], buffer, 256);
        printf("[%d->%d] Sending: %s", getpid(), pid, buffer);
        wait(NULL);
        read(from[0], buffer, 256);
        printf("[%d->%d] Recieved: %s", pid, getpid(), buffer);
    } else {
        /* Child Process: Reciever */
        read(to[0], buffer, 256);
        printf("[%d->%d] Recieved: %s", getppid(), getpid(), buffer);
        for(int i = 0; buffer[i] != 0; i++) {
            if(isalpha(buffer[i])) {
                buffer[i] ^= 32;
            }
        }
        write(from[1], buffer, 256);
        printf("[%d->%d] Flipping: %s", getpid(), getppid(), buffer);

    }
    return 0;
}
