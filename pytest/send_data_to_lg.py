#!/usr/python

import struct
import socket
import random

sock = socket.create_connection(('127.0.0.1', 12777))
for i in range(0, 1000):
  size = random.randint(1, 2048)
  hdr = struct.pack('QQ', i, size)
  sock.send(hdr)
  print("Sending id %s with %s bytes" % (i, size))
  for j in range(0, size):
    sock.send(struct.pack('B', random.randint(0, 255)))

sock.close()
