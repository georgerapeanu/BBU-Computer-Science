#!/usr/bin/python3
import socket
import threading
import struct
import time

def main():
  server_socket = socket.socket(family = socket.AF_INET, type=socket.SOCK_DGRAM)
  server_socket.bind((socket.inet_ntoa(struct.pack("!L", socket.INADDR_ANY)), 7777))
  while True:
    data, addr = server_socket.recvfrom(1024)
    time.sleep(0.5)
    server_socket.sendto(data, addr)
 
if __name__ == '__main__':
  main()
