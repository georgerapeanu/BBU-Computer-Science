#!/usr/bin/python3

import socket
import struct
import random
import math 

WIN_STRING = 'You won!'
LOSE_STRING = 'You lost!'
CLIENT_COUNT = 3

def dist(a, b):
  return math.sqrt((b[0] - a[0]) ** 2 + (b[1] - a[1]) ** 2)

def main():
  x = random.randint(0, 100)
  y = random.randint(0, 100)

  print("Chosen %d %d" % (x,y))

  server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_socket.bind(('0.0.0.0', 1234))
  server_socket.listen(CLIENT_COUNT)

  clients = []

  for i in range(0, CLIENT_COUNT):
    clients.append(server_socket.accept()[0])
  
  client_dists = []

  for i in range(0, len(clients)):
    client_x = struct.unpack('!i', clients[i].recv(4))[0]
    client_y = struct.unpack('!i', clients[i].recv(4))[0]
    client_dist = dist((x, y), (client_x, client_y))
    client_dists.append(client_dist)

  best_dist = min(client_dists)
  
  for i in range(0, len(clients)):
    if best_dist == client_dists[i]:
      clients[i].send(struct.pack('!I', len(WIN_STRING)) + WIN_STRING.encode('ASCII'))
    else:
      clients[i].send(struct.pack('!I', len(LOSE_STRING)) + LOSE_STRING.encode('ASCII'))

  for i in range(0, len(clients)):
    clients[i].close()
  
  server_socket.shutdown(socket.SHUT_RDWR)
  server_socket.close()

if __name__ == '__main__':
  main()
