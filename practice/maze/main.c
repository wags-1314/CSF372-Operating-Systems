#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 4

int maze[N][N] = {
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 1, 1}
};

int recurse(int n, int maze[n][n], int i, int j) {
    // Base Case
    if(i == (n - 1) && j == (n - 1) && maze[i][j] == 1) return 1;
    if(i == n || j == n || maze[i][j] == 0) return 0;
    
    // First check to right
    if(!fork()) {
        /* Child going right */
        exit(recurse(n, maze, i + 1, j));
    } else {
        /* Parent Waiting */
        int status;
        wait(&status);
        if(WEXITSTATUS(status)) {
            /* I found da ting */
            printf("(%d, %d) ", i + 1, j);
            exit(1);
        }
    }
    
    // Now check right to left
    if(!fork()) {
        /* Child going right */
        exit(recurse(n, maze, i, j + 1));
    } else {
        /* Parent Waiting */
        int status;
        wait(&status);
        if(WEXITSTATUS(status)) {
            /* I found da ting */
            printf("(%d, %d) ", i, j + 1);
            exit(1);
        }
    }
}

int main() {
    recurse(N, maze, 0, 0);
}
