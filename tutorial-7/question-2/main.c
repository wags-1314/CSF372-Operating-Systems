#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct vectors {
    int *row;
    int *column;
    int n;
};

void *multiply(void *);

int main() {
    int A[256][256];
    int B[256][256];
    int C[256][256];
    int n, k, m;

    pthread_t threads[256][256] = {0};

    struct vectors arr[256][256];

    scanf("%d", &n);
    scanf("%d", &k);
    scanf("%d", &m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            int temp;
            scanf("%d", &temp);
            A[i][j] = temp;
        }
    }

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < m; j++) {
            int temp;
            scanf("%d", &temp);
            B[i][j] = temp;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            arr[i][j].row = (int *)malloc(k * sizeof(int));
            arr[i][j].column = (int *)malloc(k * sizeof(int));
            for(int a = 0; a < k; a++) {
                arr[i][j].row[a] = A[i][a];
                arr[i][j].column[a] = B[a][j];
            }
            arr[i][j].n = k;
            pthread_create(&threads[i][j], NULL, multiply, (void *)&arr[i][j]);
        }
    }
}

void *multiply(void *data) {
    struct vectors* arg = (struct vectors *)data;
    printf("row> ");
    for(int i = 0; i < arg->n; i++) {
        printf("%d ", arg->row[i]);
    }
    printf("\ncol> ");
    for(int i = 0; i < arg->n; i++) {
        printf("%d ", arg->column[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}
