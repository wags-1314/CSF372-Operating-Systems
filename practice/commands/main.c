#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buffer[1024];

    pid_t pid = fork();

    if (pid > 0) {
        /* Parent Process */
        wait(NULL);
        FILE* fin = fopen("commands.txt", "r");
        fgets(buffer, 1024, fin);
        execl("/bin/bash", buffer, NULL);
    }
    else if (pid == 0) {
        FILE* fin = fopen("commands.txt", "r");
        /* Child Process */
        while (!feof(fin)) {
            fgets(buffer, 1024, fin);
        }
        execl("/bin/bash", buffer, NULL);
    }
}
