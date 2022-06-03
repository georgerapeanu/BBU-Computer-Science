#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int* v;
int v_index;
pthread_mutex_t mutex;
pthread_barrier_t barrier;
pthread_barrier_t finished_barrier;

typedef struct{
  int index;
}thread_args_t;

void* thread(void* args){
  pthread_barrier_wait(&barrier);
  int last_index = -1;
  for(int i = 0;i < 10;i++){
    pthread_mutex_lock(&mutex);
    last_index = v_index++;
    v[last_index] = ((thread_args_t*)args)->index;
    pthread_mutex_unlock(&mutex);
  }
  pthread_barrier_wait(&finished_barrier);
  printf("Thread %d last wrote on position %d\n", ((thread_args_t*)args)->index, last_index);
  free(args);
  return NULL;
}

int main(int argc, char** argv){
  if(argc == 1){
    printf("USAGE: ./n10stuff N\n");
    return 0;
  }
  int n = atoi(argv[1]);

  v = (int*)malloc(sizeof(int) * n * 10);
  v_index = 0;
  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * n);

  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, n);
  pthread_barrier_init(&finished_barrier, NULL, n);

  for(int i = 0;i < n;i++){
    thread_args_t* args = (thread_args_t*)malloc(sizeof(thread_args_t));
    args->index = i;
    pthread_create(&threads[i], NULL, &thread, args);
  }

  for(int i = 0;i < n;i++){
    pthread_join(threads[i], NULL);
  }

  for(int i = 0;i < n * 10;i++){
    printf("%d ", v[i]);
  }
  printf("\n");

  pthread_barrier_destroy(&finished_barrier);
  pthread_barrier_destroy(&barrier);
  pthread_mutex_destroy(&mutex);
  free(threads);
  free(v);

  return 0;
}
