#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
pthread_mutex_t mutex;

typedef struct{
  char* filename;
  int n;
}worker_args_t;

void* worker(void* args){
  char* filename = ((worker_args_t*)args)->filename;
  int n = ((worker_args_t*)args)->n;

  int value = 0;

  FILE *f = fopen(filename, "r");
 
  while(n > 0 && fscanf(f, "%d", &value) == 1){
    if(value % 2 == 0){
      n--;
      pthread_mutex_lock(&mutex);
      sum += value;
      pthread_mutex_unlock(&mutex);
    }
  }
  fclose(f);

  return NULL;
}

int main(int argc, char** argv){
  if(argc % 2 != 1){
    printf("invalid args\n");
    return 1;
  }

  pthread_mutex_init(&mutex, NULL);
  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1) / 2);
  worker_args_t* args = (worker_args_t*)malloc(sizeof(worker_args_t) * (argc - 1) / 2);

  for(int i = 1;i < argc;i += 2){
    args[i >> 1].filename = argv[i];
    args[i >> 1].n = atoi(argv[i + 1]);
    pthread_create(&threads[i >> 1], NULL, &worker, &args[i >> 1]);
  }

  for(int i = 1;i < argc;i += 2){
    pthread_join(threads[i >> 1], NULL);
  }
  
  free(threads);
  free(args);
  pthread_mutex_destroy(&mutex);
  printf("sum %d\n", sum);
  return 0;
}
