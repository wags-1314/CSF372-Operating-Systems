#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/shm.h>

#define N 20

int arr[] = { 19, 48, 38, 4, 29, 31, 18, 2, 33, 22, 34, 15, 25, 46, 30, 3, 26, 23, 43, 7 };

int main(){
    int shmid = shmget((key_t)1234, 1024, 0666|IPC_CREAT);
    int* shm_ptr = (int *)shmat(shmid, NULL, 0);
    
    pid_t pid = fork();
    
    if(pid == 0){
        /* Child Process */
        for (int i = 0; i < N - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < N; j++) {
                if (arr[j] < arr[min_index])
                    min_index = j;
            }
            
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
        
        for(int i = 0; i < N; i++) {
            shm_ptr[i] = arr[i];
        }
        
        shmdt(shm_ptr);
    } else {
        /* Parent Process */
        wait(NULL);
        for(int i = 0; i < N; i++){
            printf("%d ", shm_ptr[i]);
        }
        
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }
    
    return 0;
}
