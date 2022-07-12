#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("This program receives exacly 1 argument: the name of the fifo to be used\n");
    return 1;
  }

  mkfifo(argv[1], 0600);
  int fd = open(argv[1], O_WRONLY);

  if(fd == -1){
    printf("Failed to open FIFO\n");
    return 1;
  }

  int n;
  scanf("%d", &n);

  for(int i = 1;i <= n;i++){
    if(n % i == 0){
      write(fd, &i, 4);
    }
  }

  close(fd);
  return 0;
}
