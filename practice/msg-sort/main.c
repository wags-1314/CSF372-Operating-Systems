#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define N 20

int arr[] = { 19, 48, 38, 4, 29, 31, 18, 2, 33, 22, 34, 15, 25, 46, 30, 3, 26, 23, 43, 7 };

struct message {
    long int type;
    int data;
};

int main(){
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    pid_t pid = fork();
    if(pid == 0) {
        /* Child Process */
        struct message buffer;
        
        for(int i = 0; i < N - 1; i++) {
            int min_index = i;
            for(int j = i + 1; j < N; j++) {
                if(arr[j] < arr[min_index])
                    min_index = j;
            }
            
            buffer.type = 1;
            buffer.data = arr[min_index];
            msgsnd(msgid, &buffer, sizeof(buffer.data), 0);
            
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    } else {
        /* Parent Process */
        struct message buffer;
        for(int i = 0; i < N; i++) {
            msgrcv(msgid, &buffer, sizeof(buffer.data), 1, 0);
            printf("%d ", buffer.data);
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
}
