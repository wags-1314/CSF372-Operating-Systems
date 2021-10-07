#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// int arr[] = { 2, 3, 4, 7, 15, 18, 19, 22, 23, 25, 26, 29, 30, 31, 33, 34, 38, 43, 46, 48 };
int arr[] = { 19, 48, 38, 4, 29, 31, 18, 2, 33, 22, 34, 15, 25, 46, 30, 3, 26, 23, 43, 7 };


int main() {
    int fd[2];
    char buffer[256];

    int ret1 = pipe(fd);
    if (ret1 != 0) {
        printf("[Error] Unable to create a pipe.\n");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        int num = arr[0];
        write(fd[1], &num, sizeof(num));
        printf("[%d] Sending %d", getpid(), buffer, pid);
        wait(NULL);
    }
    else {
        /* Child Process: Reciever */
        read(to[0], buffer, 256);
        printf("[%d] Recieved \"%s\" from %d", getpid(), buffer, getppid());
    }
    return 0;

}
