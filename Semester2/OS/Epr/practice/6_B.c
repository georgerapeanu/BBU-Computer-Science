#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
  int fd = open("6_fifo", O_RDONLY);

  if(fd == -1){
    printf("Error opening fifo");
    exit(1);
  }

  for(int i = 0;i < 5;i++){
    int number = 0;
    read(fd, &number, 4);
    printf("%d ", number);
  }

  close(fd);
  return 0;
}
