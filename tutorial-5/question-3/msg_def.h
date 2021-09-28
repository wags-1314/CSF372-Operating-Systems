#ifndef MSG_DEFS_H
#define MSG_DEFS_H

#define DATAQ_ID      6969
#define ECHOQ_ID      3939
#define MAX_MSG_SIZE  512

struct message {
    long int type;
    char data[MAX_MSG_SIZE];
};

#endif
