#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if(argc != 3){
    printf("Usage: %s SERVER PORT\n", argv[0]);
    return 1;
  }
  int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(socket_fd < 0){
    printf("Socket error");
    return 1;
  }

  srand(time(NULL));
  char* random_stuff = (char*)malloc(11);
  char* response = (char*)malloc(11);
  random_stuff[10] = response[10] = 0x00;
  
  struct sockaddr_in server;
  memset(&server, 0 ,sizeof(server));
  server.sin_port = htons(atoi(argv[2]));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  

  for(int i = 0;i < 4;i++){
    for(int i = 0;i < 10;i++){
      random_stuff[i] = rand() & 0x7f;
    }
    time_t start = time(NULL);
    int tmp = sendto(socket_fd, random_stuff, 11, 0, (struct sockaddr*) &server, sizeof(server));
    if(tmp < 0) {
      printf("error sending\n");
    }
    if(recvfrom(socket_fd, response, 11, 0, NULL, 0) < 0) {
      printf("error recieving\n");
    }
    time_t end = time(NULL);
    int ok = 1;
    for(int i = 0;i <= 10;i++){
      ok &= (random_stuff[i] == response[i]);
    }
    printf("ping %d took %ld and is %s\n", i, end - start, (ok ? "VALID":"INVALID"));
  }

  return 0;
}
