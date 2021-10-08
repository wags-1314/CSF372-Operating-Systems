#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct message{
    long int priority;
    int data;
};
int glob[5] = {7,2,89,3,1};
int main(){
    pid_t id;
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    id = fork();
    if(id == 0){ //child
        printf("Child is child\n");
        struct message bfr;
 
        int n = sizeof(glob)/sizeof(int);
        int min_prev = -1;
        for(int i = 0 ; i < n; i++){
            int min = INT_MAX;
            for(int j = 0; j < n; j++){
                if(glob[j] < min && glob[j] > min_prev)
                {
                    min = glob[j];
                }
            }
            min_prev = min;
            bfr.priority = 1;
            bfr.data = min;
            msgsnd(msgid, &bfr, sizeof(bfr.data), 0);
        }
        printf("\n");
    }
    else{   //parent
        printf("Child is dead \n");
        int n = sizeof(glob)/sizeof(int);
        for(int i =0; i < n; i++){
            struct message bfr;
            bfr.priority = 1;
            msgrcv(msgid, &bfr, sizeof(bfr.data), bfr.priority, 0);
            printf("%d ", bfr.data);
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
}
