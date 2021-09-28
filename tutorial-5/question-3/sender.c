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
    int dataq_id = msgget((key_t)DATAQ_ID, 0666|IPC_CREAT);
    int echoq_id = msgget((key_t)ECHOQ_ID, 0666|IPC_CREAT);

    if(dataq_id == -1) {
        perror("sender: dataq mssget");
        exit(0);
    }

    /*if(echoq_id == -1) {
        perror("sender: echoq msgget");
        exit(0);
    }*/


    bool running = true;
    char buffer[50];
    struct message temp_data, echo_data;
    while(running) {
        printf("[%d] Enter some text: ", getpid());
        fgets(buffer, 50, stdin);
        temp_data.type = 1;
        strcpy(temp_data.data, buffer);
        msgsnd(dataq_id, (void *)&temp_data, MAX_MSG_SIZE, 0);
        msgrcv(echoq_id, (void *)&echo_data, MAX_MSG_SIZE, 1, 0);
        printf("[%d] Echoed: %s\n", getpid(), echo_data.data);
        if(strncmp(buffer, "end", 3) == 0) {
            running = false;
        }
    }

    return 0;
}
