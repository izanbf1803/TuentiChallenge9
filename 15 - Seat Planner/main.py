import socket, sys

def sock_send(s, data):
    s.send(data.encode())
    print(f"SEND:\n---\n{data}---\n")

def sock_read(s):
    data = s.recv(1024).decode()
    print(f"RECV:\n---\n{data}---\n")
    return data

def solve_test(s, test):
    try:
        K, S = map(int,s.recv(1024).decode().split())
        print(K,S)
        for i in range(0, 8):
            sock_send(s, ','.join(str(8*i+j) for j in range(1, 9))+"\n")
        feedback = sock_read(s)
        print("feedback", feedback)
        print(f"END TEST #{test}")
    except Exception as e:
        print(f"ERROR: {e}")
        sys.exit(1)

IP = "52.49.91.111"
PORT = 1888
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(1)
s.connect((IP, PORT))
s.send(b"TEST\n")
N = int(sock_read(s))
for test in range(N):
    solve_test(s, test)