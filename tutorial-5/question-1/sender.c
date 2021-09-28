#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main() {
    char buffer[256];
    
    printf("Enter message:\n");
    fgets(buffer, 256, stdin);

    int fd = open("fifo_to", O_WRONLY);
    write(fd, buffer, 256);
    printf("[%d]Sent: %s\n", getpid(), buffer);
    close(fd);
    return 0;
}
