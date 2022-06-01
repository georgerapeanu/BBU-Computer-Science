#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
  mkfifo("1_fifo", 0600);
  int fd_fifo = open("1_fifo", O_WRONLY);
  
  char filename[100];
  scanf("%s", filename);

  int fd_file = open(filename, O_RDONLY);
  if(fd_file == -1){
    printf("Failed to open file");
    return 0;
  }
  

  char current = 0;

  int k = 0;
  while((k = read(fd_file, &current, 1))){
    if(k == -1){
      break;
    }
    if(k > 0){
      if('0' <= current && current <= '9'){
        write(fd_fifo, &current, 1);
      }
    }
  }

  close(fd_file);
  close(fd_fifo);

  return 0;
}
