def gcd(a, b):
    if a > b: return gcd(b, a)
    if a == 0: return b
    return gcd(b%a, a)

def lcm(a, b):
    return a // gcd(a, b) * b

tests = int(input())
for test in range(tests):
    n = int(input())
    m = {}
    for v in map(int,input().split()):
        if v in m:
            m[v] += 1
        else:
            m[v] = 1
    x = 1
    for key in m:
        x = lcm(x, key*m[key])
    total, people = 0, 0
    for key in m:
        people += x*m[key]//key
        total += x*m[key]
    g = gcd(total, people)
    print(f"Case #{test+1}: {total//g}/{people//g}")