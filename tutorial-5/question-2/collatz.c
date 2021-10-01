#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/shm.h>
#include<string.h>

char* int_to_string(int x) {
    int length = snprintf(NULL, 0, "%d", x);
    char* str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;
}

bool is_number(char *string) {
    for(int i = 0; string[i] != 0; i++) {
        if(!isdigit(string[i]))
            return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    // create share memory object
    int shmid = shmget((key_t)2345, 1024, 0666|IPC_CREAT);

    if(argc > 2) {
        perror("Error: More than one argument\nUsage: ./collatz <positive_int>");
        exit(1);
    } else if(argc < 2) {
        perror("Error: No arguments\nUsage: ./collatz <positive_int>");
        exit(1);
    }

    if(!is_number(argv[1])) {
        perror("Error: Argument was not a positive integer\nUsage: ./collatz <positive_integer>");
        exit(1);
    }

    int number = atoi(argv[1]);

    pid_t pid = fork();

    if(pid > 0) {
        wait(NULL);
        void *shm_ptr = shmat(shmid, NULL, 0);
        printf("[%d] Collatz sequence for %d: %s\n", getpid(), number, (char *)shm_ptr);
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        void *shm_ptr = shmat(shmid, NULL, 0);
        
        char *num = int_to_string(number);
        strcpy(shm_ptr, num);
        free(num);
        
        int numb = number;
        do {
            if(numb % 2 == 0) {
                numb = numb / 2;
            } else {
                numb = (3 * numb) + 1;
            }
            
            strcat(shm_ptr, ", ");
            char* numstr = int_to_string(numb);
            strcat(shm_ptr, numstr);
            free(numstr);
        } while(numb != 1);

        printf("[%d] Done calculating Collatz sequence for %d\n", getpid(), number);
        shmdt(shm_ptr);
    }
    return 0;
} 
