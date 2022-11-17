#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(){
  
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_fd < 0){
    printf("socket error");
    return 1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_port = htons(1234);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if(connect(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
    printf("connection eror");
  }

  int32_t a;
  int32_t b;
  printf("a=");
  scanf("%d", &a);
  printf("b=");
  scanf("%d", &b);

  a = htonl(a);
  b = htonl(b);
  send(socket_fd, &a, sizeof(a), 0);
  send(socket_fd, &b, sizeof(b), 0);
  recv(socket_fd, &a, sizeof(a), 0);
  a = ntohl(a);
  printf("sum is %d\n", a);
  return 0;
}
