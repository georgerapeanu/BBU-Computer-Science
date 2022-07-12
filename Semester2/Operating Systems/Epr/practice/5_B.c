#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("This program receives exacly 1 argument: the name of the fifo to be used\n");
    return 1;
  }
  
  int p1_2_p2[2];

  if(pipe(p1_2_p2) == -1){
    printf("Failed to create pipe\n");
    exit(1);
  }

  int k;

  k = fork();
  if(k == -1){
    printf("Failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    exit(1);
  }else if(k == 0){
    close(p1_2_p2[0]);
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
      printf("Failed to open FIFO\n");
      close(p1_2_p2[1]);
      exit(1);
    }
    int number = 0;
    int sum = 0;
    while(read(fd, &number, 4) > 0){
      sum += number;
    }
    close(fd);
    write(p1_2_p2[1], &sum, 4);
    close(p1_2_p2[1]);
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
    int number = 0;
    read(p1_2_p2[0], &number, 4);
    printf("%d\n", number);
    exit(0);
  }

  close(p1_2_p2[0]);
  close(p1_2_p2[1]);
  wait(0);
  wait(0);

  unlink(argv[1]);

  return 0;
}
