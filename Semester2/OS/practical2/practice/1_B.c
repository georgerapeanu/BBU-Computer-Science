#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  int p1_2_p2[2];
  pipe(p1_2_p2);

  int k = fork();

  if(k == -1){
    printf("failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    return 1;
  }else if(k == 0){ /// P1
    close(p1_2_p2[0]);
    int fd = open("1_fifo", O_RDONLY);
    if(fd == -1){
      printf("failed to open fifo\n");
      close(p1_2_p2[1]);
      exit(1);
    }
    char current = 0;
    int sum = 0;
    while((k = read(fd, &current, 1))){
      if(k == -1){
        break;
      }
      if(k > 0){
        sum += current - '0';
      }
    }
    write(p1_2_p2[1], &sum, 4);
    close(p1_2_p2[1]);
    close(fd);
    exit(0);
  }

  k = fork();

  if(k == -1){
    printf("failed to fork\n");
    close(p1_2_p2[0]);
    close(p1_2_p2[1]);
    wait(0);
    return 1;
  }else if(k == 0){ /// P2
    close(p1_2_p2[1]);
    int sum = 0;
    read(p1_2_p2[0], &sum, 4);
    close(p1_2_p2[0]);

    for(int i = 1;i <= sum;i++){
      if(sum % i == 0){
        printf("divisor %d\n", i);
      }
    }
    close(p1_2_p2[1]);
    exit(0);
  }

  close(p1_2_p2[0]);
  close(p1_2_p2[1]);

  wait(0);
  wait(0);
  unlink("1_fifo");
  return 0;
}
