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
    for(int i = 0; i < N; i++) {
        msgrcv(msgq_id, (void *)&buffer, sizeof(buffer.number), 1, 0);
        printf("%d ", buffer.number);
    }

    msgctl(msgq_id, IPC_RMID, NULL);

    return 0;
}
