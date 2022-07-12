#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t mutex;
int count_letters;
int count_digits;

void* worker(void* args){
  FILE*f = fopen((char*)args, "r");
  char c;
  int local_count_letters = 0;
  int local_count_digits = 0;
  while(fscanf(f,"%c", &c) == 1){
    if('0' <= c && c <= '9'){
      local_count_digits++;
    }else if('a' <= c && c <= 'z'){
      local_count_letters++;
    }else if('A' <= c && c <= 'Z'){
      local_count_letters++;
    }
  }
  fclose(f);
  pthread_mutex_lock(&mutex);
  count_letters += local_count_letters;
  count_digits += local_count_digits;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main(int argc, char** argv){
  pthread_mutex_init(&mutex, NULL);
  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1));
  for(int i = 1;i < argc;i++){
    pthread_create(&threads[i - 1], NULL, &worker, (void*)argv[i]);
  }
  for(int i = 1;i < argc;i++){
    pthread_join(threads[i - 1], NULL);
  }
  printf("%d %d\n", count_letters, count_digits);
  free(threads);
  pthread_mutex_destroy(&mutex);
  return 0;
}
