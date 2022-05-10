#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("This program gets exactly one parameter: the name of the file used by P1\n");
    return 1;
  }

  int p1_2_p2[2];
  if(pipe(p1_2_p2) == -1){
    printf("Failed to create a pipe\n");
    return 1;
  }

  int k = fork();

  if(k == -1){
    printf("Failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    exit(1);
  }else if(k == 0){
    close(p1_2_p2[0]);
    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
      printf("Failed to open file\n");
      close(p1_2_p2[1]);
      exit(1);
    }

    char value = 0;
    int n = 0;
    scanf("%d", &n);

    while(n-- && fscanf(f,"%c", &value) == 1){
      ;
    }
    write(p1_2_p2[1], &value, 1);
    close(p1_2_p2[1]);

    fclose(f);
    exit(0);
  }
  
  k = fork();

  if(k == -1){
    printf("Failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    wait(0);
    exit(1);
  }else if(k == 0){
    close(p1_2_p2[1]);

    char value = 0;

    read(p1_2_p2[0], &value, 1);
    close(p1_2_p2[0]);

    if('0' <= value && value <= '9'){
      printf("Value is digit\n");
    }else if(('a' <= value && value <= 'z') || ('A' <= value && value <= 'Z')){
      printf("Value is letter\n");
    }else{
      printf("Value is other\n");
    }

    int fd = open("4_fifo", O_WRONLY);
    if(fd == -1){
      printf("Failed to open fifo\n");
      exit(1);
    }

    write(fd, &value, 1);
    
    close(fd);
    exit(0);
  }

  close(p1_2_p2[0]);
  close(p1_2_p2[1]);
  
  wait(0);
  wait(0);

  return 0;
}
