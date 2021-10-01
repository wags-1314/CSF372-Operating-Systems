#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main() {
    int to[2], from[2], n;
    char buffer[256];

    int ret1 = pipe(to);
    int ret2 = pipe(from);
    if (ret1 != 0 || ret2 != 0) {
        printf("[Error] Unable to create a pipe.\n");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        /* Parent Process: Sender */
        fgets(buffer, 256, stdin);
        write(to[1], buffer, 256);
        printf("[%d] Sending \"%s\" to %d", getpid(), buffer, pid);
        wait(NULL);
    } else {
        /* Child Process: Reciever */
        read(to[0], buffer, 256);
        printf("[%d] Recieved \"%s\" from %d", getpid(), buffer, getppid());
    }
    return 0;
}
