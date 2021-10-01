#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if(pid == 0) {
        /* Child Process */
        execlp("grep", "-iw", argv[1], argv[2], NULL);
    } else {
        /* Parent Process */
        int status;
        waitpid(pid, &status, 0);
        printf("%s \"%s\" in \"%s\".", status == 0 ? "Found" : "Did not find", argv[1], argv[2]);
    }
}
