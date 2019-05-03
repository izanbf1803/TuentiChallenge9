import socket, sys, subprocess

def sock_send(s, data):
    s.send(data.encode())
    print(f"SEND:\n---\n{data}---\n")

def sock_read(s):
    data = s.recv(1024).decode()
    print(f"RECV:\n---\n{data}---\n")
    return data

def solve_test(s, test):
    try:
        lines = list(filter(lambda x: len(x) != 0, sock_read(s).split('\n')))
        if lines[0].find("Validator") != -1:
            raise Exception(lines[0])
        result = subprocess.run(["solver.exe", ' '.join(lines)], stdout=subprocess.PIPE)
        print(f"solver.exe RESULT:\n---\n{result.stdout.decode()}---\n")
        # TODO: call C++ solver
        for i in range(0, 8):
            sock_send(s, ','.join(str(8*i+j) for j in range(1, 9))+"\n")
    except Exception as e:
        print(f"ERROR on test #{test-1} => {e}")
        sys.exit(1)

subprocess.run(["make"])
IP = "52.49.91.111"
PORT = 1888
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(1)
s.connect((IP, PORT))
s.send(b"TEST\n")
N = int(sock_read(s))
for test in range(1,N+1):
    solve_test(s, test)