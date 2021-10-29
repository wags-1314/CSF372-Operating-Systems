#include <stdio.h>
#include <pthread.h>

int arr[256];
int _arr[256];
pthread_t threads[256];
void *find(void *);
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);
        arr[i] = temp;
        threads[i] = i;
    }

    for(int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, find, (void *)(long)i);
        //printf(">%ld\n", threads[i]);
    }

    for(int i = 0; i < n; i++) {
        void *new = NULL;
        pthread_join(threads[i], &new);
        //printf("%d -> %ld", i, (long)new);
        _arr[(long)new] = arr[i]; // long should be intptr_t
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", _arr[i]);
    }

    pthread_exit(NULL);
    return 0;
}

void *find(void *data) {
    long index = (long) data;
    long count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[index] > arr[i] && index != i) count += 1;
    }
    pthread_exit ((void *) count);
}
