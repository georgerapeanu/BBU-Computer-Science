#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  int fd = open("3_fifo", O_RDONLY);

  if(fd == -1){
    printf("Failed to open fifo\n");
    return 1;
  }

  int number = 0;
  read(fd, &number, 4);

  printf("Received %d\n", number);

  return 0;
}
