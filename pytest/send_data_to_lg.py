#!/usr/bin/python

import struct
import socket
import random
import string
import os
from multiprocessing import Process

class LGClient:
  # struct FileHeader {
  #   byte   Cmd,
  #          Type;
  #   uint64 ID,
  #          StartOffset,
  #          Length;
  # };

  def __init__(self, prefix):
    self.prefix = prefix
    self.totalStreams = random.randint(1, 10)
    self.hdr = struct.Struct('<BBQQQ')
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

  def connect(self):
    self.sock.connect(('127.0.0.1', 12777))
    print("connected to lg as " + str(self.sock.getsockname()))

  def sendSearchHeader(self, id, len):
    self.sock.sendall(self.hdr.pack(0, 0, id, 0, len))

  def hangup(self):
    self.sock.sendall(self.hdr.pack(2, 0, 0, 0, 0))
    self.sock.recv(1)
    self.sock.close()

  def shutdown(self):
    self.sock.sendall(self.hdr.pack(3, 0, 0, 0, 0))
    self.sock.close()

  def sendStream(self, i):
    id = self.prefix + i
    len = random.randint(1, 2 << 28)
    self.sendSearchHeader(id, len)
    pages = len // 4096
    remainder = len % 4096
    for i in xrange(pages):
      data = ''.join(random.choice(string.ascii_lowercase) for x in xrange(4096))
      self.sock.sendall(data)
    data = ''.join(random.choice(string.ascii_lowercase) for x in xrange(remainder))
    self.sock.sendall(data)
    print("sent %s bytes for id %s" % (len, id))

  def run(self):
    self.connect()
    for i in xrange(self.totalStreams):
      self.sendStream(i)
    self.hangup()

def start(prefix):
  print("running client with prefix " + str(prefix))
  client = LGClient(prefix)
  client.run()

if __name__ == '__main__':
  print("starting")
  procs = [Process(target=start, args=[(i*10000)]) for i in xrange(5)]
  for p in procs:
    print("spawning proc")
    p.start()
  for p in procs:
    p.join()
  killer = LGClient(0)
  killer.connect()
  killer.shutdown()
  print("done")
