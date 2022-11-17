#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int listening_socket_fd;
void handle_interrupt(int signal) {
  printf("interrupted");
  close(listening_socket_fd);
  exit(0);
}

int main(){
  signal(SIGINT, handle_interrupt);
  listening_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(listening_socket_fd == -1){
    printf("error creating socket");
    return 1;
  }
  struct sockaddr_in server_addr;
  memset((void*) &server_addr, 0, sizeof(server_addr));
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(1234);
  server_addr.sin_family = AF_INET;

  if(bind(listening_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("bind error\n");
    return 1;
  }
  
  listen(listening_socket_fd, 5);



  while(1){
    int32_t a;
    int32_t b;
    int client_socket = accept(listening_socket_fd, NULL, NULL);
    if(client_socket < 0){
      printf("accept error");
    }

    recv(client_socket, &a, sizeof(a), 0);
    recv(client_socket, &b, sizeof(b), 0);
    a = ntohl(a);
    b = ntohl(b);
    a += b;
    a = htonl(a);
    send(client_socket, &a, sizeof(a), 0);
    close(client_socket);
  }
  return 0;
}
