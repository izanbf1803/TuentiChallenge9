def v_to_s(v):
    return ''.join(chr(x) for x in v)

def aa():
    l = -6970278787874799546
    v = [0]*8
    for i in range(8):
        v[i] = l % 256
        l >>= 8
    return v

def a(s):
    v = [ord(c) for c in s]
    for i in range(len(s)):
        v[i] = (v[i] ^ 98) % 256
    return reversed(v) # little endian

s1 = v_to_s(aa())
print(s1)
s2 = s1
for i in range(10):
    s2 = v_to_s(a(s2))
    print(s2)