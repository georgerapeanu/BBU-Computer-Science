#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
  char* filename;
  char c;
  int n;
}thread_args;

void* thread(void* args){
  char* filename = ((thread_args*)args)->filename;
  int n = ((thread_args*)args)->n;
  char c = ((thread_args*)args)->c;
  
  FILE* f = fopen(filename, "r");
  if(f == NULL){
    printf("File %s doesn't exist\n", filename);
    return NULL;
  }

  char value;

  while(n > 0 && fscanf(f, "%c", &value) == 1){
    n--;
  }
  fclose(f);
  if(n > 0){
    printf("File %s is too small for n %d\n", filename, ((thread_args*)args)->n);
    return NULL;
  }
  n = ((thread_args*)args)->n;
  printf("File %s has on position %d the character %c(ascii code %hhd), which is %s character %c(ascii code %hhd)\n", filename, n, value, value, (c != value ? "different from":"the same with"), c, c);
  return NULL;
}

int main(int argc, char** argv){
  if(argc % 3 != 1){
    printf("invalid number of arguments\n");
    return 0;
  }

  thread_args* args = (thread_args*)malloc(sizeof(thread_args) * (argc - 1) / 3);
  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc - 1) / 3);

  for(int i = 1;i < argc;i += 3){
    args[i / 3].filename = (char*)argv[i];
    args[i / 3].n = atoi(argv[i + 1]);
    args[i / 3].c = argv[i + 2][0];
    pthread_create(&threads[i / 3], NULL, &thread, &args[i / 3]);
  }

  for(int i = 1;i < argc;i += 3){
    pthread_join(threads[i / 3], NULL);
  }

  free(threads);
  free(args);

  return 0;
}
