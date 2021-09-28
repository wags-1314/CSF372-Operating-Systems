#include<stdio.h>

int main() {
    char buffer[100];
    fgets(buffer, 100, stdin);
    printf("> %s\n", buffer);
}
