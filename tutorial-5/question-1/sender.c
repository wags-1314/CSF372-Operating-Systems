#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>

int main() {
    char buffer[256];
    char otp_buffer[256];

    int fd_out = open("fifo_to", O_WRONLY);
    int fd_in = open("fifo_from", O_RDONLY);
    
    printf("[%d] Enter message: ", getpid());
    fgets(buffer, 256, stdin);
    write(fd_out, buffer, 256);
    int n = read(fd_in, otp_buffer, 256);
    printf("[%d] Recieved flipped message: %s\n", getpid(), otp_buffer);

    close(fd_in);
    close(fd_out);
    return 0;
}
