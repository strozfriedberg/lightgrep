#!/usr/bin/python

# Copyright 2024 Aon Cyber Solutions
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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

#  data = data[16+size:]

  for j in range(0, size):
    print struct.unpack('B', data[16+j])
  data = data[16+size:]

sock.close()
