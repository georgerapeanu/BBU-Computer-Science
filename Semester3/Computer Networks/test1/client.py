#!/usr/bin/python3
import socket
import struct

def main():
  server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_socket.connect(('127.0.0.1', 1234))
  x = int(input('Please input x: '))
  y = int(input('Please input y: '))
  server_socket.send(struct.pack('!i', x))
  server_socket.send(struct.pack('!i', y))
  status_length = struct.unpack('!I', server_socket.recv(4))[0]
  status = server_socket.recv(status_length).decode('ASCII')
  print(status)
  server_socket.shutdown(socket.SHUT_RDWR)
  server_socket.close()

if __name__ == '__main__':
  main()
