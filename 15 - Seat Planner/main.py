# This scripts deals with the TCP server and calls the main.exe (compiled from main.cc) to solve the problem.

import socket, sys, subprocess, time

DEBUG_SOCK = False

def sock_send(s, data):
    s.send(data.encode())
    if DEBUG_SOCK:
        print(f"SEND:\n---\n{data}---\n")

def sock_read(s):
    data = s.recv(1048576).decode()
    if DEBUG_SOCK:
        print(f"RECV:\n---\n{data}---\n")
    return data

def solve_test(s, test):
    global t0, solver_input, sol, lines
    try:
        lines = list(filter(lambda x: len(x) != 0, sock_read(s).split('\n')))
        if lines[0].find("Validator") != -1:
            raise Exception(lines[0])
        solver_input = ' '.join(lines)
        result = subprocess.run(["solver.exe", solver_input], stdout=subprocess.PIPE)
        sol = result.stdout.decode()
        for line in sol.splitlines():
            sock_send(s, line+"\n")
    except Exception as e:
        print(f"ERROR on test #{test-1} => {e}")
        print("LINES:", lines)
        print("SOLVER_INPUT:", solver_input)
        print(f"solver.exe RESULT:\n---\n{sol}---\n")
        print(time.time()-t0)
        sys.exit(1)

subprocess.run(["make"])
IP = "52.49.91.111"
PORT = 1888
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(5)
s.connect((IP, PORT))
s.send(b"SUBMIT\n")
t0 = time.time()
N = int(sock_read(s))
for test in range(1,N+1):
    solve_test(s, test)
print(sock_read(s))