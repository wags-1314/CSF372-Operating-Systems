#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int t, w;

int *tokens;
int *windows;

int cur_token = 0;

pthread_t *token_threads;

sem_t token_mutex;
sem_t window_mutex;

void *window_pthread(void *args) {
    int my_no = (int)args;
    printf("Window %d : Ready for token %d\n", my_no, windows[my_no]);
    clock_t start = clock();
    int last = 0;
    printf("Window %d : Registration for token %d ongoing\n", my_no, windows[my_no]);
    while(last < 5){
        double elapsed = (double)(clock()-start)/CLOCKS_PER_SEC;
        int cur = (int)elapsed;

        if(cur != last)
            last = cur;   
    }
    printf("Window %d : Registration for token %d completed\n", my_no, windows[my_no]);
    windows[my_no] = 0;
    pthread_exit(NULL);
}

void *token_pthread(void *args) {
    int token_no;

    sem_wait(&token_mutex);
    cur_token++;
    token_no = cur_token;
    sem_post(&token_mutex);
    int curr_window;
    sem_wait(&window_mutex);
    printf("Token %d : Waiting for a window\n", token_no);
    for (int i = 0; i < w; i = (i + 1) % w) {
        //printf(">%d\n", i);
        if(!windows[i]) {
            windows[i] = token_no;
            curr_window = i;
            break;
        }        
    }
    //printf(">> %d\n", curr_window);
    sem_post(&window_mutex);

    pthread_t n_window;
    pthread_create(&n_window, NULL, window_pthread, (void *)curr_window);
    pthread_join(n_window, NULL);
    pthread_exit(NULL);
}

int main() {
  scanf("%d", &t);
  scanf("%d", &w);

    sem_init(&token_mutex, 0, 1);
    sem_init(&window_mutex, 0, 1);

  //tokens = (int *)malloc(sizeof(int) * t);
  windows = (int *)malloc(sizeof(int) * w);

  token_threads = (pthread_t *)malloc(sizeof(pthread_t) * t);

  int count = t;

  for (int j = 0; j < t; j++) {
    pthread_create(&token_threads[j], NULL, token_pthread, (void *)&j);
  }

  for (int l = 0; l < t; l++) {
    pthread_join(token_threads[l], NULL);
  }

  pthread_exit(NULL);
}
