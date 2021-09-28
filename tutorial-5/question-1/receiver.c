#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main() {
    char buffer[256];
    
    int fd = open("fifo_to", O_RDONLY);
    int n = read(fd, buffer, 256);
    printf("[%d]Recieved: %s\n", getpid(), buffer);
    close(fd);

    return 0;
}
