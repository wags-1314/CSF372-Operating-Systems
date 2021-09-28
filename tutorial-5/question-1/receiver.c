#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>

int main() {
    char buffer[256];
    
    int fd_in = open("fifo_to", O_RDONLY);
    int fd_out = open("fifo_from", O_WRONLY);
    int n = read(fd_in, buffer, 256);

    printf("[%d] Recieved: %s\n", getpid(), buffer);
    for(int i = 0; i < strlen(buffer); i++) {
        if(isalpha(buffer[i])) {
            buffer[i] ^= 32;
        }
    }

    write(fd_out, buffer, 256);
    printf("[%d] Sent: %s\n", getpid(), buffer);
    close(fd_in);
    close(fd_out);
    return 0;
}
