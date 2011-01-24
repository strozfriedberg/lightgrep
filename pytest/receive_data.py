#!/usr/bin/python

import struct
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('127.0.0.1', 12777))  
sock.listen(1)
conn, addr = sock.accept()

data = ''

while 1:
  while len(data) < 16:
    data += conn.recv(1024)
    if not data: break

  if not data: break

  i, size = struct.unpack('QQ', data[0:16])
  print("Received id %s with %s bytes" % (i, size))

  while len(data) < size + 16:
    data += conn.recv(1024)
    if not data: break

  if not data: break

  data = data[16+size:]

#  for j in range(0, size):
#    print struct.unpack('B', data[16+j])
#  data = data[size:]

sock.close()
