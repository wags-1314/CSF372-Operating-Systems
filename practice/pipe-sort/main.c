#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>

#define N 20

int arr[] = { 19, 48, 38, 4, 29, 31, 18, 2, 33, 22, 34, 15, 25, 46, 30, 3, 26, 23, 43, 7 };

int main() {
    int fd[2], n;
    char buffer[256];

    int ret = pipe(fd);
    if (ret != 0) {
        printf("[Error] Unable to create a pipe.\n");
        exit(1);
    }
    
    pid_t pid = fork();

    if (pid > 0) {
        /* Parent Process: Sender */
        wait(NULL);
        int num;
        close(fd[1]);
        for(int i = 0; i < N; i++) {
            read(fd[0], &num, sizeof(num));
            printf("%d ", num);
        }
    } else {
        /* Child Process: Reciever */
        close(fd[0]);
        for(int i = 0; i < N - 1; i++) {
            int min_index = i;
            for(int j = i + 1; j < N; j++) {
                if(arr[j] < arr[min_index])
                    min_index = j;
            }
            
            write(fd[1], &(arr[min_index]), sizeof(arr[min_index]));
            
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
    return 0;
}
