#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  int fd = open("4_fifo", O_RDONLY);

  if(fd == -1){
    printf("Failed to open fifo\n");
    return 1;
  }

  char value = 0;
  read(fd, &value, 1);

  printf("Ascii code is %hhu\n", value);

  return 0;
}
