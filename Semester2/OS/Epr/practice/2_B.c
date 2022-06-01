#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("This program receives exactly 1 argument: the name of the fifo to be used\n");
    return 1;
  }

  int p1_2_p2[2];

  pipe(p1_2_p2);

  int k = fork();

  if(k == -1){
    printf("Failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    return 1;
  }else if(k == 0){
    close(p1_2_p2[0]);
    
    int fd_fifo = open(argv[1], O_RDONLY);
    if(fd_fifo == -1){
      printf("Failed to open fifo\n");
      close(p1_2_p2[1]);
      exit(1);
    }

    int number = 0;
    read(fd_fifo, &number, 4);
    close(fd_fifo);

    for(int i = 1;i <= number;i++){
      if(number % i == 0){
        write(p1_2_p2[1], &i, 4);
      }
    }

    close(p1_2_p2[1]);
    exit(0);
  }
  
  k = fork();

  if(k == -1){
    printf("Failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    wait(0);
    return 1;
  }else if(k == 0){
    close(p1_2_p2[1]);
    int number = 0;
    while(read(p1_2_p2[0], &number, 4) > 0){
      printf("%d\n", number);
    }
    close(p1_2_p2[0]);
    exit(0);
  }

  close(p1_2_p2[0]);
  close(p1_2_p2[1]);

  wait(0);
  wait(0);

  unlink(argv[1]);
  
  return 0;
}
