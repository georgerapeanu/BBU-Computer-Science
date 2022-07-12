#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
  int p1_2_p2[2];
  if(pipe(p1_2_p2) == -1){
    printf("Failed to create pipe\n");
    return 1;
  }

  int k;

  k = fork();

  if(k == -1){
    printf("Failed on fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    exit(1);
  }else if(k == 0){
    close(p1_2_p2[0]);
    char c = 0;

    while(read(0, &c, 1) > 0){
      write(p1_2_p2[1], &c, 1);
    }
    close(p1_2_p2[1]);
    exit(0);
  }
  
  k = fork();

  if(k == -1){
    printf("Failed on fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    wait(0);
    exit(1);
  }else if(k == 0){
    close(p1_2_p2[1]);
    char filepath[1001];
    
    int idx = 0;
    while(idx <= 1000 && read(p1_2_p2[0], filepath + idx, 1) > 0){
      idx++;
    }
    close(p1_2_p2[0]);

    if(idx > 1000){
      printf("Error: path length limit reached.\n");
      exit(1);
    }

    FILE* f = fopen(filepath, "r");
    int fr[5] = {0,0,0,0,0};
    char c;

    while(fscanf(f,"%c", &c) == 1){
      if(c == 'A'){
        fr[0]++;
      }else if(c == 'E'){
        fr[1]++;
      }else if(c == 'I'){
        fr[2]++;
      }else if(c == 'O'){
        fr[3]++;
      }else if(c == 'U'){
        fr[4]++;
      }
    }
    fclose(f);
    int fd = open("6_fifo", O_WRONLY);
    if(fd == -1){
      printf("Error opening fifo\n");
      exit(1);
    }

    write(fd, fr, 4 * 5);
    close(fd);

    exit(0);
  }

  close(p1_2_p2[0]);
  close(p1_2_p2[1]);
  wait(0);
  wait(0);

  return 0;
}
