#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include"msg_def.h"

int main(int argc, char* argv[]) {
    int msgq_id = msgget((key_t)MSGQ_ID, 0666|IPC_CREAT);

    if(msgq_id == -1) {
        perror("sender: dataq mssget");
        exit(0);
    }

    struct message buffer;
    for(int i = 0; i < N - 1; i++) {
        int min_index = i;
        for(int j = i + 1; j < N; j++) {
            if(arr[j] < arr[min_index])
                min_index = j;
        }
        
        buffer.type = 1;
        buffer.number = arr[min_index];
        msgsnd(msgq_id, (void *)&buffer, sizeof(buffer.number), 0);
        
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }

    return 0;
}
