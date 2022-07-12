#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int gcd(int a, int b){
  if(b == 0)return a;
  return gcd(b, a % b);
}

int lcm(int a, int b){
  return a * b / gcd(a, b);
}

int main(int argc, char** argv){
  if(argc != 2){
    printf("This program receives exactly 1 argument: the name of the fifo to be used\n");
    return 1;
  }

  mkfifo(argv[1], 0600);
  int fd_fifo = open(argv[1], O_WRONLY);
  if(fd_fifo == -1){
    printf("Failed to open fifo");
    return 0;
  }


  int a, b;
  scanf("%d", &a);
  scanf("%d", &b);
  int ans = lcm(a, b);

  write(fd_fifo, &ans, 4);
  close(fd_fifo);

  return 0;
}
