#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXVALUE 100


typedef struct{
    int value;
    int next;
    int index;
}thread_args_t;


int sum;
pthread_cond_t cond;
pthread_mutex_t mutex;
int turn = -1;

void* thread(void* args){
    int value = ((thread_args_t*)args)->value;
    int next = ((thread_args_t*)args)->next;
    int index = ((thread_args_t*)args)->index;
    while(1){
        pthread_mutex_lock(&mutex);
        while(1){
            if(turn == -1){
                turn = index;       
            }
            if(turn == index){
                break;   
            }
            if(sum >= MAXVALUE){
                break;
            }
        //    printf("Thread %d waits\n", index); 
            pthread_cond_wait(&cond, &mutex);
        //    printf("Thread %d done waiting\n", index); 
        }
        if(sum >= MAXVALUE){
            break;
        }
        sum += value;
        printf("Thread %d adds to the sum %d, the new sum is %d\n", index, value, sum);       
        if(sum % 2 == 0){
            turn = next;           
        }else{
            turn = -1;
        }
        printf("Next thread to execute should be %d\n", turn);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }   
    pthread_mutex_unlock(&mutex);
    free(args);
    return NULL;
}

int main(int argc, char ** argv){

    if(argc % 2 != 1){
        printf("Invalid number of arguments\n");
        return 0;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL); 

    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1) / 2);
    for(int i = 1;i < argc;i += 2){
        thread_args_t* args = (thread_args_t*)malloc(sizeof(thread_args_t));
        args->index = (i - 1) / 2;
        args->value = atoi(argv[i]);
        args->next = atoi(argv[i + 1]);
        pthread_create(&threads[(i - 1) / 2], NULL, &thread, args);
    }

    for(int i = 1; i < argc;i += 2){
        pthread_join(threads[(i - 1) / 2], NULL);
    }

    free(threads);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}

