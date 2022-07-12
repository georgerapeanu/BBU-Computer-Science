#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int* sums;
int* finished_x;
pthread_cond_t* conds;
pthread_mutex_t* mutexes;

typedef struct{
  char* filename;
  int index;
}thread1_args_t;

void* thread1(void* args){

  char* filename = ((thread1_args_t*)args)->filename;
  int index = ((thread1_args_t*)args)->index;


  FILE *f = fopen(filename, "r");
  int a, b;
  fscanf(f,"%d%d", &a, &b);


  sums[index] = 0;
  while(sums[index] <= b){
    sums[index] += a;
  }
 
  pthread_mutex_lock(&mutexes[index]);
  finished_x[index] = 1;
  pthread_cond_signal(&conds[index]);
  pthread_mutex_unlock(&mutexes[index]);
  fclose(f);
  return NULL;
}

typedef struct{
  int index;
}thread2_args_t;

void* thread2(void* args){
  int index = ((thread2_args_t*)args)->index;
  pthread_mutex_lock(&mutexes[index]);
  if(finished_x[index] != 1){
    pthread_cond_wait(&conds[((thread2_args_t*)args)->index], &mutexes[index]);
  }
  pthread_mutex_unlock(&mutexes[index]);
  printf("sum for %d is %d\n", ((thread2_args_t*)args)->index, sums[((thread2_args_t*)args)->index]);
  return NULL;
}

int main(int argc, char** argv){
  pthread_t* x_threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1));
  pthread_t* y_threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1));
  sums = (int*)malloc(sizeof(int) * (argc - 1));
  conds = (pthread_cond_t*)malloc(sizeof(pthread_cond_t) * (argc - 1));
  mutexes = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * (argc - 1));
  finished_x = (int*)malloc(sizeof(int) * (argc - 1));
  for(int i = 1;i < argc;i++){
    sums[i - 1] = 0;
    finished_x[i - 1] = 0;
    pthread_cond_init(&conds[i - 1], NULL);
    pthread_mutex_init(&mutexes[i - 1], NULL);
  }
  thread1_args_t* x_args = (thread1_args_t*)malloc(sizeof(thread1_args_t) * (argc - 1));
  thread2_args_t* y_args = (thread2_args_t*)malloc(sizeof(thread2_args_t) * (argc - 1));
  for(int i = 1;i < argc;i++){
    x_args[i - 1].index = i - 1;
    x_args[i - 1].filename = (char*)argv[i];
    y_args[i - 1].index = i - 1;

    pthread_create(&x_threads[i - 1], NULL, &thread1, &x_args[i - 1]);
    pthread_create(&y_threads[i - 1], NULL, &thread2, &y_args[i - 1]);
  }

  for(int i = 1;i < argc;i++){
    pthread_join(x_threads[i - 1], NULL);
    pthread_join(y_threads[i - 1], NULL);
    pthread_cond_destroy(&conds[i - 1]);
    pthread_mutex_destroy(&mutexes[i - 1]);
  }

  free(sums);
  free(conds);
  free(x_threads);
  free(y_threads);
  free(x_args);
  free(y_args);
  free(mutexes);
  free(finished_x);

  return 0;
}
